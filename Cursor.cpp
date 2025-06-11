#include "Cursor.h"

Cursor::Cursor() : x(0), y(0) {}

void Cursor::moveLeft(TextBuffer& buffer) {
    if (x > 0) {
        x--;
    } else if (y > 0) {
        y--;
        x = buffer.lineLength(y);
    }
}

void Cursor::moveRight(TextBuffer& buffer) {
    if (x < buffer.lineLength(y)) {
        x++;
    } else if (y < buffer.lineCount() - 1) {
        y++;
        x = 0;
    }
}

void Cursor::moveUp(TextBuffer& buffer) {
    if (y > 0) {
        y--;
        if (x > buffer.lineLength(y)) {
            x = buffer.lineLength(y);
        }
    }
}

void Cursor::moveDown(TextBuffer& buffer) {
    if (y < buffer.lineCount() - 1) {
        y++;
        if (x > buffer.lineLength(y)) {
            x = buffer.lineLength(y);
        }
    }
}

int Cursor::getX() const {
    return x;
}

int Cursor::getY() const {
    return y;
}

void Cursor::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
