#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "main.hpp"
#include "GlobalOperations.hpp"
#include "Shaders.hpp"

namespace Engine
{

    class Texture
    {
        private:
            GLuint ID;
            std::string path;
        
        public:
            Texture() = default;
            ~Texture() = default;
            
            void Create(const std::string& path);
            void Bind();
            void Unbind();
            void Parameter(GLint xAxis, GLint yAxis, GLint filterMin, GLint filterMag, GLenum internalFormat, GLenum format);
            void Render(Shaders& shader, GLint i = 0);
            GLuint GetTexture();
            void Delete();
            std::string& GetPath();
    };
}
#endif /* TEXTURE_HPP */
