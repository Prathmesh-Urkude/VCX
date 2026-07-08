#pragma once

#include <string>

namespace FileUtils {
    bool validPath(const std::string& filePath);
    std::string readFile(const std::string& filePath);
}