#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <iostream>

class SequenceNode;

class Sequence {
    private:
        SequenceNode* head;
        SequenceNode* tail;
        size_t length;

    public:
        Sequence(size_t sz = 0); // Constructor (If sz parameter is omitted, also acts as default constructor).
        Sequence(const Sequence& s); // Copy Constructor

        ~Sequence(); // Destructor

        Sequence& operator=(const Sequence& s); // Assignment Operator Overload
        std::string& operator[](size_t position); // Subscript Operator Overload
        friend std::ostream& operator<<(std::ostream& os, const Sequence& s); // Stream Insertion Operator Overload

        std::string front() const; // Getter for item of first node in Sequence
        std::string back() const; // Getter for item of last node in Sequence
        size_t size() const; // Getter for length

        bool empty() const; // Predicate for whether Sequence is empty

        void push_back(std::string item); // Append node with item to end of Sequence
        void insert(size_t position, std::string item); // Insert node with item at position

        void pop_back(); // Remove node at end of Sequence
        void erase(size_t position); // Removes node at position
        void erase(size_t position, size_t count); // Removes count sequential nodes starting at position
        void clear(); // Removes all nodes, leaving Sequence empty

};

class SequenceNode {
    public: 
        SequenceNode* next; // pointer to next Node.
        SequenceNode* prev; // pointer to previous Node.
        std::string item; // the element being stored in the node
        SequenceNode();
        SequenceNode(std::string item);
};

#endif // SEQUENCE_H