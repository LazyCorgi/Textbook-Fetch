cmake_minimum_required(VERSION 3.10)
project(Textbook-Fetch)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(Textbook-Fetch src/main.cpp src/downloader.cpp)
target_link_libraries(Textbook-Fetch ${CURL_LIBRARIES} stdc++fs)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    add_executable(Textbook-Fetch.exe src/main.cpp src/downloader.cpp)
    target_link_libraries(Textbook-Fetch.exe ${CURL_LIBRARIES} )
endif()