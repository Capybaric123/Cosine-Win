#include "displayinfo.h"

void _display_info(void)
{
    // GLFW propper logging
    // Log GLFW version
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    log_info("GLFW version: %d.%d.%d", major, minor, rev);

    // Log monitor name
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const char* name = glfwGetMonitorName(monitor);
    log_info("Monitor: %s", name);

    // Log monitor resolution and RGB bits
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    log_info("Resolution: %dx%d @ %dHz", mode->width, mode->height, mode->refreshRate);
    log_info("RGB bits: %d, %d, %d", mode->redBits, mode->greenBits, mode->blueBits);
}