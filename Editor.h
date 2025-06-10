#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>

class Editor {
public:
    Editor();
    void run();

private:
    void processKey(char key);
    void moveCursor(int dx, int dy);
    void render();

    std::vector<std::string> buffer;
    int cursorX;
    int cursorY;
};

#endif