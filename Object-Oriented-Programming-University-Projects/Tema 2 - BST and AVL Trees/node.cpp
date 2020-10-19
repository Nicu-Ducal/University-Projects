#include <iostream>
#include "Node.h"

Node::Node(int value) : value(value), leftChild(nullptr), rightChild(nullptr) {
    std::cout << "Creating the node " << this->value << "\n";
}

Node::~Node(){
    std::cout << "Destroying the node " << value << "\n";
    if (leftChild != nullptr){
        delete leftChild;
        leftChild = nullptr;
    }
    if (rightChild != nullptr){
        delete rightChild;
        rightChild = nullptr;
    }
    value = 0;
}

int Node::getValue() const{
    return this->value;
}

void Node::setValue(int val){
    this->value = val;
}

void Node::setLeftChild(Node* left){
    leftChild = left;
}

Node* Node::getLeftChild() const{
    return this->leftChild;
}

void Node::setRightChild(Node* right){
    rightChild = right;
}

Node* Node::getRightChild() const{
    return this->rightChild;
}
