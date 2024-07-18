cmake_minimum_required(VERSION 3.10)
project(Textbook-Fetch)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(Textbook-Fetch src/main.cpp src/downloader.cpp)

target_link_libraries(Textbook-Fetch ${CURL_LIBRARIES})