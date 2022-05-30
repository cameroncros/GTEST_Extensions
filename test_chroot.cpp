#include <iostream>
#include <gtest/gtest.h>
#include <dirent.h>
#include <syscall.h>
#include <fcntl.h>
#include "gtest_chroot.h"

class TestChroot : public ::testing::Test {
};

TEST_D(TestChroot, run_in_chroot, {
    EXPECT_EQ(2, list_directory("/"));
    int fd = syscall(SYS_open, "/file", O_CREAT);
    syscall(SYS_write, "hello", 6);
    syscall(SYS_close, fd);
    EXPECT_EQ(3, list_directory("/"));
})

TEST_F(TestChroot, run_in_root) {
    EXPECT_NE(0, list_directory("/"));
}

