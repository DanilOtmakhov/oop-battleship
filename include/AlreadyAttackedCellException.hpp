#ifndef ALREADY_ATTACKED_CELL_EXCEPTION_HPP
#define ALREADY_ATTACKED_CELL_EXCEPTION_HPP

#include <exception>
#include <string>
class AlreadyAttackedCellException : public std::exception {
    private:
        std::string message;

    public:
        AlreadyAttackedCellException();
        virtual const char* what() const noexcept override;
};

#endif
