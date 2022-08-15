// system libraries
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

// imgui libraries
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// imgui file dialog library
#include "ImGuiFileDialog.h"

// glew library
#include <GL/glew.h>

// glfw library
#include <GLFW/glfw3.h>

// glm libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stb library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// shaders library
#include "shader.h"
#include "shaders.h"

// window library
#include "window.h"

// namespaces
using namespace std;

// window dimensions
const GLuint WIDTH = 1200, HEIGHT = 800;

// max vertices that can be drawn
const int MAXVERTS = 10000;
int numPoints[MAXVERTS] = {0};
int lineNumber = 0;

bool moving = false;

bool my_tool_active = true;

// whether UI is enabled or no; set to false when saving canvas into an image
bool enableUI = true;

GLfloat vertices[MAXVERTS][MAXVERTS];
GLuint VBO[MAXVERTS], VAO[MAXVERTS];

// shader
Shader* shaderProgram;

// create shaders
void create_shaders();

// add point function
void add_point(float xpos, float ypos);

// mouse callback
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);

// save picture (export canvas)
int save_picture(string* path);

// ImGui terminate functions
void ImGui_Terminate();

int main()
{
	stbi_flip_vertically_on_write(1);

	// main window
    Window mainWindow(WIDTH, HEIGHT, false);

    // initialize the main window
	mainWindow.initialize();

	glfwSetMouseButtonCallback(mainWindow.getWindow(), mouse_button_callback);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	create_shaders();

	glEnable(GL_PROGRAM_POINT_SIZE);

	GLuint color_location = glGetUniformLocation(shaderProgram->GetProgram(), "u_Color");
	ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 bg_color = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);

	// minimum file dialog size
	ImVec2 dialogMinSize = {(1000.0F), (500.0F)};

    // loop until windows closed
	while (!glfwWindowShouldClose(mainWindow.getWindow()))
	{
		// get and handle user inputs
		glfwPollEvents();

		static int counter = 0;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glBindVertexArray(0);
		glUniform4f(color_location, clear_color.x, clear_color.y, clear_color.z, clear_color.w);

		glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i <= lineNumber; i++)
		{
			if (numPoints[lineNumber] > 0 && numPoints[lineNumber] < MAXVERTS / 2)
			{
				glGenVertexArrays(1, &VAO[i]);
				glGenBuffers(1, &VBO[i]);

				// bind the vao first, then bind and set vertex buffer(s) and attribute pointer(s).
				glBindVertexArray(VAO[i]);

				glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * numPoints[i], &vertices[i][0], GL_STATIC_DRAW);

				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindVertexArray(0);
			}

			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, numPoints[i]);
			glBindVertexArray(0);
		}

		if (enableUI)
		{
			// create a window inside the app titled "Options"
			ImGui::Begin("Options", &my_tool_active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::ColorEdit3("Background", (float*)& bg_color);
			ImGui::ColorEdit3("Pen", (float*)& clear_color);

			if (ImGui::Button("Save Picture"))
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png", ".");

			// display
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiWindowFlags_AlwaysAutoResize, dialogMinSize)) 
			{
				// action if OK
				if (ImGuiFileDialog::Instance()->IsOk())
				{
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

					save_picture(&filePathName);
				}
				
				// close
				ImGuiFileDialog::Instance()->Close();
			}

			if (moving)
			{
				if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
				{
					double xpos, ypos;
					glfwGetCursorPos(mainWindow.getWindow(), &xpos, &ypos);
					add_point(xpos, ypos);
				}
			}

			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the screen buffers
		glfwSwapBuffers(mainWindow.getWindow());
	}

	// properly de-allocate all resources once they've outlived their purpose
	for (int i = 0; i < lineNumber; i++)
	{
		glDeleteVertexArrays(1, &VAO[i]);
		glDeleteBuffers(1, &VBO[i]);
	}

	// terminating functions
	ImGui_Terminate();

	return 0;
}

void create_shaders()
{
	shaderProgram = new Shader();
    shaderProgram->CreateProgram(shaders::vShader, shaders::fShader);
	shaderProgram->UseShader();
}

void add_point(float xpos, float ypos)
{
	if (numPoints[lineNumber] >= MAXVERTS / 2) return;

	float dotX = 2 * (float)xpos / WIDTH - 1.0f;
	float dotY = 1 - 2 * (float)(ypos / HEIGHT);

	vertices[lineNumber][2 * numPoints[lineNumber]] = dotX;
	vertices[lineNumber][2 * numPoints[lineNumber] + 1] = dotY;

	numPoints[lineNumber]++;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		add_point(xpos, ypos);
		moving = true;
	}
    
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
		moving = false;
		lineNumber++;
	}
}

int save_picture(string* path)
{
	// disable UI since we don't want options menu to be included in
	// the final screenshot
	enableUI = false;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	int x = viewport[0];
	int y = viewport[1];
	int width = viewport[2];
	int height = viewport[3];

	char *data = (char*) malloc((size_t) (width * height * 3)); // 3 components (R, G, B)

	if (!data)
		return 0;

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	int saved = stbi_write_png(path->c_str(), width, height, 3, data, 0);

	free(data);

	enableUI = true;

	return saved;
}

void ImGui_Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}