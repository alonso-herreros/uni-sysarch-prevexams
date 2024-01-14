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
static void destroy_category(category *category_ptr);

// Calculates the duration of all the songs in a category
int calculate_duration(category *category_ptr){ ... }
int main(int argc, char **argv){ // SECTION 1.3 }
void add_item(song new_song, category *category_ptr, char *disk_title){ // SECTION 1.1
}
static int initialize_data(char *filename) { // SECTION 1.2 }

// Destroy the data created
static void destroy_data() {...}
// Destroy the data for one category
static void destroy_category(category *category_ptr) {...}
