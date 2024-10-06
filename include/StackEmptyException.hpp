#ifndef STACK_EMPTY_EXCEPTION_HPP
#define STACK_EMPTY_EXCEPTION_HPP

#include <exception>

// Exception thrown when attempting to access or modify an empty stack
class StackEmptyException : public std::exception
{
public:
    // Override the what() function to provide an error message
    virtual const char* what() const noexcept override
    {
        return "Stack is empty.";
    }
};

#endif // STACK_EMPTY_EXCEPTION_HPP
