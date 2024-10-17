#include "VBO.hpp"

Engine::VBO::VBO()
{
    glGenBuffers(1, &ID);
}

void Engine::VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Engine::VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::VBO::BufferData(const std::vector<GLfloat>& vertices, GLenum usage)
{
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), usage);
}

void Engine::VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
