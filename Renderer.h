#ifndef RENDERER_H
#define RENDERER_H

#include "TextBuffer.h"
#include "Cursor.h"

class Renderer {
public:
    void draw(const TextBuffer& buffer, const Cursor& cursor);
    void clearScreen();
    void clearLine();
    void hideCursor();
    void showCursor();
    void moveCursorTo(int x, int y);

private:
    std::vector<std::string> lastFrame;

};

#endif