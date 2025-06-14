#include "FileManager.h"

#include <fstream>
#include <string>

bool FileManager::loadFile(const std::string &path, TextBuffer &buffer) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    buffer.clear();

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        if (row >= buffer.lineCount()) {
            buffer.insertLine(row);
        }
        buffer.getLineMutable(row) = line;
        row++;
    }

    return true;
}

bool FileManager::saveFile(const std::string &path, const TextBuffer &buffer) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < buffer.lineCount(); i++) {
        file << buffer.getLineConst(i);
        if (i < buffer.lineCount() - 1) {
            file << '\n';
        }
    }

    return true;
}
