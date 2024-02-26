cmake_minimum_required (VERSION 3.8)


enable_language(CSharp)

# It really doesn't need to be shared, but if it isn't then the post build copy command throws a fit about the .lib not existing :|
add_library(gmmk-csharp SHARED "base.cs")


add_custom_command(TARGET gmmk-csharp POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/gmmk/"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-csharp> "${Output_Bin_Dir}"
)