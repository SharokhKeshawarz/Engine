#include "Texture.hpp"

void Engine::Texture::Create(const std::string& path)
{
    glGenTextures(1, &ID);
    this->path = path;
}

void Engine::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Engine::Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::Texture::Parameter(GLint xAxis, GLint yAxis, GLint filterMin, GLint filterMag, GLenum internalFormat, GLenum format)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xAxis);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yAxis);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
    int width, height, channels_in_file;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels_in_file, 0);
    if (!data) {
        std::cerr << "Failed To Load Texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Engine::Texture::Render(Engine::Shaders& shader, GLint i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    this->Bind();
    shader.Use();
    std::string result = "texture" + std::to_string(i);
    Operations::SetInt(shader.Get(), result, i);
}

GLuint Engine::Texture::GetTexture()
{
    return ID;
}

std::string& Engine::Texture::GetPath()
{
    return path;
}

void Engine::Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
