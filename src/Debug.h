#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG true

enum ControllerState {
    OFF,
    FIRING_UP_PREBLOW,
    PREFEED,
    FIRING_UP,
    STABILIZATION,
    NORMAL,
    CLEANING,
    EXTINCTION
};

class Debug{
public:
    static ControllerState state;
    static void Log(const char* str);
    static void State();
};

#endif