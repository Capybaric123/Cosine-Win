#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "log.h"

typedef struct Button {
    bool down, last, pressed, released;
}Button;

typedef struct Keyboard {
    Button keys[GLFW_KEY_LAST];
}Keyboard;

extern Keyboard keyboard;

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif