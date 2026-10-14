// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa6
// List.cpp 
// Implementation file for the List ADT (doubly linked list)

#include <iostream>
#include "List.h"
#include <stdexcept>

// Node Constructor
List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

// List Constructor
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
}

// Copy Constructor
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;

    Node* temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        insertBefore(temp->data);
        temp = temp->next;
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions
int List::length() const { return num_elements; }
ListElement List::front() const { return frontDummy->next->data; }
ListElement List::back() const { return backDummy->prev->data; }
int List::position() const { return pos_cursor; }
ListElement List::peekNext() const { return afterCursor->data; }
ListElement List::peekPrev() const { return beforeCursor->data; }

// Manipulation functions
void List::clear() {
    moveFront();
    while (num_elements > 0) eraseAfter();
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext() {
    if (afterCursor == backDummy) throw std::runtime_error("moveNext(): Cursor at back.");
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (beforeCursor == frontDummy) throw std::runtime_error("movePrev(): Cursor at front.");
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    num_elements++;
    pos_cursor++;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements)
        throw std::runtime_error("setAfter(): Cursor at back.");
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0)
        throw std::runtime_error("setBefore(): Cursor at front.");
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (afterCursor == backDummy) throw std::runtime_error("eraseAfter(): No element after cursor.");
    Node* temp = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (beforeCursor == frontDummy) throw std::runtime_error("eraseBefore(): No element before cursor.");
    Node* temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements--;
    pos_cursor--;
}

// Additional functions
int List::findNext(ListElement x) {
    while (afterCursor != backDummy) {
        if (afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    moveBack();
    return -1;
}

int List::findPrev(ListElement x) {
    while (beforeCursor != frontDummy) {
        if (beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    moveFront();
    return -1;
}

void List::cleanup() {
    Node* current = frontDummy->next;
    int originalPos = pos_cursor;
    int index = 0;

    while (current != backDummy) {
        Node* runner = current->next;
        int runnerIndex = index + 1;

        while (runner != backDummy) {
            if (runner->data == current->data) {
                Node* duplicate = runner;
                runner->prev->next = runner->next;
                runner->next->prev = runner->prev;
                runner = runner->next;
                delete duplicate;
                num_elements--;
                if (runnerIndex < originalPos)
                    originalPos--;
            } else {
                runner = runner->next;
                runnerIndex++;
            }
        }
        current = current->next;
        index++;
    }

    moveFront();
    for (int i = 0; i < originalPos; i++) {
        moveNext();
    }
}

List List::concat(const List& L) const {
    List newList;
    Node* temp = this->frontDummy->next;
    while (temp != this->backDummy) {
        newList.insertBefore(temp->data);
        temp = temp->next;
    }
    temp = L.frontDummy->next;
    while (temp != L.backDummy) {
        newList.insertBefore(temp->data);
        temp = temp->next;
    }
    newList.moveFront();
    return newList;
}

std::string List::to_string() const {
    std::string result = "(";
    Node* temp = frontDummy->next;
    while (temp != backDummy) {
        result += std::to_string(temp->data);
        if (temp->next != backDummy) result += ", ";
        temp = temp->next;
    }
    result += ")";
    return result;
}

bool List::equals(const List& R) const {
    if (this->num_elements != R.num_elements) return false;
    Node* a = this->frontDummy->next;
    Node* b = R.frontDummy->next;
    while (a != this->backDummy && b != R.backDummy) {
        if (a->data != b->data) return false;
        a = a->next;
        b = b->next;
    }
    return (a == this->backDummy && b == R.backDummy);
}

// Overloaded Operators
std::ostream& operator<<(std::ostream& out, const List& L) {
    out << L.to_string();
    return out;
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        clear();
        Node* temp = L.frontDummy->next;
        while (temp != L.backDummy) {
            insertBefore(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}