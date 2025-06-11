#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <vector>
#include <string>

class TextBuffer {
public:
    TextBuffer();
    void insertChar(int row, int col, char ch);
    void deleteChar(int row, int col);
    void insertLine(int row);
    void deleteLine(int row);
    const std::string& getLineConst(int row) const;
    std::string& getLineMutable(int row);
    int lineLength(int row) const;
    int lineCount() const;

private:
    std::vector<std::string> lines;
};

#endif