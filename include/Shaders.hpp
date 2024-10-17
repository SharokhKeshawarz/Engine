#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "main.hpp"

namespace Engine
{
        
    class Shaders
    {
        private:
            GLuint program;
            GLuint vertexShader;
            GLuint fragmentShader;
            GLuint tessControlShader;
            GLuint tessEvaluationShader;
            GLuint geometryShader;

            GLint params;
            GLchar infoLog[GL_INFO_LOG_LENGTH];

        public:
            Shaders() = default;
            ~Shaders() = default;
            GLuint Get();
            void Use();
            void Delete();

        public:
            void VertexShader(const char *path);
            void FragmentShader(const char *path);
            void GeometryShader(const char *path);
            void TessControlShader(const char *path);
            void TessEvaluationShader(const char *path);
            void Program();

        private:
            static char *GetFileContents(const char *path);
    };
}
#endif /* SHADERS_HPP */
