#include <iostream>
#include <gtest/gtest.h>
#include <dirent.h>
#include "gtest_chroot.h"

class TestChroot : public ::testing::Test {
};

TEST_D(TestChroot, run_in_chroot, {
    EXPECT_EQ(2, list_directory("/"));
    touch("/file");
    EXPECT_EQ(3, list_directory("/"));
})

TEST_F(TestChroot, run_in_root) {
    EXPECT_NE(0, list_directory("/"));
}

