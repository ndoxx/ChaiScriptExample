cmake_minimum_required(VERSION 3.10)

project(chai VERSION 1.0.0 DESCRIPTION "chai")

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE MinSizeRel)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(cotire)
include(standard_settings)
include(toolchain_clang_local)
include(compiler_warnings) # Hardcore warnings
include(sanitizers)

# Interface library to enable us to pass on options to multiple projects
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
enable_sanitizers(project_options)

# Global definitions
add_definitions(-DW_DEBUG)
add_definitions(-DW_ENABLE_ASSERT)
add_definitions(-DLOGGING_ENABLED=1)


subdirs(source)
