#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "main.hpp"

#include "Shaders.hpp"
#include "GlobalOperations.hpp"

namespace Engine
{

	class Camera
	{
	public:
		glm::vec3 Position;
		float FOV = 45.0f;
		
	private:
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);
		bool firstClick = true;
		int width;
		int height;
		float speed = 1.0f;
		float sensitivity = 100.0f;

	public:
		Camera(int width, int height, glm::vec3 position);

		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shaders& shader, const char* uniform);
		void Inputs(GLFWwindow* window, float deltaTime);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset);
	};
}

#endif