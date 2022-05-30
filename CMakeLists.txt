cmake_minimum_required(VERSION 3.22)
project(GTEST_EXT)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(GTEST_EXT test_chroot.cpp filetools.c filetools.h gtest_chroot.h)
target_link_libraries(
        GTEST_EXT
        gtest_main
        cap
)
gtest_discover_tests(GTEST_EXT)
