#pragma once

#include <string>

namespace FileUtils {
    bool validFilePath(const std::string& filePath);
    std::string readFile(const std::string& filePath);
    bool validDirPath(const std::string& filePath);

    uint64_t fileSize(const std::string& path);
    uint64_t lastModified(const std::string& path);
}