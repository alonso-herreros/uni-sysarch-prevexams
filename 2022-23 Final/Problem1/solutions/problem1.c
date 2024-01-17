/*
  FileName    [my_music.c]
  Synopsis    [Program to gather statistics about a music collection.]
  Description [Given a data structure to organize music, gather some
  statistics.]
*/

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

static int   initialize_data(char *filename);
static void destroy_data();
static void destroy_category(category *category_ptr);

/*
  Synopsis             [Calculates the duration of all the songs in a category.]
  Parameters         [A pointer to a category]  
*/
int calculate_duration(category *category_ptr)
{
    int result = 0;
    disk_ptr dptr;
    int i;

	if(category_ptr == NULL){
		return -1;
	}
    /* Get a pointer to traverse the list of disks */
    dptr = category_ptr->first;
    if (dptr == NULL)
    {
      return result;
    }

    /* Loop over the list and accumulate durations */
    while (dptr != NULL)
    {
	  int num_tracks = dptr->num_tracks;
      for (i = 0; i < num_tracks; i++)
      {
		//printf("Duration %i\n", dptr->songs[i].duration);
        result += dptr->songs[i].duration;
      }
      dptr = dptr->next;
    }
    return result;
}

/*
  Synopsis           [main]
  Description        [Gather some stats about the music structure]
  Parameters         [No parameters are expected nor processed.]  
*/
int main(int argc, char **argv)
{
    int result;
	char readbuffer[LINE_SIZE];
	char string[LINE_SIZE];
	
	int fd[2], nbytes;
	signal(SIGTSTP,SIG_IGN);
	
	// Pipe creation
	if(pipe(fd)<0){
		perror("pipe creation");
		exit(EXIT_FAILURE);
	}
	// Child creation
	childpid = fork();
	if((childpid < 0)){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(childpid == 0){
		/* Slurp the data, if any problem is detected, bomb out */
		//printf("Hello! I am the child with pid %i and my parent has pid %i\n",getpid(),getppid());
		result = initialize_data(MUSIC_DATA_FILE);
		if (result != 0)
		{
		  printf("\n *** Error while reading the music data file.\n");
		  destroy_data();
		  return 1;
		}		
		close(fd[0]);
		//printf("Starting to write information in the pipe\n");
		snprintf(string, LINE_SIZE, "Duration of rumba songs: %d\nDuration of rock songs: %d\nDuration of rap songs: %d", calculate_duration(&rumba), calculate_duration(&rock), calculate_duration(&rap));
		nbytes = write(fd[1], string, (strlen(string)+1));
		if(nbytes == -1){
			perror("Error writing pipe");
		}
		destroy_data();
		_exit(EXIT_SUCCESS);
		
	} else {
		close(fd[1]);
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		if(nbytes != -1){
			printf("%s\n", readbuffer);
		} else {
			perror("Error reading pipe");
		}
		pid = wait(&status);
		exit(EXIT_SUCCESS); 
	}
    return 0;
}

/*---------------------------------------------------------------------------*/
/* Definition of other functions                                                        */
/*---------------------------------------------------------------------------*/
/*
  Synopsis           [Add one item into the a data structure.]
*/
void add_item(song new_song, category *category_ptr, char *disk_title){
	disk_ptr dptr = category_ptr->first;
	//printf("Adding song %s with duration %d to disk %s\n",new_song.title, new_song.duration,disk_title);
	if(dptr == NULL) { // Disk is the first
		disk_ptr new_disk = (disk_ptr) calloc(1,sizeof(disk));
		new_disk->disk_title = disk_title;
		new_disk->num_tracks = 1;
		new_disk->songs[0] = new_song;
		category_ptr ->first = new_disk; 
		category_ptr ->num_of_disks = 1;
	} else {
		// Try to find the disk
		while(dptr->next != NULL){
			if(strcmp(disk_title, dptr->disk_title) == 0){
				// Disk exists, so I add the song
				dptr->songs[dptr->num_tracks] = new_song;
				dptr->num_tracks = dptr->num_tracks + 1; // Assume that the limit will not be exceeded
				free(disk_title);	
				return;
			}
			dptr = dptr->next;
		}
		// Last disk to check. Otherwise add new disk
		if(strcmp(disk_title, dptr->disk_title) == 0){
				// Disk exists, so I add the song
				dptr->songs[dptr->num_tracks] = new_song;
				dptr->num_tracks = dptr->num_tracks + 1; // Assume that the limit will not be exceeded	
				free(disk_title);
				return;
		} else { // Add new disk
			disk_ptr new_disk = (disk_ptr) calloc(1,sizeof(disk));
			new_disk->disk_title = disk_title;
			new_disk->num_tracks = 1;
			new_disk->songs[0] = new_song;
			dptr->next = new_disk;
			category_ptr ->num_of_disks++;
		}
	}
}


/*
  Synopsis           [Loads the information into the data structures.]
*/
static int initialize_data(char *filename) {
	FILE *fd;
	char *buffer = NULL;;
	ssize_t readc=0;
	size_t n=0;
	char* token;
	char* rest;
	int duration;
	enum categories music_category;

	fd = fopen(filename, "r");
	
	if(fd==NULL){
		perror("Error when opening file");
		return -1;
	}
	
	// Read lines and initialize data
	while((readc=getline(&buffer,&n,fd)!=-1)){
		buffer[strcspn(buffer, "\r\n")] = 0;
		//printf("%s\n", buffer);
		// Get individual values with strtok
		rest = buffer;
		
		// Get category
		token = strtok_r(rest, ",", &rest);
		//printf("%s\n", token);
		
		if(strcmp(token,"rap") == 0) music_category = RAP;
		else if(strcmp(token,"rock") == 0) music_category = ROCK;
		else if(strcmp(token,"rumba") == 0) music_category = RUMBA;
		
		// Get disk
		token = strtok_r(rest, ",", &rest);
		char *disk_title = strdup(token);
		//printf("%s\n", token);
		
		// Get song title
		token = strtok_r(rest, ",", &rest);
		char *title = strdup(token);
		//printf("%s\n", token);
		
		// Get duration
		token = strtok_r(rest, ",", &rest);
		duration = atoi(token);
		//printf("%s\n", token);
		
		// Append to data structures
		song new_song;
		new_song.duration = duration;
		new_song.title = title;
		if(music_category == RAP) { /*printf("Adding to RAP\n");*/ add_item(new_song, &rap, disk_title); }
		if(music_category == ROCK) { /*printf("Adding to ROCK\n");*/ add_item(new_song, &rock, disk_title); }
		if(music_category == RUMBA) { /*printf("Adding to RUMBA\n");*/ add_item(new_song, &rumba, disk_title); }
	}
	free(buffer);
	
	//printf("Finished reading file\n");
	
	if(fclose(fd)!=0){
		perror("Error when closing file");
		return -1;
	}
	return 0;
}

/*
  Synopsis           [Destroy the data created]
  Description        [Invoke destroy_category for each category]
  SideEffects        [All created data structures are freed.]
*/
static void destroy_data() { 
	destroy_category(&rap);
	destroy_category(&rock);
	destroy_category(&rumba);
}

/*
  Synopsis           [Destroy the data for one category]
  Description [Traverse the disks deallocating the titles and the disk itself.]
  SideEffects        [The linked list and its elements are removed.]
*/
static void destroy_category(category *category_ptr) {
	disk_ptr dptr;
	disk_ptr aux;
    int i;

    /* Get a pointer to traverse the list of disks */
    dptr = category_ptr->first;
	if (dptr == NULL)
    {
      return;
    }

    /* Loop over the list and accumulate durations */
    while (dptr != NULL)
    {
      for (i = 0; i < dptr->num_tracks; i++)
      {
        free(dptr->songs[i].title);
      }
	  free(dptr->disk_title);
	  aux = dptr;
      dptr = dptr->next;
	  free(aux);
    }
    return;
	
}
 
