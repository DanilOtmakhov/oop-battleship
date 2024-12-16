#include "../include/FileWrapper.hpp"

FileWrapper::FileWrapper(const std::string& filename) : file(filename) {};

FileWrapper::~FileWrapper() {
    if (file.is_open())
        file.close();
}

void FileWrapper::read(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file >> j;
}

void FileWrapper::write(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file << j.dump(4);
}
