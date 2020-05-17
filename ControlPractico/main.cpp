#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "MatrizT.h"
#include <iostream>

using namespace std;

#define PI 3.1416
MatrizT mT;
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

double alphaX = 69 * (PI / 180);
double alphaY = 37 * (PI / 180);
double alphaZ = 63 * (PI / 180);

float triangulo_rotY[] = {
    cos(alphaY), 0.0f, sin(alphaY), 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -sin(alphaY), 0.0f, cos(alphaY), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_rotX[] = {
    1, 0.0f, 0.0f, 0.0f,
    0.0f, cos(alphaX), -sin(alphaX), 0.0f,
    0.0f, sin(alphaX), cos(alphaX), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_rotZ[] = {
    cos(alphaZ), -sin(alphaZ), 0.0f, 0.0f,
    sin(alphaZ), cos(alphaZ), 0.0f, 0.0f,
    0.0f, 0.0f, 0.1f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f      
};

float x = 0.2f;
float y = 0.35f;
float z = 0.175f;

float identidad[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

float triangulo_xp[] = {
    1.0f, 0.0f, 0.0f, x, //x positivo
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_xn[] = {
    1.0f, 0.0f, 0.0f, -x, //x negativo
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_yp[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, y, //y positivo
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_yn[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, -y, //y negativo
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_zp[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, z,    //z positivo
    0.0f, 0.0f, 0.0f, 1.0f
};

float triangulo_zn[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, -z,   //z positivo
    0.0f, 0.0f, 0.0f, 1.0f
};

float es_x = 1.25f;
float es_y = 1.0f;
float es_z = 1.25f;

float triangulo_sc[] = {
    es_x, 0.0f, 0.0f, 0.0f,
    0.0f, es_y, 0.0f, 0.0f,
    0.0f, 0.0f, es_z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float vertices[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};

float vertices_s[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};

float vertices_t[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};

float vertices_rX[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};

float vertices_rY[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};

float vertices_rZ[] = {
    0.25f, -0.5f, 0.0f, // left  
    -0.25f, 0.5f, 0.0f, // right 
    -0.75f, -0.5f, 0.0f // top
};


void menu() {
    cout << "-------------------> Menu <--------------------\n";
    cout << "Tecla Flecha <-: Traslacion hacia la Izquierda\n";
    cout << "Tecla Flecha ->: Traslacion hacia la Derecha\n";
    cout << "Tecla Flecha Arriba: Traslacion hacia Arriba\n";
    cout << "Tecla Flecha Abajo: Traslacion hacia Abajo\n";
    cout << "Tecla E: Escala en X, Y, Z\n";
    cout << "Tecla X: Rotacion en X\n";
    cout << "Tecla Y: Rotacion en Y\n";
    cout << "Tecla Z: Rotacion en Z\n";
    cout << "Tecla T: Transformacion\n";
}

void print(float v[])
{
    cout << "(";
    for (int i = 0; i <= sizeof(v); i++)
    {
        cout << v[i] << ", ";
    }
    cout << ")\n";
}

void keyFunc2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float v_input[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float v_out[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float m_out[4];

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            //v_t[i] = vertices[i];
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_xn, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_t[i * 3 + j] = v_out[j];
            }
        }
        cout << "Traslacion Izquierda: ";
        print(vertices);
    }
    //print(vertices_t);
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            //v_r[i] = vertices[i];
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_xp, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_t[i * 3 + j] = v_out[j];
            }
        }
        cout << "Traslacion Derecha: ";
        print(vertices);
        //print(v_r);
    }
    //print(vertices_r);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_yp, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_t[i * 3 + j] = v_out[j];
            }
        }
        cout << "Traslacion Arriba: ";
        print(vertices);
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_yn, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_t[i * 3 + j] = v_out[j];
            }
        }
        cout << "Traslacion Abajo: ";
        print(vertices);
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.escalaM(triangulo_sc, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_s[i * 3 + j] = v_out[j];
            }
        }

        cout << "Escala en X, Y, Z: ";
        print(vertices);
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotY, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_rY[i * 3 + j] = v_out[j];
            }
        }
        cout << "Rotacion en Y: ";
        print(vertices);
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotX, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_rX[i * 3 + j] = v_out[j];
            }
        }
        cout << "Rotacion en X: ";
        print(vertices);
    }

    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v_input[j] = vertices[i * 3 + j];
            }

            mT.traslacionM(triangulo_rotZ, v_input, &v_out[0], 4, 4);

            for (int j = 0; j < 3; j++)
            {
                vertices[i * 3 + j] = v_out[j];
                vertices_rZ[i * 3 + j] = v_out[j];
            }
        }
        cout << "Rotacion en Z: ";
        print(vertices);
    }

    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        float mat[9];
        float m_r[9];
        mT.multiplicacionMM(vertices_rY, vertices_s, &mat[0], 3, 3);
        mT.multiplicacionMM(vertices_rZ, vertices_t, &m_out[0], 3, 3);
        mT.multiplicacionMM(mat, m_out, &m_r[0], 3, 3);

        for (int i = 0; i < 3; i++)
        {
            mat[i] = float(0);
            for (int j = 0; j < 3; j++)
            {
                vertices[i*3+j] = m_r[j];
                //mat[i*4+j]= 
            } 
        }
        cout << "Transformacion: ";
        print(vertices);
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Control - Practico", NULL, NULL);
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
    unsigned int VBO, VAO;

    // primer triangulo
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    menu();

    do {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibuja el triangulo
        glUseProgram(shaderProgram);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(flecha), flecha, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetKeyCallback(window, keyFunc2);
    } while (glfwWindowShouldClose(window) == 0 && (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS));

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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