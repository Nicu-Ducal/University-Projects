#include <iostream>
#include "BST.h"
#include "Tree.h"
#include "Tree.cpp"

BST::BST() : Tree(), root(nullptr) {}

BST::BST(int value) : Tree(1) {
    this->root = new Node(value);
}

BST::~BST(){
    delete root;
    root = nullptr;
}


void BST::insert(int value){
    if (root == nullptr){
        root = new Node(value);
         this->nodeNumber += 1;
        return;
    }
    else {
        Node *newNode = new Node(value);
        Node *focusNode = root;
        Node *parent = focusNode;

        while(true){
            parent = focusNode;

            if (value < focusNode->getValue()){
                focusNode = focusNode->getLeftChild();

                if (focusNode == nullptr){
                    parent->leftChild = newNode;
                    this->nodeNumber += 1;
                    return;
                }
            }
            else {
                focusNode = focusNode->getRightChild();

                if (focusNode == nullptr){
                    parent->rightChild = newNode;
                    this->nodeNumber += 1;
                    return;
                }
            }
        }
    }
}

BST& BST::operator+(int value){
    this->BST::insert(value);
    return *this;
}

BST& BST::operator>>(int value){
    this->BST::insert(value);
    return *this;
}

int BST::getRoot(){
    return this->root->value;
}

Node* BST::getRootPtr() const{
    return root;
}

bool BST::find(int value){
    Node *focusNode = root;

    while(focusNode->value != value){
        if (focusNode->value > value)
            focusNode = focusNode->leftChild;
        else
            focusNode = focusNode->rightChild;

        if (focusNode == nullptr)
            return 0;
    }
    return 1;
}

void BST::remove(int value){
    if (!(this->find(value))){
        std::cout << "The is no node with value " << value << " in the tree\n";
        return;
    }

    this->nodeNumber -= 1;
    Node *focusNode = root;
    Node *parent = root;
    bool isLeft = 1;

    while (focusNode->value != value){
        parent = focusNode;

        if (focusNode->value > value){
            isLeft = 1;
            focusNode = focusNode->leftChild;
        }
        else {
            isLeft = 0;
            focusNode = focusNode->rightChild;
        }
    }

    if (focusNode->leftChild == nullptr && focusNode->rightChild == nullptr){
        if (focusNode == root){
            delete root;
            root = nullptr;
        }
        else if (isLeft == 1){
            delete parent->leftChild;
            parent->leftChild = nullptr;
        }
        else{
            delete parent->rightChild;
            parent->rightChild = nullptr;
        }
    }
    else if (focusNode->rightChild == nullptr){
        if (focusNode == root)
            root = focusNode->leftChild;
        else if (isLeft == 1)
            parent->leftChild = focusNode->leftChild;
        else
            parent->rightChild = focusNode->leftChild;

        focusNode->leftChild = nullptr;
        delete focusNode;
    }
    else if (focusNode->leftChild == nullptr){
        if (focusNode == root)
            root = focusNode->rightChild;
        else if (isLeft == 1)
            parent->leftChild = focusNode->rightChild;
        else
            parent->rightChild = focusNode->rightChild;

        focusNode->rightChild = nullptr;
        delete focusNode;
    }
    else{
        Node *newNode = focusNode;
        Node *newNodeParent = focusNode;
        Node *focusReplace = newNode->rightChild;

        while (focusReplace != nullptr){
            newNodeParent = newNode;
            newNode = focusReplace;
            focusReplace = focusReplace->leftChild;
        }

        if(newNode != focusNode->rightChild){
            newNodeParent->leftChild = newNode->rightChild;
            newNode->rightChild = focusNode->rightChild;
        }

        if (focusNode == root){
            root = newNode;
        }
        else if (isLeft == 1){
            parent->leftChild = newNode;
        }
        else{
            parent->rightChild = newNode;
        }
        newNode->leftChild = focusNode->leftChild;

        focusNode->leftChild = focusNode->rightChild = nullptr;
        delete focusNode;
    }
}

//Functions for BST
std::ostream &operator<< (std::ostream &out, const BST& tree){
    out << "Printing the BST components:\nIn Order Traversal: ";
    tree.inOrderTraversal(tree.getRootPtr(), out);
    out << "\nPre Order Traversal: ";
    tree.preOrderTraversal(tree.getRootPtr(), out);
    out << "\nPost Order Traversal: ";
    tree.postOrderTraversal(tree.getRootPtr(), out);
    out << "\nBreadth-First Search: ";
    tree.BFS(tree.getRootPtr(), out);
    out << "\nPrinting the 2D model of the tree: ";
    tree.printTree(tree.getRootPtr(), out);
    out << "\n";
    return out;
}
