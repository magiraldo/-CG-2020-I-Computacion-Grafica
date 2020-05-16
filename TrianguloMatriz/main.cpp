//#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <math.h>
#include "MatrizT.h"

#include <stdlib.h>

#define GLFW_KEY_RIGHT   262
#define GLFW_KEY_LEFT   263
#define GLFW_KEY_DOWN   264
#define GLFW_KEY_UP   265
#define PI 3.1416
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

MatrizT mT;

float x = 0.0f, y = 0.0f, z = 0.0f;
double rot_x = 0, rot_y = 0;

float triangulo_rotY[] = {
    cos(45), 0.0f, sin(45), 0.0f, 
    0.0f, 1.0f, 0.0f, 0.0f, 
    -sin(45), 0.0f, cos(45), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_rotX[] = {
    1, 0.0f, 0.0f, 0.0f, 
    0.0f, cos(45), -sin(45), 0.0f, 
    0.0f, sin(45), cos(45), 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_rotZ[] = {
    cos(90), -sin(90), 0.0f, 0.0f,
    sin(90), cos(90), 0.0f, 0.0f,
    0.0f, 0.0f, 0.1f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_xp[] = {
	1.0f, 0.0f, 0.0f, 0.3f, //x positivo
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_xn[] = {
	1.0f, 0.0f, 0.0f, -0.3f, //x negativo
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_yp[] = {
    1.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 0.3f, //y positivo
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_yn[] = {
    1.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, -0.3f, //y negativo
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f  
};

float triangulo_scms[] = {
    0.9f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.9f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.9f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_scmx[] = {
    1.1f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.1f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.1f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
float mat_i[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

float vertices[] = {
    -0.3f, 0.0f, 0.0f, // left  
    0.3f, 0.0f, 0.0f, // right 
    0.0f, 0.3f, 0.0f // top
};

float vertices2[] = {
    -0.15f, 0.0f, 0.0f, //left v
    -0.15f, -0.3f, 0.0f, //down n
    0.15f, 0.0f, 0.0f //right v
};

float vertices3[] = {
    -0.15f, -0.3f, 0.0f, //left
    0.15f, -0.3f, 0.0f, //right
    0.15f, 0.0f, 0.0f //top
};

//Funcion creada para el cambio de colores de fondo
void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
    case 265: glClearColor(0.3f, 0.3f, 0.3f, 1.0f); break;
    case 264: glClearColor(0.2f, 0.3f, 0.3f, 1.0f); break;
    case 263: glClearColor(0.2f, 0.3f, 0.2f, 1.0f); break;
    case 262: glClearColor(0.3f, 0.2f, 0.3f, 1.0f); break;
    default: break;
    }
}

void keyFunc2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float v_input[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_input2[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_input3[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_out[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_out2[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_out3[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_xn, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_xn, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_xn, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_xp, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_xp, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_xp, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_yp, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_yp, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_yp, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_yn, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_yn, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_yn, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //n_es += n_es - 0.00000001f;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }
                
            mT.escalaM(triangulo_scms, v_input, &v_out[0], 4, 4);
            mT.escalaM(triangulo_scms, v_input2, &v_out2[0], 4, 4);
            mT.escalaM(triangulo_scms, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        //n_es += n_es - 0.00000001f;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }
            mT.escalaM(triangulo_scmx, v_input, &v_out[0], 4, 4);
            mT.escalaM(triangulo_scmx, v_input2, &v_out2[0], 4, 4);
            mT.escalaM(triangulo_scmx, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        //n_es += n_es - 0.00000001f;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotY, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_rotY, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_rotY, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        //n_es += n_es - 0.00000001f;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotX, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_rotX, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_rotX, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }

    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        //n_es += n_es - 0.00000001f;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
                v_input2[j] = vertices2[i * 3 + j];
                v_input3[j] = vertices3[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotZ, v_input, &v_out[0], 4, 4);
            mT.traslacionM(triangulo_rotZ, v_input2, &v_out2[0], 4, 4);
            mT.traslacionM(triangulo_rotZ, v_input3, &v_out3[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices2[i * 3 + j] = v_out2[j];
                vertices3[i * 3 + j] = v_out3[j];
            }
        }
    }
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
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
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //-------------------------------------------------------------
    // BUFFERSS........
    //-------------------------------------------------------------
    unsigned int VBO[3], VAO[3];

    // primer triangulo
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    //segundo triangulo
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //tercer triangulo
    glGenVertexArrays(1, &VAO[2]);
    glGenBuffers(1, &VBO[2]);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    do {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibuja el triangulo
        glUseProgram(shaderProgram);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(flecha), flecha, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(flecha), flecha, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(flecha), flecha, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetKeyCallback(window, keyFunc2);
    } while (glfwWindowShouldClose(window) == 0 && (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS));
 
    for (int i = 0; i < 3; i++)
    {
        glDeleteVertexArrays(1, &VAO[i]);
        glDeleteBuffers(1, &VBO[i]);
    }
    //glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

