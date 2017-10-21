cmake_minimum_required(VERSION 3.1)
project(retroportal VERSION 0.1.0)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/extlibs/glfw)

include_directories(
    ${CMAKE_SOURCE_DIR}/extlibs/glfw/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/glad.c

    ${CMAKE_SOURCE_DIR}/src/retro/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/retro/impl/GLFW/ApplicationImpl_GLFW.cpp ${CMAKE_SOURCE_DIR}/src/retro/impl/GLFW/ApplicationImpl_GLFW.h

    ${CMAKE_SOURCE_DIR}/src/retro/Log.cpp
    ${CMAKE_SOURCE_DIR}/src/retro/impl/ANSI/LogImpl_ANSI.cpp ${CMAKE_SOURCE_DIR}/src/retro/impl/ANSI/LogImpl_ANSI.h

    ${CMAKE_SOURCE_DIR}/src/retro/Mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/MeshImpl_GL.cpp ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/MeshImpl_GL.h

    ${CMAKE_SOURCE_DIR}/src/retro/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/RendererImpl_GL.cpp ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/RendererImpl_GL.h

    ${CMAKE_SOURCE_DIR}/src/retro/ShaderProgram.cpp
    ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/ShaderProgramImpl_GL.cpp ${CMAKE_SOURCE_DIR}/src/retro/impl/GL/ShaderProgramImpl_GL.h

    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw)