#ifndef BST_H
#define BST_H

#include "Tree.h"
#include "Node.h"

class BST : public Tree<Node>
{
    private:
        Node *root;
        friend std::ostream &operator<< (std::ostream &out, const BST&tree);

    public:
        BST();
        BST(int value);
        virtual ~BST();

        virtual int getRoot() override;
        Node* getRootPtr() const;
        virtual void insert(int value) override;
        BST& operator+(int value);
        BST& operator>>(int value);
        virtual bool find(int value) override;
        virtual void remove(int value) override;

};

std::ostream &operator<< (std::ostream &out, const BST& tree);

#endif // BST_H
