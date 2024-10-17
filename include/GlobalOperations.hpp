#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "main.hpp"

namespace Engine
{

    struct Global
    {
        static const int WIDTH;
        static const int HEIGHT;
        static const char *TITLE;
        static const bool ENABLE_VSYNC;
        static const bool DISABLE_VSYNC;
    };

    struct Operations
    {
        static void SetInt(GLuint program, const std::string& name, GLint value);
        static void SetBool(GLuint program, const std::string& name, GLboolean value);
        static void SetFloat(GLuint program, const std::string& name, GLfloat value);
        static void SetMat4fv(GLuint program, const std::string& name, glm::mat4 matrix);
        static void SetFloat4(GLuint program, const std::string& name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
        static void SetFloat3(GLuint program, const std::string& name, GLfloat value1, GLfloat value2, GLfloat value3);
    };
}
#endif /* GLOBAL_HPP */