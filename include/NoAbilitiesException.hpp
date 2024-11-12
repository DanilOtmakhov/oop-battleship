#ifndef NO_ABILITIES_EXCEPTION_HPP
#define NO_ABILITIES_EXCEPTION_HPP

#include <exception>
#include <string>

class NoAbilitiesException : public std::exception {
private:
    std::string message;

public:
    NoAbilitiesException();
    virtual const char* what() const noexcept override;
};

#endif
