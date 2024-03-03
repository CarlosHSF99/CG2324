cmake_minimum_required(VERSION 3.27)

project(cg2324)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/generator)
add_subdirectory(src/engine)
add_subdirectory(src/utils)

target_include_directories(generator PUBLIC include)
target_include_directories(engine PUBLIC include)
target_include_directories(utils PUBLIC include)
