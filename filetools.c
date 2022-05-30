#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdbool.h>
#include <ftw.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

int rmrf(const char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

int touch(const char *path)
{
    int fd = open(path, O_WRONLY | O_CREAT);
    if (fd == -1)
    {
        return -1;
    }
    return close(fd);
}

int list_directory(const char *rootdir) {
    int total = 0;
    DIR *dir = opendir(rootdir);
    while (true) {
        struct dirent *dirent = readdir(dir);
        if (dirent == NULL) {
            break;
        }
        printf("%s\n", dirent->d_name);
        total++;
    }
    return total;
}