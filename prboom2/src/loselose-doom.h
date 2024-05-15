#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIR_DEPTH 5
#define MAX_PATH_LENGTH 200	//No mallocs are made


//Since random_file doesnt follow links, getting inside /usr/lib or /usr/bin is less common than /etc, for instance
//A bunch of interesting directories are saved and random_file will pick between one of those to start from
#define STRT_DIRS 4




void random_file(char *return_path);
void remove_random(char *deleted_path);
