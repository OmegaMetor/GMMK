cmake_minimum_required (VERSION 3.8)


enable_language(CSharp)

# It really doesn't need to be shared, but if it isn't then the post build copy command throws a fit about the .lib not existing :|
file(GLOB "ModelsSrc"
     "src/Models/*.cs"
)

add_library(gmmk-csharp SHARED "src/ModLoader.cs" "src/DependencySort.cs" "${ModelsSrc}")

set_property(TARGET gmmk-csharp
    PROPERTY VS_PACKAGE_REFERENCES "System.Text.Json;"
)

set_property(TARGET gmmk-csharp PROPERTY DOTNET_SDK "Microsoft.NET.Sdk")
set_property(TARGET gmmk-csharp PROPERTY DOTNET_TARGET_FRAMEWORK "net8.0")

#add_custom_command(TARGET gmmk-csharp POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
#    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/gmmk/"
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gmmk-csharp> "${Output_Bin_Dir}"
#)