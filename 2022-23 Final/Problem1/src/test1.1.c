#define TEST
#include "main.c"

int main(int argc, char **argv)
{
    char *disk_title = "TestDisk";
    char *disk_title2 = "TestDisk2";
    song new_song;
    new_song.duration = 12;
    new_song.title = "testSong";
    song new_song2;
    new_song2.duration = 13;
    new_song2.title = "testSong2";
    song new_song3;
    new_song3.duration = 14;
    new_song3.title = "testSong3";

    add_item(new_song, &rap, disk_title);
    printf("\n");
    add_item(new_song, &rap, disk_title);
    printf("\n");
    add_item(new_song2, &rap, disk_title);
    printf("\n");
    add_item(new_song3, &rap, disk_title2);
    printf("\n");
    printf("%s\n", rap.first->songs[0].title);
    printf("%s\n", rap.first->songs[1].title);
    printf("%s\n", rap.first->next->songs[0].title);

    return 1;
}
