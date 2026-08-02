#include "sizecallback.h"

void _size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    log_trace("Framebuffer resized to: %d x %d", width, height);
}
