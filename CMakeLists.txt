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

# Include ExternalProject module
include(ExternalProject)

# Define Assimp installation directory
set(ASSIMP_INSTALL_DIR ${CMAKE_SOURCE_DIR}/external/assimp-install)

# Add ExternalProject for Assimp
ExternalProject_Add(assimp_project
    PREFIX ${CMAKE_SOURCE_DIR}/external/assimp-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/assimp
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${ASSIMP_INSTALL_DIR} -DASSIMP_WARNINGS_AS_ERRORS=OFF
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --config Release --target install
)

# Ensure that the Assimp project is built before linking
add_dependencies(${PROJECT_NAME} assimp_project)

# Include Assimp headers
include_directories(${ASSIMP_INSTALL_DIR}/include)

# Detect compiler and set appropriate Assimp library names
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "MinGW")
    # MinGW/GCC naming convention
    set(ASSIMP_LIBRARY_NAME "libassimp.dll.a")
    set(ASSIMP_DLL_NAME "libassimp-5.dll")
    set(COMPILER_TYPE "MinGW/GCC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC naming convention
    set(ASSIMP_LIBRARY_NAME "assimp-vc143-mt.lib")
    set(ASSIMP_DLL_NAME "assimp-vc143-mt.dll")
    set(COMPILER_TYPE "MSVC")
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Set library paths (files will be created by ExternalProject during build)
set(ASSIMP_LIB_PATH "${ASSIMP_INSTALL_DIR}/lib/${ASSIMP_LIBRARY_NAME}")
set(ASSIMP_DLL_PATH "${ASSIMP_INSTALL_DIR}/bin/${ASSIMP_DLL_NAME}")

message(STATUS "Configured to use ${COMPILER_TYPE} Assimp libraries:")
message(STATUS "  Library: ${ASSIMP_LIB_PATH}")
message(STATUS "  DLL: ${ASSIMP_DLL_PATH}")
message(STATUS "  (Files will be built by ExternalProject)")

# Link pre-built Assimp library
target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIB_PATH})

# Add build-time validation for Assimp libraries
add_custom_target(validate_assimp
    COMMAND ${CMAKE_COMMAND} -E echo "Validating Assimp libraries for ${COMPILER_TYPE}..."
    COMMAND ${CMAKE_COMMAND} -E echo "Checking: ${ASSIMP_LIB_PATH}"
    COMMAND ${CMAKE_COMMAND} -E echo "Checking: ${ASSIMP_DLL_PATH}"
    DEPENDS assimp_project
)
add_dependencies(${PROJECT_NAME} validate_assimp)

# Copy Assimp DLL to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${ASSIMP_DLL_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Specify the output directory for binaries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)