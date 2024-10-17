#include "GlobalOperations.hpp"

const int Engine::Global::WIDTH = 800;
const int Engine::Global::HEIGHT = 600;
const char *Engine::Global::TITLE = "Game";
const bool Engine::Global::ENABLE_VSYNC = true;
const bool Engine::Global::DISABLE_VSYNC = false;

void Engine::Operations::SetInt(GLuint program, const std::string& name, GLint value)
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Engine::Operations::SetBool(GLuint program, const std::string& name, GLboolean value)
{
    if (value != 0 || value != 1 ) {
        std::cerr << "SetBool takes True or False" << std::endl;
        exit(EXIT_FAILURE);
    }
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Engine::Operations::SetFloat(GLuint program, const std::string& name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Engine::Operations::SetMat4fv(GLuint program, const std::string& name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Engine::Operations::SetFloat3(GLuint program, const std::string& name, GLfloat value1, GLfloat value2, GLfloat value3)
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), value1, value2, value3);
}

void Engine::Operations::SetFloat4(GLuint program, const std::string& name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4)
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value1, value2, value3, value4);
}
