cmake_minimum_required (VERSION 3.21)

add_library(gmmk-patcher SHARED "src/patcher.cpp")

set_target_properties(gmmk-patcher PROPERTIES COMMON_LANGUAGE_RUNTIME "netcore")

set_target_properties(gmmk-patcher PROPERTIES DOTNET_TARGET_FRAMEWORK "net8.0")