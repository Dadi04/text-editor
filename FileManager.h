#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "TextBuffer.h"

class FileManager {
public:
    bool loadFile(const std::string& path, TextBuffer& buffer);
    bool saveFile(const std::string& path, const TextBuffer& buffer);
};

#endif