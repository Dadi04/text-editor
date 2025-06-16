#include "Editor.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

Editor::Editor() : running(true) {
    enableAnsiEscapeCodes();
}

void Editor::run() {
    renderer.draw(buffer, cursor, selection);
    
    while(running) {
        Key key = inputHandler.getKey();
        processKey(key);
        renderer.draw(buffer, cursor, selection);
    }
}

void Editor::processKey(Key key) {
    int x = cursor.getX();
    int y = cursor.getY();

    switch (key.type) {
        case KeyType::ArrowUp:
            if (selection.isActive()) {
                int sRow = std::min(selection.getStartRow(), selection.getEndRow());
                int sCol = (selection.getStartRow() <= selection.getEndRow()) ? selection.getStartCol() : selection.getEndCol();
                cursor.setPosition(sCol, sRow);
                selection.clear();
            } else {
                cursor.moveUp(buffer);
            }
            break;
        case KeyType::ArrowDown:
            if (selection.isActive()) {
                int eRow = std::max(selection.getStartRow(), selection.getEndRow());
                int eCol = (selection.getStartRow() <= selection.getEndRow()) ? selection.getEndCol() : selection.getStartCol();
                cursor.setPosition(eCol, eRow);
                selection.clear();
            } else {
                cursor.moveDown(buffer);
            }
            break;
        case KeyType::ArrowLeft:
            if (selection.isActive()) {
                int sRow = std::min(selection.getStartRow(), selection.getEndRow());
                int sCol = (selection.getStartRow() <= selection.getEndRow()) ? selection.getStartCol() : selection.getEndCol();
                cursor.setPosition(sCol, sRow);
                selection.clear();
            } else {
                cursor.moveLeft(buffer);
            }
            break;
        case KeyType::ArrowRight:
            if (selection.isActive()) {
                int eRow = std::max(selection.getStartRow(), selection.getEndRow());
                int eCol = (selection.getStartRow() <= selection.getEndRow()) ? selection.getEndCol() : selection.getStartCol();
                cursor.setPosition(eCol, eRow);
                selection.clear();
            } else {
                cursor.moveRight(buffer);
            }
            break;
        case KeyType::Enter: {
            if (selection.isActive()) {
                int firstRow = 0, firstCol = 0;
                int lastRow = buffer.lineCount() - 1;
                int lastCol = buffer.lineLength(lastRow);
                
                bool selectingAll = (selection.getStartRow() == firstRow && 
                                   selection.getStartCol() == firstCol &&
                                   selection.getEndRow() == lastRow && 
                                   selection.getEndCol() == lastCol);
                
                if (selectingAll) {
                    buffer.clear();
                    buffer.insertLine(0);
                    buffer.getLineMutable(0) = "";
                    buffer.insertLine(1);
                    buffer.getLineMutable(1) = "";
                    cursor.setPosition(0, 1);
                    selection.clear();
                    break;
                }
            }
            
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
            if (selection.isActive()) {
                int firstRow = 0, firstCol = 0;
                int lastRow = buffer.lineCount() - 1;
                int lastCol = buffer.lineLength(lastRow);
                
                bool selectingAll = (selection.getStartRow() == firstRow && 
                                   selection.getStartCol() == firstCol &&
                                   selection.getEndRow() == lastRow && 
                                   selection.getEndCol() == lastCol);
                
                if (selectingAll) {
                    buffer.clear();
                    buffer.insertLine(0);
                    buffer.getLineMutable(0) = "";
                    cursor.setPosition(0, 0);
                    selection.clear();
                    break;
                }
            }
            
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
        case KeyType::CtrlA: {
            if (buffer.lineCount() == 0) break;
            
            int firstRow = 0;
            int firstCol = 0;

            int lastRow = buffer.lineCount() - 1;
            int lastCol = buffer.lineLength(lastRow);
            
            selection.setStart(firstRow, firstCol);
            selection.setEnd(lastRow, lastCol);
            break;
        }
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
            if (selection.isActive()) {
                int sRow = std::min(selection.getStartRow(), selection.getEndRow());
                int eRow = std::max(selection.getStartRow(), selection.getEndRow());
                int sCol = std::min(selection.getStartCol(), selection.getEndCol());
                int eCol = std::max(selection.getStartCol(), selection.getEndCol());

                if (sRow == eRow) {
                    buffer.deleteRange(sRow, sCol, eCol);
                    cursor.setPosition(sCol, sRow);
                } else {
                    std::string startLine = buffer.getLineMutable(sRow);
                    std::string endLine = buffer.getLineMutable(eRow);
                    startLine = startLine.substr(0, sCol) + endLine.substr(eCol);
                    
                    buffer.getLineMutable(sRow) = startLine;
                    
                    for (int i = sRow + 1; i <= eRow; i++) {
                        buffer.deleteLine(sRow + 1);
                    }
                    cursor.setPosition(sCol, sRow);
                }

                selection.clear();
                x = cursor.getX();
                y = cursor.getY();
            }

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