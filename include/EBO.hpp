#ifndef EBO_HPP
#define EBO_HPP

#include "main.hpp"

namespace Engine
{

    class EBO
    {
        private:
            GLuint ID;
        
        public:
            EBO();
            ~EBO() = default;

            void Bind();
            void Unbind();
            void BufferData(const std::vector<GLuint>& indices, GLenum usage);
            void Delete();
    };
}
#endif /* EBO_HPP */
