#include "../include/Cerium/ShaderProgram.hpp"
#include "../include/Cerium/DebugLog.hpp"

#include <fstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace cerium
{
    ShaderProgram::ShaderProgram(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
    {
        std::string vertexShaderFilePath = "res/shaders/" + vertexShaderPath;
        std::string fragmentShaderFilePath = "res/shaders/" + fragmentShaderPath;

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderFileSource;
        std::ifstream vertexShaderFile(vertexShaderFilePath);

        std::string line;
        if(vertexShaderFile.is_open())
        {
            while (std::getline(vertexShaderFile, line))
            {
                vertexShaderFileSource += line + "\n";
            }
        }
        else
        {
            cerium::DebugLog::add(vertexShaderFilePath + " vertexShader can't be loaded");
        }

        vertexShaderFile.close();

        std::string fragmentShaderFileSource;
        std::ifstream fragmentShaderFile(fragmentShaderFilePath);

        if(fragmentShaderFile.is_open())
        {
            while (std::getline(fragmentShaderFile, line))
            {
                fragmentShaderFileSource += line + "\n";
            }
        }
        else
        {
            cerium::DebugLog::add(fragmentShaderFilePath + " fragmentShader can't be loaded");
        }
        fragmentShaderFile.close();

        GLint vertexShaderCompilationSuccess;
        GLchar vertexShaderCompilationLog[512];

        const char * vertexShaderSource = vertexShaderFileSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompilationSuccess);
        if(!vertexShaderCompilationSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderCompilationLog);
            std::cout << vertexShaderCompilationLog << std::endl;
        }

        GLint fragmentShaderCompilationSuccess;
        GLchar fragmentShaderCompilationLog[512];

        const char * fragmentShaderSource = fragmentShaderFileSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompilationSuccess);
        if(!fragmentShaderCompilationSuccess)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentShaderCompilationLog);
            std::cout << fragmentShaderCompilationLog << std::endl;
        }

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    void ShaderProgram::setMatUniform(const std::string & name, const glm::mat4 & value)
    {
        GLint uniform = glGetUniformLocation(program, name.c_str());
        if(uniform > -1)
        {
            glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
        }
        else
        {
            cerium::DebugLog::add(name + " uniform can't be founded!");
        }
    }


    void ShaderProgram::setIntegerUniform(const std::string & name, const int & value)
    {
        GLint uniform = glGetUniformLocation(program, name.c_str());
        if(uniform > -1)
        {
            glUniform1i(glGetUniformLocation(program, name.c_str()), value);
        }
        else
        {
            cerium::DebugLog::add(name + " uniform can't be founded!");
        }
    }


    void ShaderProgram::setVec4Uniform(const std::string & name, const vec4 & value)
    {
        GLint uniform = glGetUniformLocation(program, name.c_str());
        if(uniform > -1)
        {
            glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w);
        }
        else
        {
            cerium::DebugLog::add(name + " uniform can't be founded!");
        }
    }


    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program);
    }


    void ShaderProgram::use(void)
    {
        glUseProgram(program);
    }
}