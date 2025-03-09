cmake_minimum_required(VERSION 3.13)

project(scribbletool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIBOBJNAUT_PATH ../libobjectnaut)
set(LIBEDITWL_PATH $ENV{LIBEDITWL_PATH})

include_directories(
    include
    ${LIBOBJNAUT_PATH}/include
    ${LIBEDITWL_PATH}/include
)

set(SOURCES
    source/main.cpp
    source/cli/cli_PrintMisc.cpp
    source/cli/cli_PrintObject.cpp
    source/cli/cli_ExportTexture.cpp
    source/cli/cli_ObjectsHtml.cpp
    ${LIBOBJNAUT_PATH}/source/objnaut/io/io_FileSystem.cpp
    ${LIBOBJNAUT_PATH}/source/objnaut/fmt/fmt_Dictionary.cpp
    ${LIBOBJNAUT_PATH}/source/objnaut/fmt/fmt_Object.cpp
    ${LIBOBJNAUT_PATH}/source/objnaut/fmt/fmt_Adjective.cpp
    ${LIBEDITWL_PATH}/source/twl/fs/fs_File.cpp
    ${LIBEDITWL_PATH}/source/twl/util/util_Compression.cpp
    ${LIBEDITWL_PATH}/source/twl/gfx/gfx_Conversion.cpp
)

file(READ data/index.html index_html)
file(READ data/search.js search_js)
file(READ data/obj.html obj_html)
configure_file(data/data.h.in ${CMAKE_SOURCE_DIR}/include/data.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -Wpedantic)
