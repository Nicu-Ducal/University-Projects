#ifndef NODEAVL_H
#define NODEAVL_H

#include "Node.h"

class NodeAVL : public Node
{
    private:
        int balanceFactor;
        friend class AVL;

    public:
        NodeAVL(int value = 0);
        virtual ~NodeAVL();

        void setLeftChild(NodeAVL* left);
        NodeAVL* getLeftChild() const;
        void setRightChild(NodeAVL* right);
        NodeAVL* getRightChild() const;
        void setBalance(int bal);
        int getBalance() const;
};

#endif // NODEAVL_H
