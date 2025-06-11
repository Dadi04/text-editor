#ifndef EDITOR_H
#define EDITOR_H

#include "TextBuffer.h"
#include "Cursor.h"
#include "Renderer.h"
#include "InputHandler.h"

#include <string>
#include <vector>

class Editor {
public:
    Editor();
    void run();

private:
    void processKey(char key);
    void enableAnsiEscapeCodes();

    TextBuffer buffer;
    Cursor cursor;
    Renderer renderer;
    InputHandler inputHandler;

    bool running;
};

#endif