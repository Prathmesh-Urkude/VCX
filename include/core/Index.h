#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct IndexHeader {
    char magic[4];
    uint32_t version;
    uint32_t numEntries;
};

struct IndexEntry {
    std::string filePath;
    std::string blobhash;
    std::string mode;
    uint64_t size;
    uint64_t timestamp;
};

class Index {
private:
    IndexHeader header;
    std::vector<IndexEntry> entries;
public:
    Index();

    void load();
    void save();

    void add(const IndexEntry& entry);
    void remove(const std::string& filePath);

    const std::vector<IndexEntry>& getEntries() const;
    IndexEntry* findEntry(const std::string& filePath) const;
};