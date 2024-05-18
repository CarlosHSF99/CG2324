cmake_minimum_required(VERSION 3.27)

project(generator)

add_executable(${PROJECT_NAME}
        main.cpp
        plane.cpp
        box.cpp
        sphere.cpp
        cone.cpp
        patch_model.cpp
        model.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        utils
        deps
)
