#ifndef CURSOR_H
#define CURSOR_H

#include "TextBuffer.h"

class Cursor {
public:
    Cursor();
    void moveLeft(TextBuffer& buffer);
    void moveRight(TextBuffer& buffer);
    void moveUp(TextBuffer& buffer);
    void moveDown(TextBuffer& buffer);

    int getX() const;
    int getY() const;
    void setPosition(int x, int y);

private:
    int x;
    int y;
};

#endif