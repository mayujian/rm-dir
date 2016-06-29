#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
 
#define _MAXDIR_   256
char dirname[_MAXDIR_], rootdir[_MAXDIR_];
 
void del_dir(char *path)
{
    DIR* dp = NULL;
    DIR* dpin = NULL;
    char *pathname = (char*)malloc(_MAXDIR_);
    struct dirent* dirp;
    dp = opendir(path);
    if(dp == NULL)
    {
        printf("%s\n", "your input directory is not exist!");
        return;
    }
         
    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".") == 0)
            continue;
        strcpy(pathname, path);
        strcat(pathname, "\\");
        strcat(pathname, dirp->d_name);
        dpin = opendir(pathname);
        if(dpin != NULL)
            del_dir(pathname);
        else
            remove(pathname);
        strcpy(pathname, "");
        closedir(dpin);
        dpin = NULL;
    }
    rmdir(path);
    closedir(dp);
    free(pathname);
    pathname = NULL;
    dirp = NULL;
}
 
long currentTimeByMilles()
{
    clock_t rawtime;
    rawtime = clock();
    return rawtime;
}
 
int main()
{
    printf("%s", "Please input directory:");
    scanf("%s", dirname);
    long initTime = currentTimeByMilles();
    del_dir(dirname);
    long currentTime = currentTimeByMilles();
    printf("Use time:%d\n", currentTime-initTime);
    return 0;
}
