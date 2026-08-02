#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "util/log.h"

// Button states and struct
typedef struct Button {
    bool down, last, pressed, released;
}Button;

// Keyboard struct that holds keys
typedef struct Keyboard {
    Button keys[GLFW_KEY_LAST];
}Keyboard;

// Make it external (can't re-define it in another file)
extern Keyboard keyboard;

// Make the button.pressed work
// Needs to be put in the runtime loop
void keyboard_update(void);

// GLFW key callback and button.down check
void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif