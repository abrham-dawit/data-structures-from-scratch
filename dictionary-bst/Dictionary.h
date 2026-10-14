//-----------------------------------------------------------------------------
// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa7
// Dictionary.h 
// Header file for the Dictionary ADT
//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for Dictionary ADT based on a Binary Search Tree. Includes a
// built-in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>

#ifndef DICTIONARY_H_INCLUDE_
#define DICTIONARY_H_INCLUDE_

// Exported types -------------------------------------------------------------
typedef std::string keyType;  // Keys are strings (must be comparable using <, <=, >, >=, ==, !=)
typedef int         valType;  // Values are integers

//-----------------------------------------------------------------------------
// Dictionary ADT Declaration
//-----------------------------------------------------------------------------
class Dictionary {

private:
   // Private Node struct used to implement the Binary Search Tree.
   struct Node {
      keyType key;    // The key (identifier)
      valType val;    // The associated value
      Node* parent;   // Pointer to the parent node
      Node* left;     // Pointer to the left child
      Node* right;    // Pointer to the right child
      
      // Node constructor: Initializes a node with key k and value v.
      Node(keyType k, valType v);
   };

   // Dictionary fields
   Node* nil;       // (Optional) Reserved for a sentinel; not used in this implementation.
   Node* root;      // Pointer to the root of the BST.
   Node* current;   // Iterator pointer for traversal.
   int   num_pairs; // Number of key-value pairs stored.

   // Helper Functions (Optional) ---------------------------------------------
   
   // inOrderString()
   // Recursively appends an in-order traversal string of the subtree rooted at R to s.
   // Each node is represented as: "key : value\n", arranged in sorted order.
   void inOrderString(std::string& s, Node* R) const;

   // preOrderString()
   // Recursively appends a pre-order traversal string of the subtree rooted at R to s.
   // Each node is represented by its key followed by a newline.
   void preOrderString(std::string& s, Node* R) const;

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this Dictionary,
   // attaching the copy at node N. Recursion terminates when R is null.
   void preOrderCopy(Node* R, Node* N);

   // postOrderDelete()
   // Recursively deletes all nodes in the subtree rooted at R to free memory.
   void postOrderDelete(Node* R);

   // search()
   // Recursively searches the subtree rooted at R for a node with key equal to k.
   // Returns the address of the node if found; otherwise, returns nullptr.
   Node* search(Node* R, keyType k) const;

   // findMin()
   // Returns a pointer to the leftmost node (with the smallest key) in the subtree rooted at R.
   // If R is empty, returns nullptr.
   Node* findMin(Node* R);

   // findMax()
   // Returns a pointer to the rightmost node (with the largest key) in the subtree rooted at R.
   // If R is empty, returns nullptr.
   Node* findMax(Node* R);

   // findNext()
   // Returns the in-order successor of node N (the next node in sorted order).
   // If N is the rightmost node or is nullptr, returns nullptr.
   Node* findNext(Node* N);

   // findPrev()
   // Returns the in-order predecessor of node N (the previous node in sorted order).
   // If N is the leftmost node or is nullptr, returns nullptr.
   Node* findPrev(Node* N);

   // clone()
   // Recursively clones the subtree rooted at R, setting the parent pointer to 'parent'.
   // This static member function has access to the private Node type.
   static Node* clone(Node* R, Node* parent);

public:
   // Class Constructors & Destructors ----------------------------------------
   
   // Default constructor: Creates a new Dictionary in the empty state.
   Dictionary();

   // Copy constructor: Creates a deep copy of another Dictionary D.
   Dictionary(const Dictionary& D);

   // Destructor: Clears the Dictionary and frees allocated memory.
   ~Dictionary();

   // Access functions --------------------------------------------------------

   // size()
   // Returns the number of key-value pairs stored in the Dictionary.
   int size() const;

   // contains()
   // Returns true if a pair with key k exists in the Dictionary; false otherwise.
   bool contains(keyType k) const;

   // getValue()
   // Returns a reference to the value associated with key k.
   // Precondition: The key k exists in the Dictionary.
   valType& getValue(keyType k) const;

   // hasCurrent()
   // Returns true if the current iterator is defined; false otherwise.
   bool hasCurrent() const;

   // currentKey()
   // Returns the key at the current iterator position.
   // Precondition: The current iterator is defined.
   keyType currentKey() const;

   // currentVal()
   // Returns a reference to the value at the current iterator position.
   // Precondition: The current iterator is defined.
   valType& currentVal() const;

   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets the Dictionary to the empty state by deleting all key-value pairs.
   void clear();

   // setValue()
   // If a pair with key k exists, updates its value to v; otherwise, inserts the new pair (k, v).
   void setValue(keyType k, valType v);

   // remove()
   // Deletes the pair with key k from the Dictionary.
   // Precondition: The key k exists in the Dictionary.
   void remove(keyType k);

   // begin()
   // If the Dictionary is non-empty, sets the current iterator to the smallest key.
   void begin();

   // end()
   // If the Dictionary is non-empty, sets the current iterator to the largest key.
   void end();

   // next()
   // Advances the current iterator to the next key in sorted order.
   // Precondition: The current iterator is defined.
   void next();

   // prev()
   // Moves the current iterator to the previous key in sorted order.
   // Precondition: The current iterator is defined.
   void prev();

   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of the Dictionary. Each key-value pair is formatted as
   // "key : value" on a new line, with pairs in sorted order.
   std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in the Dictionary from a pre-order traversal.
   // Each key appears on a new line.
   std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value) pairs as Dictionary D.
   bool equals(const Dictionary& D) const;

   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts the string representation of Dictionary D into the output stream.
   friend std::ostream& operator<<(std::ostream& stream, Dictionary& D);

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B.
   friend bool operator==(const Dictionary& A, const Dictionary& B);

   // operator=()
   // Overwrites the state of this Dictionary with that of Dictionary D (deep copy)
   // and returns a reference to this Dictionary.
   Dictionary& operator=(const Dictionary& D);
};

#endif
