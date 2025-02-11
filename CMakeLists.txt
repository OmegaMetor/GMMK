cmake_minimum_required (VERSION 3.21)

project("gmmk")

add_library(gmmk-init SHARED "src/dllmain.cpp" "src/proxydll.cpp")

set_target_properties(gmmk-init PROPERTIES
    OUTPUT_NAME "dbgcore"
    CXX_STANDARD 20
)

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook.git"
    GIT_TAG "master"
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable( minhook )

target_link_libraries (gmmk-init PRIVATE minhook)

add_custom_target(post_build ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/mods/"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-init> "${Output_Bin_Dir}"
)

install(
    DIRECTORY ${Output_Bin_Dir}
    DESTINATION "C:/Program\ Files\ (x86)/Steam/steamapps/common/Will You Snail" # NOTE: This can be changed to your game directory for development,
    CONFIGURATIONS Debug
)
