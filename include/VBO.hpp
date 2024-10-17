#ifndef VBO_HPP
#define VBO_HPP

#include "main.hpp"

namespace Engine
{

    class VBO
    {
        private:
            GLuint ID;
        
        public:
            VBO();
            ~VBO() = default;

            void Bind();
            void Unbind();
            void BufferData(const std::vector<GLfloat>& vertices, GLenum usage);
            void Delete();
    };
}
#endif /* VBO_HPP */
