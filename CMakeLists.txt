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

# Specify the output directory for binaries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)