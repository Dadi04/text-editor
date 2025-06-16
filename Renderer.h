#ifndef RENDERER_H
#define RENDERER_H

#include "TextBuffer.h"
#include "Cursor.h"
#include "Selection.h"

class Renderer {
public:
    void draw(const TextBuffer& buffer, const Cursor& cursor, const Selection& selection);
    void clearScreen();
    void clearLine();
    void hideCursor();
    void showCursor();
    void moveCursorTo(int x, int y);

private:
    std::vector<std::string> lastFrame;

};

#endif