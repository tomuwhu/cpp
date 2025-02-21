// C++ Program to Implement Red Black Tree
// https://www.geeksforgeeks.org/red-black-tree-in-cpp/
#include <iostream>
#include <fstream>
using namespace std;

// Enumeration for colors of nodes in Red-Black Tree
enum Color { RED, BLACK };

// Class template for Red-Black Tree
template <typename T> class RedBlackTree {
private:
    // Structure for a node in Red-Black Tree
    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        // Constructor to initialize node with data and
        // color
        Node(T value)
            : data(value)
            , color(RED)
            , parent(nullptr)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    Node* root; // Root of the Red-Black Tree

    // Utility function: Left Rotation
    void rotateLeft(Node*& node)
    {
        Node* child = node->right;
        node->right = child->left;
        if (node->right != nullptr)
            node->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    // Utility function: Right Rotation
    void rotateRight(Node*& node)
    {
        Node* child = node->left;
        node->left = child->right;
        if (node->left != nullptr)
            node->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->right = node;
        node->parent = child;
    }

    // Utility function: Fixing Insertion Violation
    void fixInsert(Node*& node)
    {
        Node* parent = nullptr;
        Node* grandparent = nullptr;
        while (node != root && node->color == RED
               && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr
                    && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr
                    && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
    }

    // Utility function: Find Node with Minimum Value
    Node* minValueNode(Node*& node)
    {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Utility function: Transplant nodes in Red-Black Tree
    void transplant(Node*& root, Node*& u, Node*& v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    // Utility function: Helper to print Red-Black Tree

    void exportDOTHelper(Node* node, ofstream &file) {
        if (!node) return;
        file << node->data << " [label=\"" << node->data << "\", color=" << (node->color == RED ? "red" : "black") << "]\n";
        if (node->left) {
            file << node->data << " -> " << node->left->data << " [color=\"blue\"]\n";
            exportDOTHelper(node->left, file);
        }
        if (node->right) {
            file << node->data << " -> " << node->right->data << " [color=\"purple\"]\n";
            exportDOTHelper(node->right, file);
        }
    }

    // Utility function: Delete all nodes in the Red-Black
    // Tree
    void deleteTree(Node* node)
    {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    // Constructor: Initialize Red-Black Tree
    RedBlackTree()
        : root(nullptr)
    {
    }

    // Destructor: Delete Red-Black Tree
    ~RedBlackTree() { deleteTree(root); }

    // Public function: Insert a value into Red-Black Tree
    void insert(T key)
    { 
        if (root != nullptr) {
            Node* node = root;
            Node* z = nullptr;
            while (node != nullptr) {
                if (node->data == key) {
                    z = node;
                }
                if (node->data <= key) {
                    node = node->right;
                }
                else {
                    node = node->left;
                }
            }
            if (z != nullptr) {
                return;
            }
        }
        Node* node = new Node(key);
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr) {
            parent = current;
            if (node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        node->parent = parent;
        if (parent == nullptr)
            root = node;
        else if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;
        fixInsert(node);
    }  

    void exportToDOT(const string& filename) {
        ofstream file(filename);
        file << "digraph RedBlackTree {\n";
        exportDOTHelper(root, file);
        file << "}";
        file.close();
    }

};

// Driver program to test Red-Black Tree
int main()
{
    RedBlackTree<int> rbtree;

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open input file!" << endl;
        return 1;
    }
    
    int num;
    while (file >> num) {
        rbtree.insert(num);
    }
    
    file.close();

    rbtree.exportToDOT("rbt.dot");


    return 0;
}

