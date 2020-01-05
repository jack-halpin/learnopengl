//
//  shader.h
//  learnopengl
//
//  Created by Jack Halpin on 25/09/2019.
//

#ifndef shader_h
#define shader_h


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        char buffer[256];
        char *answer = getcwd(buffer, sizeof(buffer));
        std::string s_cwd;
        if (answer)
        {
            s_cwd = answer;
        }
        
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vertexFile;
        std::ifstream fragmentFile;

        vertexFile.exceptions(std::ifstream::failbit);
        fragmentFile.exceptions(std::ifstream::failbit);
        try{
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);

            std::stringstream vertexStream, fragmentStream;
            vertexStream << vertexFile.rdbuf();
            fragmentStream << fragmentFile.rdbuf();

            // close the files
            vertexFile.close();
            fragmentFile.close();

            vertexCode = vertexStream.str();
            fragmentCode = fragmentStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR: Shader not succesfully read" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        
        // Check that the shader compiled succesffuly
        int32_t success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
        }
        
        //Create vertex shader object and compile it
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        
        // Check that the shader compiled succesffuly
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
        }
        
        // Create a shader program that links the shaders together.
        ID = m_shaderProgram = glCreateProgram();
        
        // Set the shaders for that program
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);
        
        
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR: Linking shaders in shader program\n" << infoLog << std::endl;
        }
        
        // If it was successful we need to use the set the program to be used
        // Once we've linked them, we no longer need the shader obejcts
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    void use()
    {
        glUseProgram(m_shaderProgram);
    }
    
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }
    void setMat4(const std::string &name, glm::mat4 matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str())
                           , 1, GL_FALSE, glm::value_ptr(matrix));
    }
    unsigned int m_shaderProgram;
    unsigned int ID;
};


#endif /* shader_h */
