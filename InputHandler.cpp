#include "InputHandler.h"
#include <conio.h>

char InputHandler::getKey() {
    char ch = _getch();
    return ch;
}