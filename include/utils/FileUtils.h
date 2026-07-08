#pragma once

#include <string>

namespace FileUtils {
    bool validFilePath(const std::string& filePath);
    std::string readFile(const std::string& filePath);
}