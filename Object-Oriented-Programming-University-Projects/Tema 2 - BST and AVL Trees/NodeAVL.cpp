#include <iostream>
#include "NodeAVL.h"


NodeAVL::NodeAVL(int value) : Node(value) {
    this->balanceFactor = 0;
    std::cout << "Creating the AVL node " << this->value << " with balance factor " << this->balanceFactor << "\n";
}

NodeAVL::~NodeAVL(){
    std::cout << "Destroying the AVL node " << value << ", ";
    balanceFactor = 0;
}

void NodeAVL::setLeftChild(NodeAVL* left){
    leftChild = left;
}

NodeAVL* NodeAVL::getLeftChild() const{
    return static_cast<NodeAVL*>(this->leftChild);
}

void NodeAVL::setRightChild(NodeAVL* right){
    rightChild = right;
}

NodeAVL* NodeAVL::getRightChild() const{
    return static_cast<NodeAVL*>(this->rightChild);
}

int NodeAVL::getBalance() const{
    return this->balanceFactor;
}

void NodeAVL::setBalance(int val){
    this->balanceFactor = val;
}
