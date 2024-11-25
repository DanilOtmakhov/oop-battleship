#ifndef OUT_OF_BOUNDS_EXCEPTION_HPP
#define OUT_OF_BOUNDS_EXCEPTION_HPP

#include <exception>
#include <string>
class OutOfBoundsException : public std::exception {
	private:
		std::string message;

	public:
		OutOfBoundsException();
		virtual const char* what() const noexcept override;
};

#endif
