cmake_minimum_required(VERSION 3.13)

# fileName environment variable
set(FILE_NAME $ENV{fileName})
project(${FILE_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
 ${PROJECT_SOURCE_DIR}/src/main.cpp
 ${PROJECT_SOURCE_DIR}/src/shader.cpp
 ${PROJECT_SOURCE_DIR}/src/shaders.cpp
 ${PROJECT_SOURCE_DIR}/src/window.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imconfig.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_internal.h
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.h
    ${PROJECT_SOURCE_DIR}/imgui/imstb_rectpack.h
    ${PROJECT_SOURCE_DIR}/imgui/imstb_textedit.h
    ${PROJECT_SOURCE_DIR}/imgui/imstb_truetype.h
    ${PROJECT_SOURCE_DIR}/ImGuiFileDialog/ImGuiFileDialog.cpp
    ${PROJECT_SOURCE_DIR}/stb/stb_image_write.h
)

# find packages
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# link libraries
target_link_libraries(${PROJECT_NAME} glfw GLEW::glew ${OPENGL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/imgui ${PROJECT_SOURCE_DIR}/ImGuiFileDialog ${PROJECT_SOURCE_DIR}/stb)