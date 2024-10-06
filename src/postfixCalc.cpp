// src/postfixCalc.cpp

#include "LinkedListStack.hpp"           // Include the LinkedListStack header
#include "CannotEvaluateException.hpp"  // Include the custom exception for evaluation errors
#include "StackEmptyException.hpp"      // Include the custom exception for empty stack

#include <vector>       // For std::vector
#include <string>       // For std::string
#include <cctype>       // For std::isdigit
#include <cstdlib>      // For std::stoul
#include <stdexcept>    // For std::invalid_argument and std::out_of_range

// Function prototype as per project description
[[nodiscard]] unsigned postfixCalculator(const std::vector<std::string>& entries)
{
    // Create a stack to hold unsigned integers during evaluation
    LinkedListStack<unsigned> stack;

    // Iterate through each entry in the postfix expression
    for (const std::string& entry : entries)
    {
        // Check if the entry is an operator
        if (entry == "+" || entry == "-" || entry == "*" || entry == "/")
        {
            try
            {
                // Pop the top two elements from the stack as operands
                unsigned operand2 = stack.top();
                stack.pop();
                unsigned operand1 = stack.top();
                stack.pop();

                unsigned result = 0; // Variable to store the result of the operation

                // Perform the corresponding arithmetic operation
                if (entry == "+")
                {
                    result = operand1 + operand2;
                }
                else if (entry == "-")
                {
                    result = operand1 - operand2;
                }
                else if (entry == "*")
                {
                    result = operand1 * operand2;
                }
                else if (entry == "/")
                {
                    // Division by zero is not expected as per project specifications
                    result = operand1 / operand2;
                }

                // Push the result back onto the stack
                stack.push(result);
            }
            catch (const StackEmptyException&)
            {
                // If there are not enough operands for the operator, throw an evaluation exception
                throw CannotEvaluateException();
            }
        }
        else
        {
            // Assume the entry is a number and attempt to convert it to unsigned integer
            try
            {
                unsigned number = std::stoul(entry); // Convert string to unsigned long
                stack.push(number);                   // Push the number onto the stack
            }
            catch (const std::invalid_argument&)
            {
                // If the conversion fails due to invalid format, throw an evaluation exception
                throw CannotEvaluateException();
            }
            catch (const std::out_of_range&)
            {
                // If the number is too large to fit in an unsigned int, throw an evaluation exception
                throw CannotEvaluateException();
            }
        }
    }

    // After processing all entries, the stack should have exactly one element (the result)
    if (stack.size() == 1)
    {
        return stack.top(); // Return the final result
    }
    else
    {
        // If there's more than one element, the expression is invalid
        throw CannotEvaluateException();
    }
}
