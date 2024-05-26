//
//  SplayTree.h
//  SplayTree
//
//  Created by Polya Melnik on 26.05.2024.
//

#ifndef SplayTree_h
#define SplayTree_h

#include <string>

class SplayTree {
public:
    struct Node {
        std::string name;
        int id;
        Node* left;
        Node* right;

        Node(const std::string& n, int i) : name(n), id(i), left(nullptr), right(nullptr) {}
    };

    SplayTree();
    void insert(const std::string& name, int id);
    void remove(const std::string& name);
    int search(const std::string& name);
    std::string printInOrder();
    std::string searchByIdentifier(int id);
    
private:
    Node* root;
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);
    Node* splay(Node* root, const std::string& name);
    Node* join(Node* leftTree, Node* rightTree);
    void inorder(Node* root);
};

#endif /* SplayTree_h */
