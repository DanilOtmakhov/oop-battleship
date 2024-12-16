#ifndef SAVE_FILE_HASH_MISMATCH_EXCEPTION_HPP
#define SAVE_FILE_HASH_MISMATCH_EXCEPTION_HPP

#include <exception>
#include <string>

class SaveFileHashMismatchException : public std::exception {
private:
    std::string message;

public:
    SaveFileHashMismatchException();
    virtual const char* what() const noexcept override;
};

#endif
