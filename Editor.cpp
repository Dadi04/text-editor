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

        Key key = inputHandler.getKey();
        processKey(key);
    }
}

void Editor::processKey(Key key) {
    int x = cursor.getX();
    int y = cursor.getY();

    switch (key.type) {
        case KeyType::ArrowUp:
            cursor.moveUp(buffer);
            break;
        case KeyType::ArrowDown:
            cursor.moveDown(buffer);
            break;
        case KeyType::ArrowLeft:
            cursor.moveLeft(buffer);
            break;
        case KeyType::ArrowRight:
            cursor.moveRight(buffer);
            break;
        case KeyType::Enter: {
            std::string& line = buffer.getLineMutable(y);
            std::string newLine = line.substr(x);
            line = line.substr(0, x);

            buffer.insertLine(y + 1);
            buffer.getLineMutable(y + 1) = newLine;
            cursor.setPosition(0, y + 1);
            break;
        }
        case KeyType::Tab: {
            const std::string tab = "    ";
            for (char c : tab) {
                buffer.insertChar(y, x++, c);
            }
            cursor.setPosition(x, y);
            break;
        }
        case KeyType::Backspace: {
            if (x > 0) {
                buffer.deleteChar(y, x);
                cursor.moveLeft(buffer);
            } else if (y > 0) {
                buffer.getLineMutable(y - 1) += buffer.getLineConst(y);
                buffer.deleteLine(y);
                cursor.setPosition(buffer.lineLength(y - 1), y - 1);
            }
            break;
        }
        case KeyType::Escape: 
            renderer.clearScreen();
            running = false;
            break;
        case KeyType::CtrlA:
            // TODO: Implement select all
            break;
        case KeyType::CtrlC:
            // TODO: Implement copy
            break;
        case KeyType::CtrlX:
            // TODO: Implement cut
            break;
        case KeyType::CtrlV:
            // TODO: Implement paste
            break;
        case KeyType::CtrlZ:
            // TODO: Implement undo
            break;
        case KeyType::CtrlY:
            // TODO: Implement redo
            break;
        case KeyType::CtrlS: {
            renderer.clearScreen();
            std::cout << "Enter file name to save: ";

            std::string path;
            std::getline(std::cin, path);

            if (fileManager.saveFile(path, buffer)) {
                std::cout << "File saved. Press any key to continue...";
            } else {
                std::cout << "Failed to save file. Press any key to continue...";
            }

            _getch();
            break;
        }
        case KeyType::CtrlO: {
            renderer.clearScreen();
            std::cout << "Enter file name to open: ";

            std::string path;
            std::getline(std::cin, path);

            if (fileManager.loadFile(path, buffer)) {
                cursor.setPosition(0, 0);
                std::cout << "File loaded. Press any key to continue...";
            } else {
                std::cout << "Failed to load file. Press any key to continue...";
            }

            _getch();
            break;
        }
        case KeyType::Character:
            buffer.insertChar(y, x, key.ch);
            cursor.moveRight(buffer);
            break;
        default:
            // Unknown
            break;
    }
}

void Editor::enableAnsiEscapeCodes() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}