cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

# Set the project name
project(MyProject)

# Add the GLFW subdirectory
add_subdirectory(glfw)

# Include the dependencies folder
include_directories(glfw/deps)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the GLFW library
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Specify the output directory for binaries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)