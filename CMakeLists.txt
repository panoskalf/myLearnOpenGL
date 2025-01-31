cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

# Set the project name
project(MyProject)

# Add the GLFW subdirectory
add_subdirectory(external/glfw)

# Include directories
include_directories(include)

# Add the glad source file
add_library(glad STATIC src/glad.c)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the GLFW and glad libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

# Add the GLM subdirectory and disable tests and installation
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glm)

# Include GLM headers
include_directories(external/glm)

# Add ImGui
include_directories(external/imgui)
include_directories(external/imgui/backends)  # Include ImGui backends
include_directories(external/glfw/include)    # Include GLFW headers for ImGui backend
file(GLOB IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

# Link ImGui library
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

# Specify the output directory for binaries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)