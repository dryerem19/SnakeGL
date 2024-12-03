<!-- PROJECT LOGO -->
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Snake OpenGL Game</h3>

  <p align="center">
    A simple snake game in C++ and modern OpenGL
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]]

This project is a classic Snake game implemented in the C++ programming language using the OpenGL graphics library. The goal of the project is to demonstrate the basic principles of working with OpenGL and creating an interactive 2D game.

Project objectives:

* Practical application of OpenGL and C++ knowledge.
* Creating a functional and fun game.
* Demonstration of the basics of developing 2D games in C++ using OpenGL.

### Controls

| Keyboard | Action     |
|:---------|:----------:|
| ESC      | Game pause |
| W        | Move Up    |
| S        | Move Down  |
| A        | Move Left  |
| D        | Move Right |

### Build

### Installing the necessary tools 
1. CMake: Download and install CMake from the official website: https://cmake.org/download. Add CMake to the PATH environment variable.
2. Visual Studio (optional, but recommended for Windows): If you are going to compile a project on Windows, you will need Visual Studio with the C++ compiler installed. You can use the free version of the Community Edition.
3. vcpkg: Download and install vcpkg following the instructions on the official website: https://github.com/microsoft/vcpkg. Add vcpkg to the PATH environment variable.

### Build project
1. Clone the repo
   ```sh
   git clone https://github.com/dryerem19/SnakeGL
   ```
2. Navigate to the root directory of the project and run the following command
   ```sh
   vcpkg integrate install
   vcpkg install --recurse
   ```
4. Open project folder in Visual Studio 2022
5. Run build project

## Used libraries
* **[GLAD](https://github.com/Dav1dde/glad/)**: OpenGL function loader.  Provides platform-independent access to OpenGL functions.
* **[GLFW 3](http://www.glfw.org/)**: Cross-platform windowing library. Handles window creation, input, and OpenGL context management.
* **[GLM](https://github.com/icaven/glm/)**: OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
* **[Dear ImGui](https://github.com/ocornut/imgui/)**: Immediate Mode GUI library.  A simple and efficient way to create in-application user interfaces.

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[product-screenshot]: images/screenshot.png
