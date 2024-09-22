cmake_minimum_required (VERSION 3.8)

project("gmmk")

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

add_subdirectory("CSharp")
add_subdirectory("Cpp")

add_dependencies(gmmk-cpp gmmk-csharp)

add_custom_target(post_build ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/gmmk/"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-csharp> "${Output_Bin_Dir}"
)