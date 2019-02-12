#pragma once
#include "GLCommon.h"
#include <GLFW/glfw3.h>

class Window
{
public:
	static GLFWwindow* MainWindow;
	static int Width;
	static int Height;

	
	Window(const std::string& title, const int width, const int height);
};

