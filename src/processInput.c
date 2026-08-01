#include "processInput.h"

Keyboard keyboard;

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 0) {
        return;
    }

    switch (action) {
        case GLFW_PRESS:
            keyboard.keys[key].down = true;
            break;
        case GLFW_RELEASE:
            keyboard.keys[key].down = false;
            break;
        default:
            break;
    }

}
