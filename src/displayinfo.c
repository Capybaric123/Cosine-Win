#include "displayinfo.h"

void displayinfo(void)
{
    // GLFW propper logging
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    log_info("GLFW version: %d.%d.%d", major, minor, rev);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const char* name = glfwGetMonitorName(monitor);
    log_info("Monitor: %s", name);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    log_info("Resolution: %dx%d @ %dHz", mode->width, mode->height, mode->refreshRate);
    log_info("RGB bits: %d, %d, %d", mode->redBits, mode->greenBits, mode->blueBits);
}