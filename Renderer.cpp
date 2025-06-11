#include "Renderer.h"

#include <iostream>

void Renderer::draw(const TextBuffer& buffer, const Cursor& cursor) {
    hideCursor();
    clearScreen();
    
    for (int i = 0; i < buffer.lineCount(); i++) {
        std::cout << buffer.getLineConst(i) << '\n';
    }

    moveCursorTo(cursor.getX(), cursor.getY());
    showCursor();
}

void Renderer::hideCursor() {
    std::cout << "\033[?25l";
}

void Renderer::showCursor() {
    std::cout << "\033[?25h";
}

void Renderer::clearScreen() {
    std::cout << "\033[2J\033[H";
}

void Renderer::moveCursorTo(int x, int y) {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}