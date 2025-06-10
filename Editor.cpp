#include "Editor.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

Editor::Editor() : cursorX(0), cursorY(0) {
    buffer.push_back("");
}

void Editor::run() {
    while(true) {
        render();

        char key = _getch();

        if (key == -32) {
            char arrow = _getch();
            switch (arrow) {
                case 72: moveCursor(0, -1); break;
                case 80: moveCursor(0, 1); break;
                case 75: moveCursor(-1, 0); break;
                case 77: moveCursor(1, 0); break;
            }
        } else if (key == 27) {
            break;
        } else {
            processKey(key);
        }
    }
}

void Editor::processKey(char key) {
    if (key == '\r') {
        std::string& currentLine = buffer[cursorY];
        std::string newLine = currentLine.substr(cursorX);

        currentLine = currentLine.substr(0, cursorX);
        buffer.insert(buffer.begin() + cursorY + 1, newLine);

        cursorX = 0;
        cursorY++;
    } else {
        buffer[cursorY].insert(cursorX, 1, key);
        cursorX++;
    }
}

void Editor::moveCursor(int dx, int dy) {
    cursorY += dy;
    if (cursorY < 0) cursorY = 0;
    if (cursorY >= buffer.size()) cursorY = buffer.size() - 1;

    cursorX += dx;
    if (cursorX < 0) cursorX = 0;
    if (cursorX >= buffer[cursorY].size()) cursorX = buffer[cursorY].size();
}

void Editor::render() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    DWORD screenSize = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD charsWritten;

    COORD topLeft = { 0, 0 };

    FillConsoleOutputCharacter(hOut, ' ', screenSize, topLeft, &charsWritten);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, screenSize, topLeft, &charsWritten);
    
    SetConsoleCursorPosition(hOut, topLeft);

    for (const auto& line : buffer) {
        std::cout << line << std::endl;
    }

    COORD coord = { static_cast<SHORT>(cursorX), static_cast<SHORT>(cursorY) };
    SetConsoleCursorPosition(hOut, coord);
    
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}