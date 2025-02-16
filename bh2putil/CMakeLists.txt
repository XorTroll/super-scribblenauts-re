cmake_minimum_required(VERSION 3.13)

project(bh2putil)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    include
    ../libobjectnaut/include
    ../../editwl/libeditwl/include
)

set(SOURCES
    source/main.cpp
    ../libobjectnaut/source/objnaut/fs/fs_FileSystem.cpp
    ../libobjectnaut/source/objnaut/fmt/fmt_TextList.cpp
    ../libobjectnaut/source/objnaut/fmt/fmt_InputDictionary.cpp
    ../../editwl/libeditwl/source/twl/fs/fs_File.cpp
    ../../editwl/libeditwl/source/twl/util/util_Compression.cpp
    ../../editwl/libeditwl/source/twl/gfx/gfx_Conversion.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -Wpedantic)
