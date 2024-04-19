cmake_minimum_required(VERSION 3.27)

project(engine)

add_executable(${PROJECT_NAME}
        main.cpp
        group.cpp
        transform.cpp
        xml_world_loader.cpp
        world.cpp
        camera.cpp
        window.cpp
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

target_link_libraries(
        ${PROJECT_NAME}
        utils
        deps
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
)
