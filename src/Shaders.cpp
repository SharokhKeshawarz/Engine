#include "Shaders.hpp"

char *Engine::Shaders::GetFileContents(const char *path)
{
    std::ifstream in(path, std::ios::binary);
    if (in) {
        in.seekg(0, std::ios::end);
        std::streamsize size = in.tellg();
        in.seekg(0, std::ios::beg);
        char *contents = new char[size + 1];
        if (in.read(contents, size)) {
            contents[size] = '\0';
            return contents;
        }
        delete[] contents;
    }
    throw(errno);
}

void Engine::Shaders::VertexShader(const char *path)
{
    char *vertexShaderSource = this->GetFileContents(path);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(vertexShader, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Vertex Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    delete[] vertexShaderSource;
}

void Engine::Shaders::FragmentShader(const char *path)
{
    char *fragmentShaderSource = this->GetFileContents(path);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(fragmentShader, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Fragment Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    delete[] fragmentShaderSource;
}
void Engine::Shaders::GeometryShader(const char *path)
{
    char *geometryShaderSource = this->GetFileContents(path);
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderSource, nullptr);
    glCompileShader(geometryShader);
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(geometryShader, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Geometry Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    delete[] geometryShaderSource;
}

void Engine::Shaders::TessControlShader(const char *path)
{
    char *tessControlShaderSource = this->GetFileContents(path);
    tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tessControlShader, 1, &tessControlShaderSource, nullptr);
    glCompileShader(tessControlShader);
    glGetShaderiv(tessControlShader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(tessControlShader, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Tessellation Control Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    delete[] tessControlShaderSource;
}

void Engine::Shaders::TessEvaluationShader(const char *path)
{
    char *tessEvaluationShaderSource = this->GetFileContents(path);
    tessEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tessEvaluationShader, 1, &tessEvaluationShaderSource, nullptr);
    glCompileShader(tessEvaluationShader);
    glGetShaderiv(tessEvaluationShader, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(tessEvaluationShader, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Tessellation Evaluation Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    delete[] tessEvaluationShaderSource;
}


void Engine::Shaders::Program()
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    if (geometryShader) glAttachShader(program, geometryShader);
    if (tessControlShader) glAttachShader(program, tessControlShader);
    if (tessEvaluationShader) glAttachShader(program, tessEvaluationShader);


    glLinkProgram(program);
    glValidateProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (!params) {
        glGetProgramInfoLog(program, GL_INFO_LOG_LENGTH, nullptr, infoLog);
        std::cerr << "Program Linking Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShader) glDeleteShader(geometryShader);
    if (tessControlShader) glDeleteShader(tessControlShader);
    if (tessEvaluationShader) glDeleteShader(tessEvaluationShader);
}

GLuint Engine::Shaders::Get()
{
    return program;
}

void Engine::Shaders::Use()
{
    glUseProgram(program);
}

void Engine::Shaders::Delete()
{
    glDeleteProgram(program);
}
