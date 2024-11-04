cmake_minimum_required (VERSION 3.21)

add_library(gmmk-init SHARED "src/dllmain.cpp" "src/proxydll.cpp")

set_target_properties(gmmk-init PROPERTIES
    OUTPUT_NAME "dbgcore"
    CXX_STANDARD 20
)

include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook.git"
    GIT_TAG "master"
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable( minhook )

target_link_libraries (gmmk-init PRIVATE minhook)