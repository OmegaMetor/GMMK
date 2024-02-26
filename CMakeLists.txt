cmake_minimum_required (VERSION 3.8)

project("gmmk")

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

add_subdirectory("CSharp")
add_subdirectory("Cpp")

add_dependencies(gmmk-cpp gmmk-csharp)