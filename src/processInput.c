#include "processInput.h"

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        log_trace("Shutdown call detected!");
        glfwSetWindowShouldClose(window, 1);
    }
}
