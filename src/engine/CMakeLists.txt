cmake_minimum_required(VERSION 3.27)

project(engine)

add_executable(${PROJECT_NAME}
        main.cpp
        group.cpp
        world.cpp
        camera.cpp
        window.cpp
        model.cpp
        transform/timed_translate.cpp
        transform/translate.cpp
        transform/scale.cpp
        transform/timed_rotate.cpp
        transform/rotate.cpp
        color.cpp
        color_rgb.cpp
        vertex_buffers.cpp
        light/light.cpp
        light/directional_light.cpp
        light/spot_light.cpp
        light/point_light.cpp
        texture.cpp
)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})
link_libraries(${IL_LIBRARIES})

target_link_libraries(
        ${PROJECT_NAME}
        utils
        deps
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${IL_LIBRARIES}
)
