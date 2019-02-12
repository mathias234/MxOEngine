#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Window.h"
#include "Collision.h"
#include "Random.h"

float timeSinceLastShoot;

void Camera::Update(float deltaTime)
{
	Vec3f change {0,0,0};

	float speed = 50;
	bool showMouse = true;
	if (glfwGetKey(Window::MainWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		change.x -= cos(glm::radians(GetRotation().y + 90)) *speed;
		change.z -= sin(glm::radians(GetRotation().y + 90)) * speed;
	}

	if (glfwGetKey(Window::MainWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		change.x += cos(glm::radians(GetRotation().y + 90)) * speed;
		change.z += sin(glm::radians(GetRotation().y + 90)) * speed;
	}

	if (glfwGetKey(Window::MainWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		change.x += -cos(glm::radians(GetRotation().y)) * speed;
		change.z += -sin(glm::radians(GetRotation().y)) * speed;
	}

	if (glfwGetKey(Window::MainWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		change.x += cos(glm::radians(GetRotation().y)) * speed;
		change.z += sin(glm::radians(GetRotation().y)) * speed;
	}


	//if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
	//	showMouse = !showMouse;
	//}

	auto newPos = GetPosition() + change * deltaTime;


	//if (Collision::AtMapEdgeX(newPos.x))
	//	newPos.x = GetPosition().x;
	//if (Collision::AtMapEdgeZ(newPos.z))
	//	newPos.z = GetPosition().z;

	SetPosition(newPos);

	//Window::MainWindow->setMouseCursorVisible(showMouse);

	//if (!showMouse) {
	//	static sf::Vector2i lastMousePos = sf::Mouse::getPosition();

	//	auto mouseDelta = sf::Mouse::getPosition() - lastMousePos;

	//	auto oldRot = GetRotation();

	//	SetRotation({ oldRot.x, oldRot.y + mouseDelta.x * 0.1f, oldRot.z });


	//	auto centerX = Window::Width / 2;
	//	auto centerY = Window::Height / 2;

	//	sf::Mouse::setPosition({ centerX, centerY }, *Window::MainWindow);

	//	lastMousePos = sf::Mouse::getPosition();
	//}
}

void Camera::SetPosition(Vec3f position)
{
	pos = position;
}

void Camera::SetRotation(Vec3f rotation)
{
	rot = rotation;
}

Vec3f Camera::GetPosition()
{
	return pos;
}

Vec3f Camera::GetRotation()
{
	return rot;
}

