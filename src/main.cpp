// src/main.cpp

#include "LinkedListStack.hpp"           // Include the LinkedListStack header
#include "CannotEvaluateException.hpp"  // Include the custom exception for evaluation errors
#include "StackEmptyException.hpp"      // Include the custom exception for empty stack

#include <iostream>    // For std::cout and std::cerr
#include <vector>      // For std::vector
#include <string>      // For std::string

// Declaration of postfixCalculator function
unsigned postfixCalculator(const std::vector<std::string>& entries);

int main()
{
    try
    {
        // Demonstrate LinkedListStack with integer type
        LinkedListStack<int> stack;
        stack.push(10); // Push 10 onto the stack
        stack.push(20); // Push 20 onto the stack
        stack.push(30); // Push 30 onto the stack

        std::cout << "Stack size: " << stack.size() << std::endl;     // Output: 3
        std::cout << "Top element: " << stack.top() << std::endl;    // Output: 30

        stack.pop(); // Remove the top element (30)
        std::cout << "After pop, top element: " << stack.top() << std::endl; // Output: 20

        // Demonstrate the copy constructor
        LinkedListStack<int> copiedStack = stack; // Create a copy of 'stack'
        std::cout << "Copied stack top element: " << copiedStack.top() << std::endl; // Output: 20

        // Demonstrate postfixCalculator with valid expressions
        std::vector<std::string> entries1 = {"5", "3", "*"};
        unsigned result1 = postfixCalculator(entries1);
        std::cout << "Postfix calculator result 1: " << result1 << std::endl; // Expected Output: 15

        std::vector<std::string> entries2 = {"5", "3", "2", "*", "-"};
        unsigned result2 = postfixCalculator(entries2);
        std::cout << "Postfix calculator result 2: " << result2 << std::endl; // Expected Output: 5 - (3 * 2) = 5 - 6 = (unsigned underflow)

        // Demonstrate postfixCalculator with an invalid expression (should throw exception)
        std::vector<std::string> entries3 = {"5", "3", "2"};
        unsigned result3 = postfixCalculator(entries3); // This should throw CannotEvaluateException
        std::cout << "Postfix calculator result 3: " << result3 << std::endl;
    }
    catch (const StackEmptyException& e)
    {
        // Handle exceptions related to stack operations
        std::cerr << "StackEmptyException: " << e.what() << std::endl;
    }
    catch (const CannotEvaluateException& e)
    {
        // Handle exceptions related to postfix evaluation
        std::cerr << "CannotEvaluateException: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        // Handle any other standard exceptions
        std::cerr << "Other exception: " << e.what() << std::endl;
    }

    return 0; // Indicate successful execution
}
