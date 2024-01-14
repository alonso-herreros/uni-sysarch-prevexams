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


static int initialize_data(char *filename);
static void destroy_data();
disk *cat_getdisk(category *cat_ptr, char *disk_title);
int disk_add(disk *disk, song new_song);
int disk_indexoftitle(disk *disk, char *song_title);


// Calculates the duration of all the songs in a category
int calculate_duration(category *category_ptr){ /*...*/ }
int main(int argc, char **argv){ /* SECTION 1.3 */}

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
        if (disk->num_tracks >= MAXIMUM_TRACKS)  return 0;
        found_index = ++disk->num_tracks;
    }
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
        disk_found = disk_new(disk_title);
    }
    disk_add(disk_found, new_song);
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

    fd = fopen(filename, "r");

    if(fd==NULL){ return -1;}

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
