#include "input.h"

Keyboard keyboard;

void keyboard_update(void)
{
    for (int i = 0; i <= GLFW_KEY_LAST; i++)
    {
        Button *b = &keyboard.keys[i];

        b->pressed = b->down && !b->last;

        b->last = b->down;
    }
}

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
