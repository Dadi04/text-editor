#include "TextBuffer.h"
#include <stdexcept>

TextBuffer::TextBuffer() {
    lines.push_back("");
}

void TextBuffer::insertChar(int row, int col, char ch) {
    if (row >= 0 && row < lines.size()) {
        if (col >= 0 && col <= lines[row].size()) {
            lines[row].insert(col, 1, ch);
        }
    }
}

void TextBuffer::deleteChar(int row, int col) {
    if (row >= 0 && row < lines.size()) {
        if (col >= 0 && col <= lines[row].size()) {
            lines[row].erase(col - 1, 1);
        } else if (col == 0 && row > 0) {
            std::string& curr = lines[row];
            std::string& prev = lines[row - 1];
            prev += curr;
            lines.erase(lines.begin() + row);
        }
    }
}

void TextBuffer::insertLine(int row) {
    if (row >= 0 && row <= lines.size()) {
        lines.insert(lines.begin() + row, "");
    } 
}

void TextBuffer::deleteLine(int row) {
    if (row >= 0 && row < lines.size()) {
        lines.erase(lines.begin() + row);
        if (lines.empty()) {
            lines.push_back("");
        }
    }
}

const std::string& TextBuffer::getLineConst(int row) const {
    if (row >= 0 && row < lines.size()) {
        return lines[row];
    }
    static const std::string empty = "";
    return empty;
}

std::string &TextBuffer::getLineMutable(int row) {
    static std::string dummy = "";
    if (row >= 0 && row < lines.size()) {
        return lines[row];
    }
    return dummy;

}

int TextBuffer::lineLength(int row) const {
    if (row >= 0 && row < lines.size()) {
        return lines[row].size();
    }
    return 0;
}

int TextBuffer::lineCount() const {
    return lines.size();
}