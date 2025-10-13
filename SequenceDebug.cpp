#include "Sequence.h"

/*
 * Greg Rosen
 * Project 3: Sequence
 * Tests for implementation of Sequence Class
 */

void emptyTest();
void SeqManipTest();
void memLeakTest();

int main() {
    emptyTest();
    SeqManipTest();
    memLeakTest();
    std::cout << "____Testing Complete____";
    return 0;
}

/*
 * Tests for memory leaks of constructors/destructors and methods of Sequence/SequenceNode classes
 */
void memLeakTest() {
    size_t i = 0;
    constexpr size_t LOOP_LIMIT = 1e6; // # iterations for loops for testing
    std::cout << "____Testing for memory leaks____" << std::endl;
    std::cout << "Testing for Constructor(s)/destructors, assignment overload, and subscript overload..." << std::endl;
    for (i = 0; i < LOOP_LIMIT; ++i) {
        const Sequence testSeq(10);
        Sequence copySeq1(testSeq);
        Sequence copySeq2(8);
        copySeq2=testSeq;
    }
    std::cout << "Complete" << std::endl;
    std::cout << "Testing for remaining methods..." << std::endl;
    for (i = 0; i < LOOP_LIMIT; ++i) {
        Sequence testSeq(5);
        testSeq[0] = "zero";
        testSeq[1] = "one";
        testSeq[2] = "two";
        testSeq[3] = "three";
        testSeq[4] = "four";
        testSeq.push_back("Blarg");
        testSeq.pop_back();
        testSeq.push_front("Blarg");
        testSeq.pop_front();
        testSeq.insert(0,"Blarg");
        testSeq.erase(0);
        testSeq.insert(4,"Blarg");
        testSeq.erase(4);
        testSeq.insert(2,"Blarg");
        testSeq.erase(2);
        testSeq.erase(0,2);
        testSeq.push_front("one");
        testSeq.push_front("zero");
        testSeq.erase(3,2);
        testSeq.push_back("three");
        testSeq.push_back("four");
        testSeq.erase(1,3);
        testSeq.insert(1,"three");
        testSeq.insert(1,"two");
        testSeq.insert(1,"one");
        testSeq.clear();
    }
    std::cout << "Complete" << std::endl;
}

/*
 * Tests for methods for manipulating Sequence object
 */
void SeqManipTest() {
    Sequence testSeq(5);
    std::cout << "____Testing behavior of parameterized-constructed sequence of size 5____" << std::endl;
    std::cout << "Size is..." << testSeq.size() << std::endl;
    std::cout << "Sequence is empty?..." << (testSeq.empty()?"true":"false") << std::endl;
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Partially Filled Sequence..." << std::endl;
    testSeq[0] = "zero";
    testSeq[3] = "three";
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Negative index in brackets should throw exception..." << std::endl;
    try {
        testSeq[-1] = "-one";
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "OOB positive index in brackets should throw exception..." << std::endl;
    try {
        testSeq[5] = "five";
    } catch (std::exception&) {
        std::cout << "Exception thrown" << std::endl;
    }
    std::cout << "Fill sequence using brackets..." << std::endl;
    testSeq[1] = "one";
    testSeq[2] = "two";
    testSeq[4] = "four";
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Remove elements one-by-one using pop_back..." << std::endl;
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_back();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_back();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_back();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_back();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_back();
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "pop_back should throw exception on empty sequence...";
    try {
        testSeq.pop_back();
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Add elements back one-by-one using push_back..." << std::endl;
    testSeq.push_back("zero");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_back("one");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_back("two");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_back("three");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_back("four");
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Remove elements one-by-one using pop_front..." << std::endl;
    testSeq.pop_front();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_front();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_front();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_front();
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.pop_front();
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "pop_front should throw exception on empty sequence...";
    try {
        testSeq.pop_front();
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Add elements back one-by-one using push_front..." << std::endl;
    testSeq.push_front("four");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_front("three");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_front("two");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_front("one");
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_front("zero");
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Erase from front..." << std::endl;
    testSeq.erase(0);
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Insert at front..." << std::endl;
    testSeq.insert(0,"zero");
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Erase from back..." << std::endl;
    testSeq.erase(4);
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Insert at back(should push tail one spot further)..." << std::endl;
    testSeq.insert(3,"four");
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Correct order..." << std::endl;
    testSeq[3] = "three";
    testSeq[4] = "four";
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Erase from middle..." << std::endl;
    testSeq.erase(2);
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Insert at middle..." << std::endl;
    testSeq.insert(2,"two");
    std::cout << "Sequence: " << testSeq << std::endl;
    std::cout << "Test erase(range) from 0(beginning) to 1..." << std::endl;
    testSeq.erase(0,2);
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_front("one");
    testSeq.push_front("zero");
    std::cout << "Test erase(range) from 3 to 4(end)..." << std::endl;
    testSeq.erase(3,2);
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.push_back("three");
    testSeq.push_back("four");
    std::cout << "Test erase(range) from 1 to 3(end)..." << std::endl;
    testSeq.erase(1,3);
    std::cout << "Sequence: " << testSeq << std::endl;
    testSeq.insert(1,"three");
    testSeq.insert(1,"two");
    testSeq.insert(1,"one");
    std::cout << "Erase should throw exception if index negative...";
    try {
        testSeq.erase(-1);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Erase should throw exception if index OOB...";
    try {
        testSeq.erase(5);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Insert should throw exception if index negative...";
    try {
        testSeq.insert(-1, "-one");
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Insert should throw exception if index OOB...";
    try {
        testSeq.insert(5, "five");
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Erase(range) should throw exception if count zero...";
    try {
        testSeq.erase(1, 0);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Erase(range) should throw exception if position negative...";
    try {
        testSeq.erase(-1, 1);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Erase(range) should throw exception if position OOB...";
    try {
        testSeq.erase(5, 1);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Erase(range) should throw exception if final removal index OOB...";
    try {
        testSeq.erase(3, 3);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Making assignment copy of sequence..." << std::endl;
    Sequence testCopy = testSeq;
    std::cout << "Copy Sequence: " << testCopy << std::endl;
    std::cout << "Orig Sequence: " << testSeq << std::endl;
    std::cout << "Changing element of copy sequence..." << std::endl;
    testCopy[2] = "Different";
    std::cout << "Copy Sequence: " << testCopy << std::endl;
    std::cout << "Orig Sequence: " << testSeq << std::endl;
    testCopy[2] = "two";
    std::cout << "Changing element of original sequence..." << std::endl;
    testSeq[2] = "Different";
    std::cout << "Copy Sequence: " << testCopy << std::endl;
    std::cout << "Orig Sequence: " << testSeq << std::endl;
    testSeq[2] = "two";
    std::cout << "Clear copy sequence..." << std::endl;
    testCopy.clear();
    std::cout << "Copy Sequence: " << testCopy << std::endl;
    std::cout << "Orig Sequence: " << testSeq << std::endl;
}

/*
 * Tests for correct operation of Sequence methods when Sequence is empty
 */
void emptyTest() {
    Sequence testSeq;
    std::cout << "____Testing behavior of default-constructed empty sequence____" << std::endl;
    std::cout << "Subscript operator should throw exception..." << std::endl;
    try {
        std::cout << testSeq[0] << std::endl;
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Stream insertion operator should return <>..." << std::endl;
    std::cout << testSeq << std::endl;
    std::cout << "Front method should throw exception..." << std::endl;
    try {
        std::cout << testSeq.front() << std::endl;
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "Back method should throw exception..." << std::endl;
    try {
        std::cout << testSeq.back() << std::endl;
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "size method should return 0..." << std::endl;
    std::cout << "size method returns..." << testSeq.size() << std::endl;
    std::cout << "empty method should return true..." << std::endl;
    std::cout << "empty method returns..." << (testSeq.empty()?"true":"false") << std::endl;
    std::cout << "insert method should throw exception..." << std::endl;
    try {
        testSeq.insert(0, "Hello");
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "pop-front method should throw exception..." << std::endl;
    try {
        testSeq.pop_front();
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "pop-back method should throw exception..." << std::endl;
    try {
        testSeq.pop_back();
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "erase method should throw exception..." << std::endl;
    try {
        testSeq.erase(0);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "erase(range) method should throw exception..." << std::endl;
    try {
        testSeq.erase(0, 5);
    } catch (std::exception&) {
        std::cout << "Exception thrown!" << std::endl;
    }
    std::cout << "clear method should leave sequence unchanged" << std::endl;
    testSeq.clear();
    std::cout << "Is sequence still empty..." << (testSeq.empty()?"true":"false") << std::endl;
    std::cout << "self-assignment should leave sequence unchanged" << std::endl;
    testSeq = testSeq;
    std::cout << "Is sequence still empty..." << (testSeq.empty()?"true":"false") << std::endl;
    std::cout << "Assigning empty sequence to another sequence should make that sequence empty..." << std::endl;
    Sequence seqToBeMadeEmpty(3);
    std::cout << "Is new sequence empty..." << (seqToBeMadeEmpty.empty()?"true":"false") << std::endl;
    seqToBeMadeEmpty = testSeq;
    std::cout << "After assignment, is new sequence now empty..." << (seqToBeMadeEmpty.empty()?"true":"false") << std::endl;
}

// Comment here to make change to SequenceDebug.cpp to test commit process from within CLion