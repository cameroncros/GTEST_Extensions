#ifndef GTEST_EXT_GTEST_CHROOT_H
#define GTEST_EXT_GTEST_CHROOT_H

#include <sys/capability.h>
#include "filetools.h"

#define TEST_D(test_fixture, test_name, code)                                                                        \
    TEST_F(test_fixture, test_name)                                                                                  \
{                                                                                                                    \
    cap_t cap = cap_get_proc();                                                                                      \
    cap_flag_value_t chroot_allowed;                                                                                 \
    cap_get_flag(cap, CAP_SYS_CHROOT, CAP_EFFECTIVE, &chroot_allowed);                                               \
    if (getuid() != 0 && !chroot_allowed) {                                                                          \
        GTEST_SKIP() << "Not permitted to chroot. Run as root or enable CAP_SYS_CHROOT";                             \
    }                                                                                                                \
    char path[PATH_MAX] = {};                                                                                        \
    const char* tmppath = "/tmp/";                                                                                   \
    ASSERT_NE(nullptr, strcpy(path, tmppath));                                                                       \
    ASSERT_NE(nullptr, strcat(path, "testdir-XXXXXX"));                                                              \
    ASSERT_NE(nullptr, mkdtemp(path));                                                                               \
    int pid = fork();                                                                                                \
    if (pid == 0)                                                                                                    \
    {                                                                                                                \
        if (0 != chroot(path))                                                                                       \
        {                                                                                                            \
            FAIL() << "Failed to chroot to [" << path << "] - " << strerror(errno);                                  \
            exit(::testing::Test::HasFailure());                                                                     \
        }                                                                                                            \
        {                                                                                                            \
            code                                                                                                     \
        }                                                                                                            \
        exit(::testing::Test::HasFailure());                                                                         \
    }                                                                                                                \
    else                                                                                                             \
    {                                                                                                                \
        int status = 0;                                                                                              \
        ASSERT_EQ(pid, wait(&status));                                                                               \
        if (!WEXITSTATUS(status))                                                                                    \
        {                                                                                                            \
             rmrf(path);                                                                                             \
        }                                                                                                            \
        else                                                                                                         \
        {                                                                                                            \
             FAIL() << "Test ran in " << path;                                                                       \
        }                                                                                                            \
    }                                                                                                                \
}

#endif //GTEST_EXT_GTEST_CHROOT_H
