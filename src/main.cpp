
#include"Texture.hpp"
#include"Shaders.hpp"
#include"VAO.hpp"
#include"VBO.hpp"
#include"EBO.hpp"
#include"Camera.hpp"
#include "GlobalOperations.hpp"

void GLAPIENTRY error_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
  fprintf(stderr, "GL CALLBACK: %s\n", message);
}

template<typename T>
std::vector<T> readValuesFromFile(const std::string& filename) {
    std::ifstream file(filename);  // Open the file
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file!");
    }

    std::vector<T> values;  // Vector to store the values
    std::string line;
    bool isFirstLine = true;  // To track the first line

    // Loop through each line in the file
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;  // Skip the first line
            continue;
        }

        std::stringstream ss(line);  // Use stringstream to process each line
        std::string token;

        // Split the line by commas
        while (std::getline(ss, token, ',')) {
            // Remove any leading/trailing spaces and convert the token to the required type
            try {
                T value = static_cast<T>(std::stod(token));  // Convert string to T (handles float, double, int, etc.)
                values.push_back(value);  // Store the value in the vector
            } catch (const std::invalid_argument& e) {
                // Handle conversion error if necessary
                std::cerr << "Error: Invalid value encountered: " << token << std::endl;
            }
        }
    }

    file.close();  // Close the file
    return values;  // Return the vector of values
}


int main(int argc, char **argv)
{
    if (!glfwInit()) {
        std::cout << "Failed To Init GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(Engine::Global::WIDTH, Engine::Global::HEIGHT, Engine::Global::TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed To Init Window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Create the camera object
    Engine::Camera camera(Engine::Global::WIDTH, Engine::Global::HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
    
    // Set the camera instance as the user pointer for this window
    glfwSetWindowUserPointer(window, &camera);
    
    // Set the scroll callback to the static Camera::scroll_callback function
    glfwSetScrollCallback(window, Engine::Camera::scroll_callback);

    glfwSwapInterval(Engine::Global::DISABLE_VSYNC);
    stbi_set_flip_vertically_on_load(true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed To Init GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    glViewport(0, 0, Engine::Global::WIDTH, Engine::Global::HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(error_message_callback, 0);

    Engine::Shaders shader;
    shader.VertexShader("shaders/default_vert.glsl");
    shader.FragmentShader("shaders/default_frag.glsl");
    shader.Program();

	Engine::Shaders lightShader;
	lightShader.VertexShader("shaders/light_vert.glsl");
	lightShader.FragmentShader("shaders/light_frag.glsl");
	lightShader.Program();

	std::vector<float> vertices = readValuesFromFile<float>("test/cubeVertices.txt");
	std::vector<unsigned int> indices = readValuesFromFile<unsigned int>("test/cubeIndices.txt");

	Engine::VAO vao;
	Engine::VBO vbo;
	Engine::EBO ebo;

	vao.Bind();
	vbo.Bind();
	ebo.Bind();

	vbo.BufferData(vertices, GL_STATIC_DRAW);
	ebo.BufferData(indices, GL_STATIC_DRAW);
	vao.AttribPointer(3, GL_FLOAT, GL_FALSE, 8, 0);
	vao.AttribPointer(3, GL_FLOAT, GL_FALSE, 8, 3);
	vao.AttribPointer(2, GL_FLOAT, GL_FALSE, 8, 6);

	Engine::VAO lightVAO;
	lightVAO.Bind();
	vbo.Bind();
	ebo.Bind();
	lightVAO.AttribPointer(3, GL_FLOAT, GL_FALSE, 8, 0);


	Engine::Texture texture;
	texture.Create("assets/wall.jpg");
	texture.Bind();
	texture.Parameter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB, GL_RGB);

	Engine::Texture texture2;
	texture2.Create("assets/pack.png");
	texture2.Bind();
	texture2.Parameter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB, GL_RGB);
	texture.Unbind();
	texture2.Unbind();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
		shader.Use();
		Engine::Operations::SetFloat3(shader.Get(), "objectColor", 1.0f, 0.5f, 0.31f);
		Engine::Operations::SetFloat3(shader.Get(), "lightColor", 1.0f, 1.0f, 1.0f);
		glm::mat4 model(1.0f);
		Engine::Operations::SetMat4fv(shader.Get(), "model", model);
        camera.Matrix(shader, "camMatrix");

		vao.Bind();
		vbo.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
		
		lightShader.Use();
		camera.Matrix(lightShader, "camMatrix");
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		Engine::Operations::SetMat4fv(lightShader.Get(), "model", model);
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, GLFW_TRUE);

        camera.Inputs(window, deltaTime);
        camera.updateMatrix(camera.FOV, 0.1f, 100.0f);
    }

    return EXIT_SUCCESS;
}
