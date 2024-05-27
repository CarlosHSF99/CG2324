cmake_minimum_required(VERSION 3.27)

project(generator)

add_executable(${PROJECT_NAME}
        main.cpp
        models/plane.cpp
        models/box.cpp
        models/sphere.cpp
        models/cone.cpp
        models/patch_model.cpp
        models/model.cpp
)

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})
link_libraries(${IL_LIBRARIES})

target_link_libraries(
        ${PROJECT_NAME}
        utils
        deps
        ${IL_LIBRARIES}
)
