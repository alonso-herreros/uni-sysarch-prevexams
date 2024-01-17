#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MUSIC_DATA_FILE "music_data.txt"
#define LINE_SIZE 120
#define MAXIMUM_TRACKS 20
#define PIPE_R 0
#define PIPE_W 1

typedef struct song_info song;
typedef struct disk_info disk, *disk_ptr;
typedef struct category_info category;

struct song_info
{
  unsigned duration;
  char *title;
};

struct disk_info
{
  char *disk_title;
  int num_tracks; /* Number of tracks in the disk */
  song songs[MAXIMUM_TRACKS];
  disk_ptr next;
};

struct category_info
{
  int num_of_disks;
  disk_ptr first;
};

enum categories {RAP, ROCK, RUMBA};
category rap, rock, rumba;
pid_t childpid, pid;
int status;

void parent(int pipefd[2]);
void child(int pipefd[2], char *filename);

static int initialize_data(char *filename);
static void destroy_data();
int cat_add(category *cat, disk* disk);
disk *cat_getdisk(category *cat_ptr, char *disk_title);
int disk_add(disk *disk, song new_song);
int disk_indexoftitle(disk *disk, char *song_title);


// Calculates the duration of all the songs in a category
int calculate_duration(category *category_ptr)
{
    if (category_ptr == NULL || category_ptr->num_of_disks == 0) return 0;

    int sum = 0;
    for (disk *c_disk = category_ptr->first; c_disk != NULL; c_disk = c_disk->next) {
        int i;
        for (song c_song = c_disk->songs[i=0]; i<c_disk->num_tracks; c_song = c_disk->songs[++i]) {
            sum += c_song.duration;
        }
    }
    return sum;
}

void child(int pipefd[2], char *filename)
{
    close(pipefd[PIPE_R]);
    // printf("[DBG][C] started\n");

    if(initialize_data(filename)<0) {
        // printf("[DBG][C] Init Data ERROR\n");
        kill(getppid(), SIGINT);
        close(pipefd[PIPE_W]);
        exit(EXIT_FAILURE);
    }
    // printf("[DBG][C] Init Data OK\n");

    int durations[3];
    durations[0] = calculate_duration(&rap);
    durations[1] = calculate_duration(&rock);
    durations[2] = calculate_duration(&rumba);

    write(pipefd[PIPE_W], durations, 3*sizeof(int));
    close(pipefd[PIPE_W]);

    // printf("[DBG][C] Destroying data\n");
    destroy_data();
    // printf("[DBG][C] Ending\n");
    exit(EXIT_SUCCESS);
}

void parent(int pipefd[2])
{
    signal(SIGTSTP, SIG_IGN);
    close(pipefd[PIPE_W]);

    // printf("[DBG][P] Started\n");
    
    int durations[3];
    read(pipefd[PIPE_R], durations, 3*sizeof(int));
    
    printf("Duration of rumba songs: %d\nDuration of rock songs: %d\nDuration of rap songs: %d\n",
        durations[2], durations[1], durations[0]);

    // printf("[DBG][P] Ending\n");
    childpid = wait(&status);
    // printf("[DBG][P] Child ended with %d\n", status);
    if (status == EXIT_FAILURE)  exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

#ifndef TEST
int main(int argc, char **argv)
{
    if (argc != 2)  exit(EXIT_FAILURE);
    char *filename = argv[1];
    // printf("[DBG] Args OK\n");

    int pipefd[2];
    if (pipe(pipefd) < 0)  exit(EXIT_FAILURE);
    // printf("[DBG] Pipe OK\n");

    if ((childpid = fork()) < 0)  exit(EXIT_FAILURE);
    else if (childpid == 0)  child(pipefd, filename);
    parent(pipefd);
}
#endif

int cat_add(category *cat, disk *new_disk) {
    if (cat == NULL || new_disk == NULL)  return -1;

    if (cat->num_of_disks == 0) {
        // printf("[DBG] Category empty. Adding as first disk.\n");
        cat->first = new_disk;
        cat->num_of_disks = 1;
        return 1;
    }
    
    // printf("[DBG] Category not empty (%d disks).\n", cat->num_of_disks);

    disk *disk_found = cat_getdisk(cat, new_disk->disk_title);
    if (disk_found == new_disk) {
        // printf("[DBG] Disk is already in category\n");
        return 1;
    }
    
    if (disk_found == NULL) {
        // printf("[DBG] Disk not found. Appending.\n");
        disk *curr;
        for (curr = cat->first; curr->next != NULL; curr = curr->next);
        curr->next = new_disk;
        cat->num_of_disks++;
        return 1;
    }

    // printf("[DBG] Equivalent disk found at %p. Searching for pointer to it.\n", disk_found);
    for (disk **curr = &(cat->first); (*curr) != NULL; curr = &((*curr)->next)){
        // printf("[DBG] Checking: %p\n", (*curr));
        if ((*curr) == disk_found) {
            // printf("[DBG] Redirecting pointer towards %p\n", new_disk);
            *curr = new_disk;
            free(disk_found);
        }
    }

    return 1;
}

disk *cat_getdisk(category *cat, char *disk_title)
{
    if (cat == NULL || cat->num_of_disks == 0 || disk_title == NULL) return NULL;

    for (disk *curr = cat->first; curr != NULL; curr = curr->next) {
        if (strcmp(curr->disk_title, disk_title) == 0)  return curr;
    }
    return NULL;
}

disk *disk_new(char *disk_title) {
    disk *new_disk = (disk *) calloc(sizeof(disk),1);
    new_disk->disk_title = strdup(disk_title);
    return new_disk;
}

int disk_add(disk *disk, song new_song)
{
    int found_index = disk_indexoftitle(disk, new_song.title);
    if (found_index == -1) {
        // printf("[DBG] Song '%s' not found. Will append.\n", new_song.title);
        if (disk->num_tracks >= MAXIMUM_TRACKS)  return 0;
        found_index = disk->num_tracks++;
    }
    // printf("[DBG] Adding song at position %d\n", found_index);
    disk->songs[found_index] = new_song;
    return 1;
}

int disk_indexoftitle(disk *disk, char *song_title)
{
    if (disk == NULL || disk->num_tracks == 0 || song_title == NULL)  return -1;

    int i;
    for (song curr = disk->songs[i=0]; i<disk->num_tracks; curr = disk->songs[++i]) {
        if (strcmp(curr.title, song_title) == 0) return i;
    }
    return -1;
}

void add_item(song new_song, category *category_ptr, char *disk_title) {
    disk *disk_found = cat_getdisk(category_ptr, disk_title);
    if (disk_found == NULL) {
        // printf("[DBG] Disk '%s' not found. Creating new disk\n", disk_title);
        disk_found = disk_new(disk_title);
    }
    // printf("[DBG] Adding song '%s' to disk '%s'\n", new_song.title, disk_found->disk_title);
    disk_add(disk_found, new_song);
    // printf("[DBG] Disk has %d songs after addition\n", disk_found->num_tracks);
    // printf("[DBG] Adding disk '%s' to category\n", disk_found->disk_title);
    cat_add(category_ptr, disk_found);
    // printf("[DBG] Category has %d disks after addition\n", category_ptr->num_of_disks);
}

static int initialize_data(char *filename) {
    FILE *fd;
    char *buffer = NULL;
    ssize_t readc=0;
    size_t n=0;
    char* token;
    char* rest;
    int duration;
    enum categories music_category;

    // printf("[DBG][C] Trying to open '%s'\n", filename);

    fd = fopen(filename, "r");

    if(fd==NULL){ return -1;}

    // printf("[DBG][C] File open OK\n");

    // Read lines and initialize data
    while((readc=getline(&buffer, &n, fd)!=-1)){
        buffer[strcspn(buffer, "\r\n")] = 0;
        // Get individual values with strtok
        rest = buffer;

        // Get category
        token = strtok_r(rest, ",", &rest);

        if(strcmp(token,"rap") == 0) music_category = RAP;
        else if(strcmp(token,"rock") == 0) music_category = ROCK;
        else if(strcmp(token,"rumba") == 0) music_category = RUMBA;

        // Get disk
        token = strtok_r(rest, ",", &rest);
        char *disk_title = strdup(token); // 1-argument function to copy the String

        // Get song title
        token = strtok_r(rest, ",", &rest);
        char *title = strdup(token);

        // Get duration
        token = strtok_r(rest, ",", &rest);
        duration = atoi(token);

        // Append to data structures
        song new_song;
        new_song.duration = duration;
        new_song.title = title;
        if(music_category==RAP){ add_item(new_song, &rap, disk_title); }
        if(music_category == ROCK) { add_item(new_song, &rock, disk_title); }
        if(music_category == RUMBA) { add_item(new_song, &rumba, disk_title); }
    }
    free(buffer);

    if(fclose(fd)!=0){
        perror("Error when closing file");
        return -1;
    }
    return 0;
}

// Destroy the data created
static void destroy_data() { /*...*/ }
// Destroy the data for one category
static void destroy_category(category *category_ptr) { /*...*/ }
