#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#include <iostream>
#include <math.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*
 Here we define the vertex shader. The vertex shader is the first step in teh OpenGL graphics
 pipeline. The shader allows us to transform the vertices we pass into it if need be. For now,
 this shader simply outputs the same values that we pass into it
 */

const char *vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.x, 1.0f);\n"
"    vertexColor = aColor;\n"
"}\0";

const char *fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
//"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(vertexColor, 1.0f);\n"
"}\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    Shader s("../../src/shaders/vertex_shader_ex2.vs", "../../src/shaders/fragment_shader.fs");
    
    
    // 2. Create VBO and VAO objects
    
    // For the sake of drawing constant vertices we can define these here
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.25f,  0.5f, 0.3f, 0.0f, 0.0f, 1.0f // top
    };
    
    // Note on vertex array objects (VAO). In the vertex shader, we must manually define
    // how vertex attributes (x, y and z coordinates) are layed out in our buffer.
    // For the set of vertices defined above we would expect each vertex to take up 3 * 4 = 12 bytes.
    // In the buffer the floats of the vertices are arranged as (X | Y | Z) (X | Y | Z) ...
    // The vertices in this case are tightly packed into the buffer. We have to specify this layout
    // using a VAO. We do so as such:
    
    // Create a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // Next we create a vertex buffer object (VBO) in order to store our vertices into.
    uint32_t VBO;
    glGenBuffers(1, &VBO);
    
    // We call this before setting up the buffer and the vertex attributes. By doing so the
    // VAO object becomes bound to configuration of the buffer and the vertex attributes that we
    // define after it.
    glBindVertexArray(VAO);
    
    // Bind to the buffer. When we bind to the buffer, any future buffer manipulation calls
    // we make will be done on the buffer we have bound to. NOTE: we can bind to one buffer of each type
    // In this case we are using the GL_ARRAY_BUFFER type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Now we tell OpenGL how to interpret the vertex data in this VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // The buffer and the vertex attributes have been bound to VAO. We can unbind now.
    glBindVertexArray(0);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        
        // NOTE: we have to say which program and which VAO to use everytime we render.
        
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
        s.use();
        s.setFloat("hOffset", 0.5f);
        glBindVertexArray(VAO);
        
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the triangle.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
