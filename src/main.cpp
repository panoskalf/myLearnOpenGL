#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int createAndCompileShader(GLenum type, const char *source);
unsigned int createAndCompileShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const bool DRAW_WIREFRAME = false;

// simple vertex shader in GLSL
const char *vertexShaderSource =    "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

// simple fragment shader in GLSL which paints orange
const char *orangeFragmentShaderSource =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";
// simple fragment shader in GLSL which paints yellow
const char *yellowFragmentShaderSource =
                                    "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                    "}\0";

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", 0, 0);
    if (window == 0)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // first triangle vertices
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // top left
         0.0f, -0.5f, 0.0f, // bottom middle
        -0.5f, -0.5f, 0.0f, // bottom left
    };

    // second triangle vertices
    float vertices2[] = {
         0.0f,  0.5f, 0.0f, // top middle
         0.0f, -0.5f, 0.0f, // bottom middle
         0.5f, -0.5f, 0.0f, // bottom right
    };

    // create a vertex buffer objects (VBOs) and vertex array objects (VAOs)
    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // The order here matters make sure to bind the VAO first before the VBO
    // 1. bind Vertex Array Object
    glBindVertexArray(VAOs[0]);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    /**
     *  GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
     *  GL_STATIC_DRAW: the data is set only once and used many times.
     *  GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    // tell OpenGL how to interpret the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // bind VAO 2
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // create vertex shader
    unsigned int vertexShader = createAndCompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    // create fragment shader
    unsigned int orangeFragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, orangeFragmentShaderSource);
    unsigned int yellowFragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, yellowFragmentShaderSource);
    // link two shaders into a shader program
    unsigned int orangeShaderProgram = createAndCompileShaderProgram(vertexShader, orangeFragmentShader);
    unsigned int yellowShaderProgram = createAndCompileShaderProgram(vertexShader, yellowFragmentShader);
    // we no longer need the shader objects
    glDeleteShader(vertexShader);
    glUseProgram(orangeFragmentShader);
    glUseProgram(yellowFragmentShader);

    if (DRAW_WIREFRAME)
    {
        // draw in wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);
        glBindVertexArray(VAOs[0]);
        //instead of glDrawArrays when there is no BAO or index buffer
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(orangeShaderProgram);
    glDeleteProgram(yellowShaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // close window when ESC is pressed
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

unsigned int createAndCompileShader(GLenum type, const char *source)
{
    unsigned int shader;
    int  success;
    char infoLog[512];
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int createAndCompileShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int shaderProgram;
    int  success;
    char infoLog[512];
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}