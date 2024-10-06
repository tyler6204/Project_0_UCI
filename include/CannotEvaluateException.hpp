#ifndef CANNOT_EVALUATE_EXCEPTION_HPP
#define CANNOT_EVALUATE_EXCEPTION_HPP

#include <exception>

// Exception thrown when the postfix expression cannot be evaluated
class CannotEvaluateException : public std::exception
{
public:
    // Override the what() function to provide an error message
    virtual const char* what() const noexcept override
    {
        return "Cannot evaluate the postfix expression.";
    }
};

#endif // CANNOT_EVALUATE_EXCEPTION_HPP
