cmake_minimum_required (VERSION 3.8)


add_library(gmmk-cpp SHARED "src/dllmain.cpp" "src/proxydll.cpp" "src/modloader.cpp")
target_include_directories(gmmk-cpp PRIVATE "include/")

set_target_properties(gmmk-cpp PROPERTIES COMMON_LANGUAGE_RUNTIME "")

set_target_properties(gmmk-cpp PROPERTIES OUTPUT_NAME "dbgcore")

add_custom_command(TARGET gmmk-cpp POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/gmmk/mods"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-cpp> ${Output_Bin_Dir}
)