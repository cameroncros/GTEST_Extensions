#ifndef GTEST_EXT_FILETOOLS_H
#define GTEST_EXT_FILETOOLS_H

extern "C" {

int rmrf(const char *path);
int touch(const char *path);
int list_directory(const char *path);

};

#endif //GTEST_EXT_FILETOOLS_H
