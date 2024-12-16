#ifndef UNABLE_OPEN_FILE_EXCEPTION_HPP
#define UNABLE_OPEN_FILE_EXCEPTION_HPP

#include <exception>
#include <string>

class UnableToOpenFileException : public std::exception {
private:
    std::string message;

public:
    UnableToOpenFileException();
    virtual const char* what() const noexcept override;
};

#endif
