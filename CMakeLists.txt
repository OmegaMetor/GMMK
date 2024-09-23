cmake_minimum_required (VERSION 3.8)

project("gmmk")

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

add_subdirectory(init)

add_custom_target(post_build ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/gmmk/"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-init> "${Output_Bin_Dir}"
)

install(
    DIRECTORY ${Output_Bin_Dir}
    DESTINATION "C:/Program\ Files\ (x86)/Steam/steamapps/common/Will You Snail" # NOTE: This can be changed to your game directory for development,
    CONFIGURATIONS Debug
)