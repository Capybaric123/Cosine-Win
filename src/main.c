#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "log.h"
#include "sizecallback.h"
#include "input.h"
#include "state.h"
#include "util/types.h"
#include "displayinfo.h"

#define WIDTH 640
#define HEIGHT 480

struct State state;

// Shader source code
// TODO: move them
static const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void _wireframe_mode(bool enabled);

int main(void)
{

    // Initialize logger
    log_trace("Logger initialized successfully!");

    // Initialize GLFW
    if(!glfwInit())
    {
        log_error("Failed to initialize GLFW!");
        return -1;
    }
    log_trace("GLFW initialized successfully!");
    // Set window hints
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    log_trace("Set GLFW version context!");
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log_trace("Set GLFW openGL profile!");

    // Create the window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cosine Engine", NULL, NULL);
    // Check for errors during creation
    if(window == NULL)
    {
        log_error("Failed to create GLFW window!");
        glfwTerminate();
        return -1;
    }

    // Log GLFW display info
    _display_info();

    // Set OpenGL window context
    log_trace("Successfully created GLFW window!");
    glfwMakeContextCurrent(window);
    log_trace("Set openGL window context!");

    // Load GLAD and print out the OpenGL version
    int version = gladLoadGL(glfwGetProcAddress);
    // Check for errors during initialization
    if(version == 0)
    {
        log_error("Failed to initialize GLAD!");
        glfwTerminate();
        return -1;
    }
    // Log the OpenGL version
    log_info("Loaded OpenGL %d.%d",
             GLAD_VERSION_MAJOR(version),
             GLAD_VERSION_MINOR(version));

    // Compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Simple logger to output any compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        log_error("ERROR::SHADER::VERTEX::COMPILATION_FILED\n%s", infoLog);
    }

    // Compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for any compile errors with the fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        log_error("ERROR:SHADER::FRAGMENT:COMPILATION_FAILED\n%s", infoLog);
    }

    // Create a shader program
    u32 shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach shaders and link the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for any linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        log_error("ERROR::SHADER::PROGRAM:LINKING_FAILED\n%s", infoLog);
    }

    // List of vertices for the rectangle
    static f32 vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    // List of indices for the rectangle
    static u32 indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // TODO: move to separate files

    // Create the VAO and the VBO
    GLuint VBO, VAO, IBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // Bind the VAO before the VBO
    glBindVertexArray(VAO);

    // Bind the VBO and set its data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set the vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind the vertex buffer (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind the VAO
    glBindVertexArray(0);

    // Bind the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Set the initial window size OpenGL viewport
    glViewport(0, 0, 640, 480);

    // Set the framebuffer and the key callbacks
    glfwSetFramebufferSizeCallback(window, _size_callback);
    glfwSetKeyCallback(window, _key_callback);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Main loop aka. runtime
    while(!glfwWindowShouldClose(window))
    {
        // Clear the window with a nice colour
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Make the keyboard.key.pressed work
        keyboard_update();

        // Input checks and everything else
        if (keyboard.keys[GLFW_KEY_ESCAPE].down == true) {
            glfwSetWindowShouldClose(window, true);
            log_info("Shutdown call processed");
        }
        if (keyboard.keys[GLFW_KEY_F3].pressed == true) {
            state.wireframe = !state.wireframe;
            log_info("Wireframe mode set to: %s", state.wireframe ? "on" : "off");
        }
        // Wireframe mode :3
        _wireframe_mode(state.wireframe);

        // Use the program and bind the VAO
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Draw call
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Make the window not show up as not responding
        glfwPollEvents();
        // Swap the double buffers
        glfwSwapBuffers(window);
    }

    // Cleanup buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);

    // Cleanup the shader program
    glDeleteProgram(shaderProgram);

    // Destroy the window on exit
    glfwDestroyWindow(window);
    // Terminate GLFW on exit
    glfwTerminate();

    return 0;
}

// Over-engineered toggle function
void _wireframe_mode(bool enabled) {
    if (enabled) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}