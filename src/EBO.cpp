#include "EBO.hpp"

Engine::EBO::EBO()
{
    glGenBuffers(1, &ID);
}

void Engine::EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Engine::EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::EBO::BufferData(const std::vector<GLuint>& indices, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), usage);
}

void Engine::EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
