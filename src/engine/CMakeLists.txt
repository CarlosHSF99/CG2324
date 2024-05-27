cmake_minimum_required(VERSION 3.27)

project(engine)

add_executable(${PROJECT_NAME}
        main.cpp
        scene/group.cpp
        scene/world.cpp
        scene/camera.cpp
        scene/window.cpp
        scene/model/model.cpp
        scene/transform/timed_translate.cpp
        scene/transform/translate.cpp
        scene/transform/scale.cpp
        scene/transform/timed_rotate.cpp
        scene/transform/rotate.cpp
        scene/model/color/color.cpp
        scene/model/color/color_rgb.cpp
        scene/model/vertex_buffers.cpp
        scene/light/light.cpp
        scene/light/directional_light.cpp
        scene/light/spot_light.cpp
        scene/light/point_light.cpp
        scene/model/texture.cpp
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
