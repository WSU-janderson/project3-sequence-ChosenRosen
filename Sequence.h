#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <iostream>

/*
 * Greg Rosen
 * Project 3: Sequence
 * Declaration for Sequence class
 */

/*
 * Sequence: A dynamic array of string elements.
 * Elements may be added/removed/altered at will.
 * Implemented as a doubly-linked list.
 */
class Sequence {
    private:
        /*
         * SequenceNode: Node of a sequence
         * Implemented as a private nested class of Sequence
         */
        class SequenceNode {
        public:
            SequenceNode* next; // pointer to next node
            SequenceNode* prev; // pointer to previous node
            std::string item; // Element stored in the node

            explicit SequenceNode(std::string item = "");
        };

        SequenceNode* head; // Pointer to first node of sequence. Nullptr if sequence is empty.
        SequenceNode* tail; // Pointer to back node of sequence. Nullptr if sequence is empty.
        size_t length; // Number of elements in sequence. 0 if sequence is empty.

        [[nodiscard]] SequenceNode* getNodePtr(size_t position) const; // Getter for pointer to node at given position

    public:
        explicit Sequence(size_t sz = 0); // Default/Parameterized Constructor
        Sequence(const Sequence& s); // Copy Constructor

        ~Sequence(); // Destructor

        Sequence& operator=(const Sequence& s); // Assignment Operator overload
        std::string& operator[](size_t position) const; // Subscript Operator overload
        friend std::ostream& operator<<(std::ostream& os, const Sequence& s); // Stream Insertion Operator overload

        [[nodiscard]] std::string front() const; // Getter first element in sequence
        [[nodiscard]] std::string back() const; // Getter for last element in sequence
        [[nodiscard]] size_t size() const; // Getter for size of sequence

        [[nodiscard]] bool empty() const; // Predicate for whether sequence is empty

        void push_front(std::string item); // Prepend node with given item to front of sequence
        void push_back(std::string item); // Append node with given item to end of Sequence
        void insert(size_t position, const std::string& item); // Insert node with given item at given position

        void pop_front(); // Remove node from the front of sequence
        void pop_back(); // Remove node from the end of sequence
        void erase(size_t position); // Remove node at given position from sequence
        void erase(size_t position, size_t count); // Remove range of sequential nodes from sequence
        void clear(); // Remove all nodes from sequence, leaving it empty
};

#endif // SEQUENCE_H