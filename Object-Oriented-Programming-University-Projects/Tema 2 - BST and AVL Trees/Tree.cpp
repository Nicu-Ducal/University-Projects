#include <iostream>
#include <queue>
#include "Tree.h"

template <typename T>
Tree<T>::Tree(bool add){
    if (add == 0) this->nodeNumber = 0;
    else this->nodeNumber = 1;
}

template <typename T>
Tree<T>::~Tree(){
    std::cout << "Destructor called for tree\n";
    nodeNumber = 0;
}

template <typename T>
int Tree<T>::getNodeNumber() const{
    return nodeNumber;
}


template <typename T>
void Tree<T>::inOrderTraversal(T *focusNode, std::ostream &out) const{
    if (focusNode != nullptr){
       inOrderTraversal(focusNode->getLeftChild(), out);
       out << focusNode->getValue() << " ";
       inOrderTraversal(focusNode->getRightChild(), out);
    }
}

template <typename T>
void Tree<T>::preOrderTraversal(T *focusNode, std::ostream &out) const{
    if (focusNode != nullptr){
       out << focusNode->getValue() << " ";
       preOrderTraversal(focusNode->getLeftChild(), out);
       preOrderTraversal(focusNode->getRightChild(), out);
    }
}

template <typename T>
void Tree<T>::postOrderTraversal(T *focusNode, std::ostream &out) const{
    if (focusNode != nullptr){
       postOrderTraversal(focusNode->getLeftChild(), out);
       postOrderTraversal(focusNode->getRightChild(), out);
       out << focusNode->getValue() << " ";
    }
}

template <typename T>
void Tree<T>::BFS(T *root, std::ostream &out) const{
    if (root == nullptr){
        out << "The tree is empty\n";
        return;
    }
    std::queue <T*> q;
    q.push(root);

    while(!q.empty()){
        T *now = q.front();
        out << now->getValue() << " ";
        q.pop();

        if (now->getLeftChild() != nullptr)
            q.push(now->getLeftChild());
        if(now->getRightChild() != nullptr)
            q.push(now->getRightChild());
    }
}

template<typename T>
void Tree<T>::printTree(T *focusNode, std::ostream &out, int space) const{

    if (focusNode == nullptr)
        return;

    space += 10;
    printTree(focusNode->getRightChild(), out, space);

    out << "\n";
    for (int i = 10; i < space; i++)
        out << " ";
    out << focusNode->getValue() << "\n";

    printTree(focusNode->getLeftChild(), out, space);
}

template <typename T>
int Tree<T>::leavesNumber(T *focusNode) const{
    if (focusNode == nullptr)
        return 0;
    else if (focusNode->getLeftChild() == nullptr && focusNode->getRightChild() == nullptr)
        return 1;
    else
        return leavesNumber(focusNode->getLeftChild()) + leavesNumber(focusNode->getRightChild());
}

template <typename T>
int Tree<T>::heigth(T *focusNode) const{
    if (focusNode == nullptr)
        return 0;
    return std::max(heigth(focusNode->getLeftChild()), heigth(focusNode->getRightChild())) + 1;
}

