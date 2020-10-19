#include <iostream>
#include "AVL.h"
#include "Tree.h"
#include "Tree.cpp"

AVL::AVL() : Tree(), root(nullptr) {}

AVL::AVL(int value) : Tree(1) {
    this->root = new NodeAVL(value);
}

AVL::~AVL(){
    delete root;
    root = nullptr;
}

NodeAVL* AVL::leftLeftRotate(NodeAVL* focusNode){
    NodeAVL* newFocus = focusNode->getLeftChild();
    focusNode->leftChild = newFocus->getRightChild();
    newFocus->rightChild = focusNode;
    newFocus->balanceFactor = heigth(newFocus->getLeftChild()) - heigth(newFocus->getRightChild());
    focusNode->balanceFactor = heigth(focusNode->getLeftChild()) - heigth(focusNode->getRightChild());
    return newFocus;
}

NodeAVL* AVL::rightRightRotate(NodeAVL* focusNode){
    NodeAVL* newFocus = focusNode->getRightChild();
    focusNode->rightChild = newFocus->getLeftChild();
    newFocus->leftChild = focusNode;
    newFocus->balanceFactor = heigth(newFocus->getLeftChild()) - heigth(newFocus->getRightChild());
    focusNode->balanceFactor = heigth(focusNode->getLeftChild()) - heigth(focusNode->getRightChild());
    return newFocus;
}

NodeAVL* AVL::leftRightRotate(NodeAVL* focusNode){
    focusNode->leftChild = rightRightRotate(focusNode->getLeftChild());
    return leftLeftRotate(focusNode);
}

NodeAVL* AVL::rightLeftRotate(NodeAVL* focusNode){
    focusNode->rightChild = leftLeftRotate(focusNode->getRightChild());
    return rightRightRotate(focusNode);
}

NodeAVL* AVL::balance(NodeAVL* focusNode){
    if (focusNode->balanceFactor > 1){
        if (focusNode->getLeftChild()->balanceFactor > 0)
            focusNode = leftLeftRotate(focusNode);
        else
            focusNode = leftRightRotate(focusNode);
        }
    else if (focusNode->balanceFactor < -1){
        if (focusNode->getRightChild()->balanceFactor > 0)
            focusNode = rightLeftRotate(focusNode);
        else
            focusNode = rightRightRotate(focusNode);
    }
    return focusNode;
}

NodeAVL* AVL::diveAndBalance(NodeAVL* focusNode, const NodeAVL* targetNode){
    if (targetNode == nullptr){
        return nullptr;
    }
    if(focusNode->value != targetNode->value){
        if(focusNode->value > targetNode->value)
            focusNode->leftChild = diveAndBalance(focusNode->getLeftChild(), targetNode);
        else
            focusNode->rightChild = diveAndBalance(focusNode->getRightChild(), targetNode);
        }
    focusNode->balanceFactor = heigth(focusNode->getLeftChild()) - heigth(focusNode->getRightChild());
    focusNode = balance(focusNode);
    return focusNode;
}

void AVL::insert(int value){
    this->nodeNumber += 1;
    if (root == nullptr){
        root = new NodeAVL(value);
        return;
    }
    else {
        NodeAVL *newNode = new NodeAVL(value);
        NodeAVL *focusNode = root;
        NodeAVL *parent = focusNode;

        while(true){
            parent = focusNode;

            if (value < focusNode->value){
                focusNode = focusNode->getLeftChild();
                if (focusNode == nullptr){
                    parent->leftChild = newNode;
                    break;
                }
            }
            else {
                focusNode = focusNode->getRightChild();
                if (focusNode == nullptr){
                    parent->rightChild = newNode;
                    break;
                }
            }
        }
        root = diveAndBalance(root, newNode);
    }
}


AVL& AVL::operator+(int value){
    AVL::insert(value);
    return *this;
}

AVL& AVL::operator>>(int value){
    this->AVL::insert(value);
    return *this;
}

int AVL::getRoot(){
    return this->root->value;
}

NodeAVL* AVL::getRootPtr() const{
    return root;
}

void AVL::printBalances(NodeAVL *focusNode, std::ostream& out) const{
    if (focusNode != nullptr){
       printBalances(focusNode->getLeftChild(), out);
       out << "Value: " << focusNode->value << ", Balance Factor: " << focusNode->balanceFactor << "\n";
       printBalances(focusNode->getRightChild(), out);
    }
}

bool AVL::find(int value){
    NodeAVL *focusNode = root;

    while(focusNode->value != value){
        if (focusNode->value > value)
            focusNode = focusNode->getLeftChild();
        else
            focusNode = focusNode->getRightChild();

        if (focusNode == nullptr)
            return 0;
    }
    return 1;
}


void AVL::remove(int value){
    if (!(this->find(value))){
        std::cout << "The is no node with value " << value << " in the tree\n";
        return;
    }

    this->nodeNumber -= 1;
    NodeAVL *focusNode = root;
    NodeAVL *parent = root;
    NodeAVL* targetNode = nullptr;
    bool isLeft = 1;

    while (focusNode->value != value){
        parent = focusNode;

        if (focusNode->value > value){
            isLeft = 1;
            focusNode = focusNode->getLeftChild();
        }
        else {
            isLeft = 0;
            focusNode = focusNode->getRightChild();
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
        targetNode = parent;
    }
    else if (focusNode->rightChild == nullptr){
        if (focusNode == root)
            root = focusNode->getLeftChild();
        else if (isLeft == 1)
            parent->leftChild = focusNode->leftChild;
        else
            parent->rightChild = focusNode->leftChild;

        focusNode->leftChild = nullptr;
        delete focusNode;
        targetNode = parent;
    }
    else if (focusNode->leftChild == nullptr){
        if (focusNode == root)
            root = focusNode->getRightChild();
        else if (isLeft == 1)
            parent->leftChild = focusNode->rightChild;
        else
            parent->rightChild = focusNode->rightChild;

        focusNode->rightChild = nullptr;
        delete focusNode;
        targetNode = parent;
    }
    else{
        NodeAVL *newNode = focusNode;
        NodeAVL *newNodeParent = focusNode;
        NodeAVL *focusReplace = newNode->getRightChild();

        while (focusReplace != nullptr){
            newNodeParent = newNode;
            newNode = focusReplace;
            focusReplace = focusReplace->getLeftChild();
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
        targetNode = newNodeParent;
    }
    root = diveAndBalance(root, targetNode);
}

// Functions for AVL
std::ostream &operator<< (std::ostream &out, const AVL& tree){
    out << "Printing the AVL components:\nIn Order Traversal: ";
    tree.inOrderTraversal(tree.getRootPtr(), out);
    out << "\nPre Order Traversal: ";
    tree.preOrderTraversal(tree.getRootPtr(), out);
    out << "\nPost Order Traversal: ";
    tree.postOrderTraversal(tree.getRootPtr(), out);
    out << "\nBreadth-First Search: ";
    tree.BFS(tree.getRootPtr(), out);
    out << "\nPrinting nodes' value and balance factor:\n";
    tree.printBalances(tree.getRootPtr(), out);
    out << "\nPrinting the 2D model of the tree: ";
    tree.printTree(tree.getRootPtr(), out);
    out << "\n";
    return out;
}
