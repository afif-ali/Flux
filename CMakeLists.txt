cmake_minimum_required(VERSION 4.4)

project(Flux)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/glfw-3.4)

include_directories(${PROJECT_NAME} lib/glad/include/ lib/glfw-3.4/include/lib/imgui lib/ src/)


file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE IMGUI_SOURCES "/lib/imgui/*.cpp")
# Add WIN32 as an argument to hide console
add_executable(${PROJECT_NAME}  ${PROJECT_SOURCES} ${IMGUI_SOURCES} lib/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

get_filename_component(MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)

set(MINGW_DLLS
    "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
    "${MINGW_BIN_DIR}/libstdc++-6.dll"
    "${MINGW_BIN_DIR}/libwinpthread-1.dll"
)


add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${MINGW_DLLS}
    ${CMAKE_BINARY_DIR}
)

add_dependencies(${PROJECT_NAME} copy_resources)