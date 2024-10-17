#ifndef VAO_HPP
#define VAO_HPP

#include "main.hpp"

namespace Engine
{

    class VAO
    {
        private:
            GLuint ID;
            GLuint index = 0;

        public:
            VAO();
            ~VAO() = default;

            void Bind();
            void Unbind();
            void AttribPointer(GLint size, GLenum type, GLboolean normalized, GLint stride, GLint pointer);
            void Delete();
    };
}
#endif /* VAO_HPP */
