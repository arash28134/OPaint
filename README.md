## OPaint
OPaint is a simple drawing app written in C++ using OpenGL, GLFW, GLEW, GLM, Dear ImGui and ImGuiFileDialog libraries for Linux. It focuses on providing a lightweight and simple UI for quickly taking notes and saving them as .PNG files
## Usage
You can change color of pen and background using color widgets. you can also manually enter their RGB value.
When you're done drawing, you can save the drawing as a .PNG file

![Alt text](preview.gif?raw=true "Preview Gif")
## Installation
To install the program, either [Build from source](#building-from-source) or download a pre-built binary from [Releases](https://github.com/arash28134/OPaint/releases) section
## Building from source
- First clone the repository and It's submodules:
```
git clone --recurse-submodules https://github.com/arash28134/OPaint.git
```
- Make sure you have the dependencies needed for building program listed in CMakeLists.txt
- Run the build script:
```
./build.sh
```
- Alternatively you can run build script using the **--r** flag and have it automatically run the final executable after building is finished:
```
./build.sh --r
```