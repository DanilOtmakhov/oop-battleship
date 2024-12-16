#ifndef FILE_WRAPPER_HPP
#define FILE_WRAPPER_HPP

#include "UnableToOpenFileException.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

class FileWrapper {
    private:
        std::fstream file;
    public:
        FileWrapper(const std::string& filename);
        ~FileWrapper();
        void read(nlohmann::json& j);
        void write(nlohmann::json& j);
};

#endif
