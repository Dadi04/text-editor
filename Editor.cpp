#include "Editor.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

Editor::Editor() : running(true) {
    enableAnsiEscapeCodes();
}

void Editor::run() {
    while(running) {
        renderer.clearScreen();
        renderer.draw(buffer, cursor);

        char key = inputHandler.getKey();
        processKey(key);
    }
}

void Editor::processKey(char key) {
    int x = cursor.getX();
    int y = cursor.getY();

    if (key == -32 || key == 224) {
        char arrow = inputHandler.getKey();
        switch (arrow) {
            case 72: cursor.moveUp(buffer); break;
            case 80: cursor.moveDown(buffer); break;
            case 75: cursor.moveLeft(buffer); break;
            case 77: cursor.moveRight(buffer); break;
        }
    } else if (key == '\r') {
        std::string line = buffer.getLineConst(y);
        std::string newLine = line.substr(x);

        line = line.substr(0, x);
        buffer.insertLine(y + 1);
        buffer.getLineMutable(y + 1) = newLine;

        cursor.setPosition(0, y + 1);
    } else if (key == '\t') {
        const std::string tab = "    ";
        for (char c : tab) {
            buffer.insertChar(y, x++, c);
        }
        cursor.setPosition(x, y);
    } else if (key == 27) {
        running = false;
    } else if (key == 8) {
        if (x > 0) {
            buffer.deleteChar(y, x);
            cursor.moveLeft(buffer);
        } else if (y > 0) {
            buffer.getLineMutable(y - 1) += buffer.getLineConst(y);
            buffer.deleteLine(y);
            cursor.setPosition(buffer.lineLength(y - 1), y - 1);
        }
    } else {
        buffer.insertChar(y, x, key);
        cursor.moveRight(buffer);
    }
}

void Editor::enableAnsiEscapeCodes() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}