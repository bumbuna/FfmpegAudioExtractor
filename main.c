#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  if(argc != 2) {
      fprintf(stderr, "usage %s <directory>\n", argv[0]);
      return -1;
    }
    DIR *dirPtr = opendir(argv[1]);
    chdir(argv[1]);
    if(dirPtr == NULL) {
        perror("openDir()");
        exit(EXIT_FAILURE);
    }
    struct dirent *currDir;
    while((currDir = readdir(dirPtr))) {
        if(currDir->d_type == DT_DIR) continue;
        char *mp3File = strdup(currDir->d_name);
        char *c = &mp3File[strlen(mp3File)];
        while(*c != '.') {
            c--;
        }
        if(strcmp(".mp4", c) && strcmp(".mkv", c)) continue;
        strcpy(c+1, "mp3");
        int f;
        if((f = open(mp3File, O_RDONLY)) != -1) {
            printf("%s already exists\n", mp3File);
            close(f);
            continue;
        }
        if(fork() == 0) {
            execv("/usr/bin/ffmpeg", (char *[]){
                "/usr/bin/ffmpeg",
                "-v",
                "quiet",
                "-i",
                currDir->d_name,
                mp3File,
                0
            });
        } else {
            int retcode = 0;
            wait(&retcode);
            if(retcode == 0) {
                printf("%s audio extracted successfully to %s.\n", currDir->d_name, mp3File);
            } else {
                fprintf(stderr, "ffmpeg exited with error %d.\n", retcode);
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}
