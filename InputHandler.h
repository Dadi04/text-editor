#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

enum class KeyType {
    Character,
    ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
    Enter, Tab, Escape, Backspace,
    CtrlA, CtrlC, CtrlX, CtrlV, CtrlZ, CtrlY, CtrlS, CtrlO,
    Unknown,
};

struct Key {
    KeyType type;
    char ch;
};

class InputHandler {
public:
    Key getKey();
};

#endif