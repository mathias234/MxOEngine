#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GLCommon.h"
#include "Window.h"
#include "Random.h"
#include "CppGame.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Maths.h"
#include "Lighting/DirectionalLight.h"
#include "../MXOFile/MxOLoader.h"
#include "Texture.h"
#include "../MXOFile/Moa.h"
#include <GLFW/glfw3.h>

bool gameRunning = true;

MxOLoader CppGame::Loader;

int main() {
	Window("Matrix Online", 800, 600);

	CppGame::Loader.initialize("G:/Matrix Online");

	unsigned long meshDataSize;
	char* meshData;

	if (CppGame::Loader.get_file(0x28000DB1, &meshDataSize, meshData))
	{
		std::cout << "Successfully loaded file " << " of size: " << meshDataSize << std::endl;
	}
	else
	{
		std::cout << "Failed to load file" << std::endl;;
	}

	Moa mgaMesh(meshData, meshDataSize);


	Camera cam = Camera();
	cam.SetPosition({ 0,2,0 });
	cam.SetRotation({ -2,0,0 });


	Shader shader("data/shaders/Main.shader");
	DirectionalLight dirLight;
	dirLight.AmbientIntensity = 0.3f;
	dirLight.Color = Vec3f(1, 1, 1);
	dirLight.DiffuseIntensity = 0.85f;
	dirLight.Direction = glm::vec3(80, -45, -20);

	float oldTime = 0;
	float newTime = 0;
	while (!glfwWindowShouldClose(Window::MainWindow))
	{
		oldTime = newTime;
		newTime = glfwGetTime();

		float deltaTime = newTime - oldTime;

		int fWidth, fHeight;
		glfwGetFramebufferSize(Window::MainWindow, &fWidth, &fHeight);
		glViewport(0, 0, fWidth, fHeight);

		// Game Loop
		CallGL(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
		CallGL(glClearColor(0.0f, 1.0f, 0.894f, 1.0f));

		CallGL(glEnable(GL_DEPTH_TEST));
		CallGL(glDisable(GL_CULL_FACE));
		CallGL(glFrontFace(GL_CCW));

		cam.Update(deltaTime);

		shader.Bind();

		shader.SetUniform("u_ViewMatrix", Math::CreateViewMatrix(cam.GetPosition(), cam.GetRotation()));
		shader.SetUniform("u_ProjMatrix", Math::CreateProjMatrix());
		shader.SetUniform("u_ModelMatrix", Math::CreateModelMatrix({ 0,0,0 }, { 0,0,0 }, { 0.1,0.1,0.1 }));
		shader.SetUniform("u_Tiling", { 1,1 });
		shader.SetUniform("u_Color", { 1,1,1,1 });

		dirLight.Bind(shader);

		mgaMesh.Draw(shader);


		glfwSwapBuffers(Window::MainWindow);

		glfwPollEvents();
	}

	return 0;
}
