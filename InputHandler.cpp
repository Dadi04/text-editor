#include "InputHandler.h"
#include <conio.h>
#include <iostream>

Key InputHandler::getKey() {
    char ch = _getch();
    if (ch == -32 || ch == 224) {
        char code = _getch();
        switch (code) {
            case 72: return { KeyType::ArrowUp, 0 };
            case 80: return { KeyType::ArrowDown, 0 };
            case 75: return { KeyType::ArrowLeft, 0 };
            case 77: return { KeyType::ArrowRight, 0 };
            default: return { KeyType::Unknown, 0 };
        }
    }

    switch (ch) {
        case 1: return { KeyType::CtrlA, 0 };
        case 3: return { KeyType::CtrlC, 0 };
        case 8: return { KeyType::Backspace, 0 };
        case 9: return { KeyType::Tab, 0 };
        case 13: return { KeyType::Enter, 0 };
        case 15: return { KeyType::CtrlO, 0 };
        case 19: return { KeyType::CtrlS, 0 };
        case 22: return { KeyType::CtrlV, 0 };
        case 24: return { KeyType::CtrlX, 0 };
        case 25: return { KeyType::CtrlY, 0 };
        case 26: return { KeyType::CtrlZ, 0 };
        case 27: return { KeyType::Escape, 0 };
        default: return { KeyType::Character, ch };
    }
}