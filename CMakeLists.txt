cmake_minimum_required(VERSION 3.2)
project(FFS)

# set default build directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)


#---------------------------------L I B R A R Y---------------------------------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-varargs -fPIC -Ofast -msse4.1")

include_directories(
    ${INCLUDE_DIRECTORIES}
    src
)

set(FFS_SRC
    src/FFS/Definitions.c
    src/FFS/Length.c
)

add_library(ffs STATIC ${FFS_SRC})

#-----------------------------------T E S T S-----------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wno-varargs -fPIC")

include_directories(
    ${INCLUDE_DIRECTORIES}
    src
    # for testing
    ${CMAKE_BINARY_DIR}/../../ArcaneCore/ArcaneCore/src/cpp
)
link_directories(
    ${LINK_DIRECTORIES}
    # for testing
    ${CMAKE_BINARY_DIR}/../../ArcaneCore/ArcaneCore/build/linux_x86
)

set(FFS_TEST_SRC
    tests/TestMain.cpp
    tests/Length_TestSuite.cpp
)

add_executable(tests ${FFS_TEST_SRC})

target_link_libraries(tests
    arcanecore_test
    arcanecore_io
    arcanecore_base
    ffs
)
