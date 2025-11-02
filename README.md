# CMake C++ GLFW Development Workspace for Visual Studio Code

This repository is a VS Code workspace template for a C++ application that uses the [GLFW source](https://github.com/glfw/glfw) as a git submodule and [CMake](https://cmake.org/) for building. The demo application is based on my current progress on [learnopengl tutorial](https://learnopengl.com).

## Motivation

I created this project for my convenience using CMake to get quickly started with glfw and the necessary libraries in order to follow the tutorial.

I ended up including
- glfw *- cross-platform window creation and OpenGL context management*
- glm *- mathematics library for 3D transformations and linear algebra*
- imgui *- immediate mode GUI for debugging controls and real-time parameter adjustment*
- assimp *- 3D model loading library supporting multiple file formats*

**current snapshot**
![assimp 3D model loading](images/snapshot.png)


## Prerequisites

- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- [Visual Studio Code](https://code.visualstudio.com/) (optional)
- C and C++ compiler (e.g., MinGW for Windows or MSVC)

### How to get started

1. Clone the repository and initialize submodules:
    ```sh
    git clone --recurse-submodules <repository_url>
    cd <repository_folder>
    ```

2. Configure and build the project:
    ```sh
    cmake -S . -B build -G "MinGW Makefiles" # -G optional MSVC also works
    cmake --build build --config Debug --target all -j 18
    ```

## Notes

- Ensure that the `glfw` submodule is properly initialized and updated.
- The `glad` headers are included from the `glfw/deps/glad` directory.
- The output binaries will be located in the `build/bin` directory and it **must be run from 2 levels nested in there**.