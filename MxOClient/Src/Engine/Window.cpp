#include "Window.h"
#include <GL/glew.h>
#include "GLCommon.h"
#include <gl/glew.h>

GLFWwindow* Window::MainWindow;

int Window::Width;
int Window::Height;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Window::Window(const std::string& title, const int width, const int height)
{
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	glfwSetErrorCallback(error_callback);

	/* Create a windowed mode window and its OpenGL context */
	auto window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	glfwSwapInterval(1);

	glewInit();



	std::cout << glGetString(GL_VERSION) << std::endl;

	Window::Width = width;
	Window::Height = height;

	MainWindow = window;
}
