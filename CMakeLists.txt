cmake_minimum_required(VERSION 3.10.0)
project(haven)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -O2 -march=native -s -fvisibility=hidden -flto -fwhole-program -Wl,--strip-all")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --no-gnu-unique -fno-rtti -std=c++17")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/config.hpp")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(haven ${SOURCES})
