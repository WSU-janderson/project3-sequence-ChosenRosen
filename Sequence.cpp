#include "Sequence.h"
#include <exception>

// Creates an empty sequence (numElts == 0) or a sequence of numElts items
// indexed from 0 ... (numElts - 1).
Sequence::Sequence(size_t sz) : head(nullptr), tail(nullptr), length(sz) {
    for (int i = 0; i < sz; ++i) {
        push_back("");
    }
}

// Creates a (deep) copy of sequence s
Sequence::Sequence(const Sequence& s) {
    if (s.head == nullptr) {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }
    else {
        this->length = s.length;
        const SequenceNode* origCurr = s.head;

        this->head = new SequenceNode(origCurr->item);
        SequenceNode* copyCurr = this->head;
        while (origCurr->next != nullptr) {
            origCurr = origCurr->next;
            const auto temp = new SequenceNode(origCurr->item);
            temp->prev = copyCurr;
            copyCurr->next = temp;
            copyCurr = temp;
        }
        this->tail = copyCurr;
    }
}
// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    clear();
}

// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {
        clear();
        const auto temp = new Sequence(s);
        this->head = temp->head;
        this->tail = temp->tail;
        this->length = temp->length;
    }
    return *this;
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
std::string& Sequence::operator[](size_t position) {
    if (position<0 || position>=(length)) {
        throw std::exception();
    }
    else if (position < length / 2) {
        SequenceNode* currNode = head;
        for (int i=0; i<position; ++i) {
            currNode = currNode->next;
        }
        return currNode->item;
    }
    else {
        SequenceNode* currNode = tail;
        for (int i=length - 1; i>position; --i) {
            currNode = currNode->prev;
        }
        return currNode->item;
    }
}

// The value of item is appended to the sequence.
void Sequence::push_back(std::string item) {
    if (length == 0) {
        head = new SequenceNode(item);
        tail = head;
    }
    else {
        const auto appendNode = new SequenceNode(item);
        appendNode->prev = tail;
        tail->next = appendNode;
        tail = appendNode;
    }
    ++length;
}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    if (length == 0) {
        throw std::exception();
    }
    else {
        const SequenceNode* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        --length;
    }
}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {

}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if (head != nullptr) {
        return head->item;
    }
    else {
        return "";
    }
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if (head != nullptr) {
        return tail->item;
    }
    else {
        return "";
    }
}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    if (head == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

// Return the number of elements in the sequence.
size_t Sequence::size() const {
    return length;
}

// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
void Sequence::clear() {
    SequenceNode* currNode = this->head;
    if (currNode != nullptr) {
        while (currNode->next != nullptr) {
            const SequenceNode* target = currNode;
            currNode = currNode->next;
            delete target;
        }
        delete currNode;
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }
}

// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {

}

// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {

}

// Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
// stream. This is *not* a method of the Sequence class, but instead it is a
// friend function
std::ostream& operator<<(std::ostream& os, const Sequence& s) {

}

//default constructor, ensure next and prev are nullptr
SequenceNode::SequenceNode() : next(nullptr), prev(nullptr)
{}

// parameterized constructor, next and prev are set to nullptr and the
// node's element is set to the given value
SequenceNode::SequenceNode(std::string item) : next(nullptr), prev(nullptr), item(item)
{}