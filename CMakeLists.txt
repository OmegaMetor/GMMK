cmake_minimum_required (VERSION 3.21)

project("gmmk")

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

add_subdirectory(init)
add_subdirectory(patcher)

target_link_libraries(gmmk-init PRIVATE gmmk-patcher)

add_custom_target(post_build ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/mods/"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-init> "${Output_Bin_Dir}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-patcher> "${Output_Bin_Dir}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:gmmk-patcher>/ijwhost.dll "${Output_Bin_Dir}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:gmmk-patcher>/gmmk-patcher.runtimeconfig.json "${Output_Bin_Dir}"
)

install(
    DIRECTORY ${Output_Bin_Dir}
    DESTINATION "C:/Program\ Files\ (x86)/Steam/steamapps/common/Will You Snail" # NOTE: This can be changed to your game directory for development,
    CONFIGURATIONS Debug
)