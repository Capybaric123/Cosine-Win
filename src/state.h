#ifndef STATE_H
#define STATE_H

// Set global variables aka. the global state
struct State
{
    _Bool wireframe;
};

// Make it so another file can't redefine the struct
extern struct State state;

#endif
