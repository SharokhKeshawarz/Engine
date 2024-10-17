#include"Camera.hpp"

Engine::Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Engine::Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	cameraMatrix = projection * view;
}

void Engine::Camera::Matrix(Shaders& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.Get(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Engine::Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	float adjustedSpeed = speed * deltaTime * 0b1010; // Binary for 10 

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += adjustedSpeed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position += adjustedSpeed * -glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position += adjustedSpeed * -Orientation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += adjustedSpeed * glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += adjustedSpeed * Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position += adjustedSpeed * -Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.4f;
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 0.1f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			Orientation = newOrientation;

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Engine::Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	// Retrieve the Camera object from the GLFW window user pointer
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	// Call the non-static member function
	camera->ProcessScroll(window, xoffset, yoffset);
}

void Engine::Camera::ProcessScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    if (FOV >= 1.0f && FOV <= 120.0f)
        FOV -= yoffset;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 120.0f)
        FOV = 120.0f;
}
