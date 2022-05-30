#ifndef GTEST_EXT_GTEST_CHROOT_H
#define GTEST_EXT_GTEST_CHROOT_H

#include "filetools.h"

#define TEST_D(test_fixture, test_name, code)                                  \
    TEST_F(test_fixture, test_name)                                            \
{                                                                              \
    char path[PATH_MAX] = {};                                                  \
    const char* tmppath = "/tmp/";                                             \
    ASSERT_NE(nullptr, strcpy(path, tmppath));                                 \
    ASSERT_NE(nullptr, strcat(path, "testdir-XXXXXX"));                        \
    ASSERT_NE(nullptr, mktemp(path));                                          \
    ASSERT_EQ(0, mkdir(path, S_IRWXO | S_IRWXG | S_IRWXU)) << path;            \
    int pid = fork();                                                          \
    if (pid == 0)                                                              \
    {                                                                          \
        ASSERT_EQ(0, chroot(path)) << path << " - " << strerror(errno);        \
        {                                                                      \
            code                                                               \
        }                                                                      \
        exit(::testing::Test::HasFailure());                                   \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        int status = 0;                                                        \
        ASSERT_EQ(pid, wait(&status));                                         \
        if (WIFEXITED(status))                                                 \
        {                                                                      \
             rmrf(path);                                                       \
        }                                                                      \
        else                                                                   \
        {                                                                      \
             FAIL() << "Test ran in " << path;                                 \
        }                                                                      \
    }                                                                          \
}

#endif //GTEST_EXT_GTEST_CHROOT_H
