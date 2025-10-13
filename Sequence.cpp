#include "Sequence.h"
#include <exception>
#include <utility>

/*
 * Greg Rosen
 * Project 3: Sequence
 * Implementation for Sequence and SequenceNode classes
 */

/*
 * Constructor
 * Creates a sequence of sz nodes with empty strings as items.
 * If sz = 0 or sz parameter is omitted, effectively default constructor.
 * WARNING: default constructor creates empty sequence with head and tail fields remaining nullptr.
 */
Sequence::Sequence(const size_t sz) : head(nullptr), tail(nullptr), length(0) {
    for (size_t i = 0; i < sz; ++i) {
        push_back("");
    }
}

/*
 * Copy Constructor
 * Creates a (deep) copy of sequence s
 */
Sequence::Sequence(const Sequence& s) {
    if (s.empty()) { // If s is empty, then copy sequence will also be empty
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }
    else {
        this->length = s.length;
        const SequenceNode* origCurr = s.head; // Node of original sequence currently being handled

        // Move from head to tail of s, building duplicate sequence node-by-node
        this->head = new SequenceNode(origCurr->item);
        SequenceNode* copyCurr = this->head; // Node of copy sequence currently being handled
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

/*
 * Destructor
 * Destroys all items in the sequence and release the memory associated with the sequence
 */
Sequence::~Sequence() {
    clear();
}

/*
 * Assignment operator overload
 * The current sequence is released and replaced by a (deep) copy of sequence s.
 * A reference to the copied sequence is returned (return *this).
 */
Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {
        clear();
        Sequence temp(s); // Create temporary deep copy of s, and copy fields to this.
        this->head = temp.head;
        this->tail = temp.tail;
        this->length = temp.length;
        temp.head = nullptr; // temp head and tail must be set to nullptr to avoid deletion of copied sequence.
        temp.tail = nullptr;
        temp.length = 0; // temp length must be set to zero to ensure clear() method called by destructor works correctly.
    }
    return *this;
}

/*
 * Array subscript operator overload
 * Returns item of node at index position of sequence
 * The position satisfies ( position >= 0 && position <= last_index() )
 * Throws an exception if the position is outside the bounds of the sequence
 */
std::string& Sequence::operator[](const size_t position) const {
    return getNodePtr(position)->item;
}

/*
 * Stream insertion operator overload
 * Outputs all items of sequence as a single string to the given output stream
 * ex: For a given six-item sequence: "<4,8,15,16,23,42>"
 * Outputs <> for an empty sequence
 * This is *not* a method of the Sequence class, but instead it is a friend function
 */
std::ostream& operator<<(std::ostream& os, const Sequence& s) {
    if (s.empty()) {
        os << "<>";
    }
    else {
        const Sequence::SequenceNode* currNode = s.head;
        os << "<" + currNode->item;
        while (currNode->next != nullptr) {
            currNode = currNode->next;
            os << "," + currNode->item;
        }
        os << ">";
    }
    return os;
}

/*
 * Private helper method
 * Get a pointer to the node at position in Sequence
 * If position is in the first half of sequence, find node by traversing sequence forwards from head
 * Otherwise, traverse sequence backwards from tail (Also applies to center of odd-length sequence)
 * The position satisfies ( position >= 0 && position <= last_index() )
 * Throws an exception if the position is outside the bounds of the sequence
 */
Sequence::SequenceNode* Sequence::getNodePtr(const size_t position) const {
    if (position >= length) {
        throw std::exception();
    }
    SequenceNode* currNode;
    if (position < length / 2) {
        currNode = head;
        for (size_t i = 0; i < position; ++i) {
            currNode = currNode->next;
        }
    }
    else {
        currNode = tail;
        for (size_t i = length - 1; i > position; --i) {
            currNode = currNode->prev;
        }
    }
    return currNode;
}

/*
 * Getter for item of sequence head
 * Throws an exception if the sequence is empty
 */
std::string Sequence::front() const {
    if (empty()) {
        throw std::exception();
    }
    else {
        return head->item;
    }
}

/*
 * Getter for item of sequence tail
 * Throws an exception if the sequence is empty
 */
std::string Sequence::back() const {
    if (empty()) {
        throw std::exception();
    }
    else {
        return tail->item;
    }
}

/*
 * Return the number of elements in the sequence.
 */
size_t Sequence::size() const {
    return length;
}

/*
 * Return true if the sequence has no elements, otherwise false.
 */
bool Sequence::empty() const {
    if (length == 0) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Node with provided item is prepended to the sequence
 */
void Sequence::push_front(std::string item) {
    const auto prependNode = new SequenceNode(std::move(item));
    if (empty()) {
        head = prependNode;
        tail = head;
    }
    else {
        prependNode->next = head;
        head->prev = prependNode;
        head = prependNode;
    }
    ++length;
}

/*
 * Node with provided item is appended to the sequence
 */
void Sequence::push_back(std::string item) {
    const auto appendNode = new SequenceNode(std::move(item));
    if (empty()) {
        head = appendNode;
        tail = head;
    }
    else {
        appendNode->prev = tail;
        tail->next = appendNode;
        tail = appendNode;
    }
    ++length;
}

/*
 * Insert node with provided item at provided position in sequence
 * The position satisfies ( position >= 0 && position <= last_index() )
 * Throws an exception if the position is outside the bounds of the sequence
 */
void Sequence::insert(const size_t position, const std::string& item) {
    if (position >= length) {
        throw std::exception();
    }
    else if (position == 0) {
        push_front(item); // If insertion occurs at front of sequence
    }
    else {
        SequenceNode* nodeBeforeInsert = getNodePtr(position - 1);
        auto* insertNode = new SequenceNode(item);
        insertNode->prev = nodeBeforeInsert;
        insertNode->next = nodeBeforeInsert->next;
        nodeBeforeInsert->next = insertNode;
        insertNode->next->prev = insertNode;
        ++length;
    }
}

/*
 * head node of sequence is erased.
 * If sequence was empty, throw an exception
 */
void Sequence::pop_front() {
    if (empty()) {
        throw std::exception();
    }
    else if (length == 1) {
        clear();
    }
    else {
        const SequenceNode* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        --length;
    }
}

/*
 * tail node of sequence is erased.
 * If sequence was empty, throw an exception
 */
void Sequence::pop_back() {
    if (empty()) {
        throw std::exception();
    }
    else if (length == 1) {
        clear();
    }
    else {
        const SequenceNode* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        --length;
    }
}

/*
 * Remove node at given position from the sequence, adjusting the adjacent nodes to bridge the gap.
 * Release memory allocated for removed node, and size of sequence reduced by 1.
 * The position satisfies ( position >= 0 && position <= last_index() )
 * Throws an exception if the position is outside the bounds of the sequence
 */
void Sequence::erase(const size_t position) {
    if (position >= length) {
        throw std::exception();
    }
    else if (position == 0) {
        pop_front(); // If head of sequence is removed
    }
    else if (position == length - 1) {
        pop_back(); // If tail of sequence is removed
    }
    else {
        const SequenceNode* nodeToErase = getNodePtr(position);
        nodeToErase->prev->next = nodeToErase->next;
        nodeToErase->next->prev = nodeToErase->prev;
        delete nodeToErase;
        --length;
    }
}

/*
 * Remove count nodes from the sequence, starting from given position and proceeding to
 * index (position + count - 1)
 * Release memory allocated for removed nodes, and size of sequence is reduced by count.
 * If called with invalid position and/or count, an exception is thrown.
 */
void Sequence::erase(const size_t position, const size_t count) {
    if (count == 0 || position + count - 1 >= length) {
        throw std::exception();
    }
    else if (position == 0 && count == length) {
        clear();
    }
    else {
        const SequenceNode* nodeToErase = getNodePtr(position);
        for (int i = 0; i < count; ++i) {
            if (nodeToErase == head) { // Ensures proper handling if removal(s) start at head.
                pop_front();
                nodeToErase = head;
            }
            else if (nodeToErase == tail) { // Ensure proper handling if final removal is tail.
                pop_back();
            }
            else {
                nodeToErase->prev->next = nodeToErase->next;
                nodeToErase->next->prev = nodeToErase->prev;
                const SequenceNode* temp = nodeToErase;
                nodeToErase = nodeToErase->next;
                delete temp;
                --length;
            }
        }
    }
}

/*
 * Resets sequence to empty state, freeing all memory currently allocated for its nodes.
 */
void Sequence::clear() {
    if (!empty()) {
        const SequenceNode* currNode = this->head;
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

/*
 * SequenceNode constructor
 * Creates a SequenceNode with given item
 * If item = "" or item is omitted, effectively default constructor
 * WARNING: SequenceNode is always constructed with nullptr for next and prev.
 *
 */
Sequence::SequenceNode::SequenceNode(std::string item) : next(nullptr), prev(nullptr), item(std::move(item))
{}