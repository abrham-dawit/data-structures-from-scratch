//-----------------------------------------------------------------------------
// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa8
// Dictionary.cpp
// Implementation file for Dictionary ADT based on a Red-Black Tree (RBT)
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

#define RED 1
#define BLACK 0

// Node Constructor
Dictionary::Node::Node(keyType k, valType v)
    : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

// Helper Functions

// inOrderString(): builds sorted string "key : value"
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString(): builds pre-order string, tags RED nodes
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        if (R->color == RED) s += " (RED)";
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// search(): binary search for key
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) return R;
    if (k < R->key) return search(R->left, k);
    return search(R->right, k);
}

// findMin(): leftmost node
Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R->left != nil) R = R->left;
    return R;
}

// findMax(): rightmost node
Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R->right != nil) R = R->right;
    return R;
}

// findNext(): in-order successor
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) return findMin(N->right);
    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

// findPrev(): in-order predecessor
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) return findMax(N->left);
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

// postOrderDelete(): clear memory
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// preOrderCopy(): deep copies tree from R
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != nil) {
        setValue(R->key, R->val);  
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

Dictionary::Node* Dictionary::clone(Node* R, Node* parent, Node* origNil) {
    if (R == origNil) return nil;

    Node* newNode = new Node(R->key, R->val);
    newNode->color = R->color;
    newNode->parent = parent;
    newNode->left = clone(R->left, newNode, origNil);
    newNode->right = clone(R->right, newNode, origNil);
    return newNode;
}


//Red-Black Tree Functions

// LeftRotate(): rotate node N left
void Dictionary::LeftRotate(Node* N) {
    Node* y = N->right;
    N->right = y->left;
    if (y->left != nil) y->left->parent = N;
    y->parent = N->parent;
    if (N->parent == nil) root = y;
    else if (N == N->parent->left) N->parent->left = y;
    else N->parent->right = y;
    y->left = N;
    N->parent = y;
}

// RightRotate(): rotate node N right
void Dictionary::RightRotate(Node* N) {
    Node* y = N->left;
    N->left = y->right;
    if (y->right != nil) y->right->parent = N;
    y->parent = N->parent;
    if (N->parent == nil) root = y;
    else if (N == N->parent->right) N->parent->right = y;
    else N->parent->left = y;
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUp(): fix tree after insert
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node* U = N->parent->parent->right;
            if (U->color == RED) {
                N->parent->color = BLACK;
                U->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        } else {
            Node* U = N->parent->parent->left;
            if (U->color == RED) {
                N->parent->color = BLACK;
                U->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant(): replaces u with v
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

// RB_DeleteFixUp(): fix tree after deletion
void Dictionary::RB_DeleteFixUp(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// RB_Delete(): removes node from RBT
void Dictionary::RB_Delete(Node* z) {
    Node* y = z;
    Node* x;
    int y_original_color = y->color;
    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    } else {
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        RB_DeleteFixUp(x);
    delete z;
}

//Constructor / Destructor

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nil;
    root = current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) : Dictionary() {
    root = clone(D.root, nil, D.nil);
    num_pairs = D.num_pairs;
    current = nil;
}


Dictionary::~Dictionary() {
    clear();
    delete nil;
}

//Access Functions

int Dictionary::size() const { return num_pairs; }

bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nil);
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil)
        throw std::logic_error("Dictionary: getValue(): key not found");
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return (current != nil);
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent())
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent())
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    return current->val;
}

//Manipulation

void Dictionary::clear() {
    postOrderDelete(root);
    root = current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            return;
        }
        if (k < x->key) x = x->left;
        else x = x->right;
    }
    Node* z = new Node(k, v);
    z->parent = y;
    z->left = z->right = nil;
    if (y == nil) root = z;
    else if (k < y->key) y->left = z;
    else y->right = z;
    z->color = RED;
    RB_InsertFixUp(z);
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* z = search(root, k);
    if (z == nil)
        throw std::logic_error("Dictionary: remove(): key not found");
    if (z == current) current = nil;
    RB_Delete(z);
    num_pairs--;
}

void Dictionary::begin() {
    if (root != nil) current = findMin(root);
}

void Dictionary::end() {
    if (root != nil) current = findMax(root);
}

void Dictionary::next() {
    if (!hasCurrent())
        throw std::logic_error("Dictionary: next(): current undefined");
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent())
        throw std::logic_error("Dictionary: prev(): current undefined");
    current = findPrev(current);
}

//Other Functions

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    return (this->to_string() == D.to_string());
}

//Overloaded Operators

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        root = clone(D.root, nil, D.nil);
        num_pairs = D.num_pairs;
        current = nil;
    }
    return *this;
}