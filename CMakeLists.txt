cmake_minimum_required(VERSION 3.0)

project(GreedySnake VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(GreedySnake ${SOURCES})

target_include_directories(GreedySnake PUBLIC src)
target_link_libraries(GreedySnake PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

file(COPY "assets" DESTINATION "${CMAKE_BINARY_DIR}/${NAME}")

