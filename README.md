# CMake C++ GLFW Development Workspace for Visual Studio Code

This repository is a VS Code workspace template for a C++ application that uses the [GLFW source](https://github.com/glfw/glfw) as a git submodule and [CMake](https://cmake.org/) for building. The [window.c](https://github.com/glfw/glfw/blob/master/tests/window.c) demo application from the official GLFW source was used as a demo `main.cpp`.

## Motivation

I created this project because at the time I wanted some simple solution using CMake to get quickly started with glfw while compiling the libraries myself.

## Prerequisites

- [Git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- [Visual Studio Code](https://code.visualstudio.com/) (optional)
- C and C++ compiler (e.g., MinGW for Windows)

## Usage

### Command Line

1. Clone the repository and initialize submodules:
    ```sh
    git clone --recurse-submodules <repository_url>
    cd <repository_folder>
    ```

2. Configure and build the project:
    ```sh
    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build --config Debug --target all -j 18
    ```

### Visual Studio Code

1. Open the project folder in VS Code.
2. Install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension.
3. Configure the project by running the `CMake: Configure` command from the Command Palette (`Ctrl+Shift+P`).
4. Build the project by running the `CMake: Build` command from the Command Palette.

## Notes

- Ensure that the `glfw` submodule is properly initialized and updated.
- The `glad` headers are included from the `glfw/deps/glad` directory.
- The output binaries will be located in the `build/bin` directory.