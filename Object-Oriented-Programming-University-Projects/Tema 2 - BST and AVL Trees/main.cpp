#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "NodeAVL.h"
#include "Tree.h"
#include "Tree.cpp"
#include "BST.h"
#include "AVL.h"

void testerBST(std::string s){

    std::ifstream in(s);
    //std::ofstream out("tester.out");

    int n, x;
    BST *tree = new BST();

    in >> n;
    for (int i = 0; i < n; i++){
        in >> x;
        if (i < n / 3)
            tree->insert(x);
        else if (i >= n / 3 && i < 2 * n / 3)
            *tree + x;
        else
            *tree >> x;
    }

    std::cout << *tree;
    std::cout << "\nRoot: " << tree->getRoot() << "\n";
    std::cout << "Number of nodes: " << tree->getNodeNumber() << "\n";
    std::cout << "Leaves number: " << tree->leavesNumber(tree->getRootPtr()) << "\n";
    std::cout << "Height of the tree: " << tree->heigth(tree->getRootPtr()) << "\n";

    in >> n >> x;
    std::cout << "Find " << n << ": " << tree->find(n) << "\n";
    std::cout << "Find " << x << ": " << tree->find(x) << "\n";

    tree->remove(tree->getRoot());
    std::cout << *tree << "\n";
    std::cout << "\nRoot: " << tree->getRoot() << "\n";
    std::cout << "Number of nodes: " << tree->getNodeNumber() << "\n";
    std::cout << "Leaves number: " << tree->leavesNumber(tree->getRootPtr()) << "\n";
    std::cout << "Height of the tree: " << tree->heigth(tree->getRootPtr()) << "\n";

    delete tree;
    in.close();
}

void testerAVL(std::string s){

    std::ifstream in(s);
    //std::ofstream out("tester.out");

    int n, x;

    AVL *tree = new AVL();
    in >> n;
    for (int i = 0; i < n; i++){
        in >> x;
        if (i < n / 3)
            tree->insert(x);
        else if (i >= n / 3 && i < 2 * n / 3)
            *tree + x;
        else
            *tree >> x;
    }

    std::cout << *tree;
    std::cout << "\nRoot: " << tree->getRoot() << "\n";
    std::cout << "Number of nodes: " << tree->getNodeNumber() << "\n";
    std::cout << "Leaves number: " << tree->leavesNumber(tree->getRootPtr()) << "\n";
    std::cout << "Height of the tree: " << tree->heigth(tree->getRootPtr()) << "\n";

    in >> n >> x;
    std::cout << "Find " << n << ": " << tree->find(n) << "\n";
    std::cout << "Find " << x << ": " << tree->find(x) << "\n";

    tree->remove(tree->getRoot());
    std::cout << *tree << "\n";
    std::cout << "\nRoot: " << tree->getRoot() << "\n";
    std::cout << "Number of nodes: " << tree->getNodeNumber() << "\n";
    std::cout << "Leaves number: " << tree->leavesNumber(tree->getRootPtr()) << "\n";
    std::cout << "Height of the tree: " << tree->heigth(tree->getRootPtr()) << "\n";

    delete tree;
    in.close();
}

int main(){

    std::cout << "\t\t===========Binary Search Tree class test===========\n";
    testerBST("tester.in");
    testerBST("tester1.in");

    std::cout << "\t\t===========AVL Tree class test===========\n";
    testerAVL("tester.in");
    testerAVL("tester1.in");

    return 0;
}
