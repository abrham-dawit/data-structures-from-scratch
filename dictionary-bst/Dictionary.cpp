// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa7
// Dictionary.cpp
// Implementation file for the Dictionary ADT based on a Binary Search Tree

#include "Dictionary.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>

// Node Constructor
Dictionary::Node::Node(keyType k, valType v)
    : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {
}

Dictionary::Node* Dictionary::clone(Node* R, Node* parent) {
    if (R == nullptr)
        return nullptr;
    Node* newNode = new Node(R->key, R->val);
    newNode->parent = parent;
    newNode->left = clone(R->left, newNode);
    newNode->right = clone(R->right, newNode);
    return newNode;
}

// Helper Function: inOrderString
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nullptr) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// Helper Function: preOrderString
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nullptr) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// Helper Function: postOrderDelete
void Dictionary::postOrderDelete(Node* R) {
    if (R != nullptr) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// Helper Function: search
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nullptr || k == R->key)
        return R;
    if (k < R->key)
        return search(R->left, k);
    else
        return search(R->right, k);
}

// Helper Function: findMin
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nullptr)
        return nullptr;
    while (R->left != nullptr)
        R = R->left;
    return R;
}

// Helper Function: findMax
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nullptr)
        return nullptr;
    while (R->right != nullptr)
        R = R->right;
    return R;
}

// Helper Function: findNext
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nullptr)
        return nullptr;
    if (N->right != nullptr)
        return findMin(N->right);
    Node* P = N->parent;
    while (P != nullptr && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}


// Helper Function: findPrev 
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nullptr)
        return nullptr;
    if (N->left != nullptr)
        return findMax(N->left);
    Node* P = N->parent;
    while (P != nullptr && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

// Constructor: Dictionary 
Dictionary::Dictionary() {
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D) {
    root = clone(D.root, nullptr);
    num_pairs = D.num_pairs;
    current = nullptr;
}

// Destructor
Dictionary::~Dictionary() {
    clear();
}

// size()
int Dictionary::size() const {
    return num_pairs;
}

// contains()
bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nullptr);
}

// getValue()
valType& Dictionary::getValue(keyType k) const {
    Node* node = search(root, k);
    if (node == nullptr)
        throw std::logic_error("getValue(): key not found");
    return node->val;
}


// hasCurrent()
bool Dictionary::hasCurrent() const {
    return (current != nullptr);
}

// currentKey() 
keyType Dictionary::currentKey() const {
    if (current == nullptr)
        throw std::logic_error("currentKey(): current is undefined");
    return current->key;
}


// currentVal()
valType& Dictionary::currentVal() const {
    if (current == nullptr)
        throw std::logic_error("currentVal(): current is undefined");
    return current->val;
}

// clear()
void Dictionary::clear() {
    postOrderDelete(root);
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

// setValue()
void Dictionary::setValue(keyType k, valType v) {
    Node* node = search(root, k);
    if (node != nullptr) {
        // Update existing key.
        node->val = v;
    } else {
        // Insert new key-value pair.
        Node* newNode = new Node(k, v);
        Node* parent = nullptr;
        Node* temp = root;
        while (temp != nullptr) {
            parent = temp;
            if (k < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }
        newNode->parent = parent;
        if (parent == nullptr) {
            // Tree is empty.
            root = newNode;
        } else if (k < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        num_pairs++;
        if (current == nullptr) {
            current = newNode;
        }
    }
}

// remove()
void Dictionary::remove(keyType k) {
    Node* node = search(root, k);
    if (node == nullptr)
        throw std::logic_error("remove(): key not found");

    auto transplant = [this](Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr)
            v->parent = u->parent;
    };

    if (node->left == nullptr) {
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        transplant(node, node->left);
    } else {
        Node* y = findMin(node->right);
        if (y->parent != node) {
            transplant(y, y->right);
            y->right = node->right;
            if (y->right != nullptr)
                y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        if (y->left != nullptr)
            y->left->parent = y;
    }
    if (current == node)
        current = nullptr;
    delete node;
    num_pairs--;
}

// begin()
void Dictionary::begin() {
    if (root != nullptr)
        current = findMin(root);
    else
        current = nullptr;
}

// end()
void Dictionary::end() {
    if (root != nullptr)
        current = findMax(root);
    else
        current = nullptr;
}

// next()
void Dictionary::next() {
    if (current == nullptr)
        throw std::logic_error("next(): current is undefined");
    current = findNext(current);
}

// prev()
void Dictionary::prev() {
    if (current == nullptr)
        throw std::logic_error("prev(): current is undefined");
    current = findPrev(current);
}


// to_string()
std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre_string()
std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
bool Dictionary::equals(const Dictionary& D) const {
    return (this->to_string() == D.to_string());
}

// Overloaded operator<<
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    stream << D.to_string();
    return stream;
}

// Overloaded operator==
bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

// Overloaded operator=
Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        root = clone(D.root, nullptr);
        num_pairs = D.num_pairs;
        current = nullptr;
    }
    return *this;
}
 