#include "Renderer.h"

#include <iostream>

void Renderer::draw(const TextBuffer& buffer, const Cursor& cursor, const Selection& selection) {
    hideCursor();
    clearScreen();
    
    for (int row = 0; row < buffer.lineCount(); row++) {
        const std::string line = buffer.getLineConst(row);
        for (int col = 0; col < line.length(); col++) {
            char ch = line[col];
            if (selection.isSelected(row, col)) {
                std::cout << "\033[7m" << ch << "\033[0m";
            } else {
                std::cout << ch;
            }
        }
        std::cout << '\n';
    }

    moveCursorTo(cursor.getX(), cursor.getY());
    showCursor();
    std::cout.flush();
}

void Renderer::hideCursor() {
    std::cout << "\033[?25l";
}

void Renderer::showCursor() {
    std::cout << "\033[?25h";
}

void Renderer::clearScreen() {
    std::cout << "\033[H\033[0J";
}

void Renderer::moveCursorTo(int x, int y) {
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}