#ifndef LINKED_LIST_STACK_HPP
#define LINKED_LIST_STACK_HPP

#include <cstddef> // For size_t
#include <stdexcept> // For std::exception
#include "StackEmptyException.hpp" // Custom exception for empty stack

// Template class for a linked-list-based stack
template <typename T>
class LinkedListStack
{
private:
    // Internal Node structure representing each element in the stack
    struct Node
    {
        T data;      // Data stored in the node
        Node* next;  // Pointer to the next node

        // Constructor to initialize a node with data and a pointer to the next node
        Node(const T& data_, Node* next_ = nullptr)
            : data(data_), next(next_) {}
    };

    Node* head;      // Pointer to the top of the stack
    size_t stackSize; // Number of elements in the stack

    // Helper function to perform a deep copy from another stack
    void copyFrom(const LinkedListStack& other)
    {
        if (other.head == nullptr)
        {
            // If the other stack is empty, initialize an empty stack
            head = nullptr;
            stackSize = 0;
            return;
        }

        // Copy the first node
        head = new Node(other.head->data);
        Node* current = head;
        Node* otherCurrent = other.head->next;

        // Iterate through the other stack and copy each node
        while (otherCurrent != nullptr)
        {
            current->next = new Node(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        // Set the size of the new stack
        stackSize = other.stackSize;
    }

    // Helper function to clear all nodes and free memory
    void clear()
    {
        while (head != nullptr)
        {
            Node* temp = head; // Temporary pointer to current node
            head = head->next; // Move head to the next node
            delete temp;       // Delete the current node
        }
        stackSize = 0; // Reset stack size
    }

public:
    // Constructor: Initializes an empty stack
    LinkedListStack()
        : head(nullptr), stackSize(0)
    {}

    // Copy Constructor: Creates a deep copy of another stack
    LinkedListStack(const LinkedListStack& st)
        : head(nullptr), stackSize(0)
    {
        copyFrom(st); // Use the helper function to copy
    }

    // Assignment Operator: Assigns one stack to another with deep copy
    LinkedListStack& operator=(const LinkedListStack& st)
    {
        if (this != &st) // Check for self-assignment
        {
            clear();      // Clear current stack
            copyFrom(st); // Copy from the other stack
        }
        return *this; // Return the current object
    }

    // Move Constructor (Deleted): Prevents move operations
    LinkedListStack(LinkedListStack&&) = delete;

    // Move Assignment Operator (Deleted): Prevents move assignments
    LinkedListStack& operator=(LinkedListStack&&) = delete;

    // Destructor: Cleans up all allocated memory
    ~LinkedListStack()
    {
        clear(); // Free all nodes
    }

    // Returns the number of elements in the stack
    [[nodiscard]] size_t size() const noexcept
    {
        return stackSize;
    }

    // Checks if the stack is empty
    [[nodiscard]] bool empty() const noexcept
    {
        return stackSize == 0;
    }

    // Returns a modifiable reference to the top element of the stack
    // Throws StackEmptyException if the stack is empty
    [[nodiscard]] T& top()
    {
        if (empty())
        {
            throw StackEmptyException();
        }
        return head->data;
    }

    // Returns a constant reference to the top element of the stack
    // Throws StackEmptyException if the stack is empty
    [[nodiscard]] const T& top() const
    {
        if (empty())
        {
            throw StackEmptyException();
        }
        return head->data;
    }

    // Pushes an element onto the top of the stack
    // Marked noexcept as it should not throw exceptions
    void push(const T& elem) noexcept
    {
        Node* newNode = new Node(elem, head); // Create a new node pointing to current head
        head = newNode;                        // Update head to the new node
        ++stackSize;                           // Increment stack size
    }

    // Removes the top element from the stack
    // Throws StackEmptyException if the stack is empty
    void pop()
    {
        if (empty())
        {
            throw StackEmptyException();
        }
        Node* temp = head;   // Temporary pointer to current head
        head = head->next;   // Move head to the next node
        delete temp;         // Delete the old head node
        --stackSize;         // Decrement stack size
    }
};

#endif // LINKED_LIST_STACK_HPP
