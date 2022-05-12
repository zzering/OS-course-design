#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LEN (256)

static void trave_dir(char* path) {
    DIR *d = NULL;
    struct dirent *dp = NULL;
    struct stat st;    
    char p[MAX_PATH_LEN] = {0};
    
    if(stat(path, &st) < 0 || !S_ISDIR(st.st_mode)) {
        printf("invalid path: %s\n", path);
        return;
    }
    if(!(d = opendir(path))) {
        printf("opendir[%s] error: %m\n", path);
        return;
    }
    while((dp = readdir(d)) != NULL) {
        if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
            continue;
        snprintf(p, sizeof(p) - 1, "%s/%s", path, dp->d_name);
        stat(p, &st);
        if(!S_ISDIR(st.st_mode)) {
            printf("%s\n", dp->d_name);
        } else {
            printf("%s/\n", dp->d_name);
            trave_dir(p);
        }
    }
    closedir(d);
    return;
}

int main(int argc, char **argv)
{   
    char *path = NULL;
    if (argc != 2) {
        //type ./a.out +specific directory to traverse the directory you typed
        //or use the default directory ../
        printf("the directory to travese is: %s \n\n", argv[0]);
        path = "../";
    } else {
        path = argv[1];
        printf("the directory to travese is: %s \n\n", argv[1]);
    }
    trave_dir(path);
    return 0;
}


