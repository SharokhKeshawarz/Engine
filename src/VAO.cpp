#include "VAO.hpp"

Engine::VAO::VAO()
    : index(0)
{
    glGenVertexArrays(1, &ID);
}

void Engine::VAO::Bind()
{
    glBindVertexArray(ID);
}

void Engine::VAO::Unbind()
{
    glBindVertexArray(0);
}

void Engine::VAO::AttribPointer(GLint size, GLenum type, GLboolean normalized, GLint stride, GLint pointer)
{
    glVertexAttribPointer(index, size, type, normalized, static_cast<GLsizei>(stride * sizeof(float)), reinterpret_cast<void*>(pointer * sizeof(float)));
    glEnableVertexAttribArray(index);
    index++;
}

void Engine::VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}