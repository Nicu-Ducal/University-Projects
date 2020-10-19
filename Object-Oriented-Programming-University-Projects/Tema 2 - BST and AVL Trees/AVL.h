#ifndef AVL_H
#define AVL_H

#include "Tree.h"
#include "NodeAVL.h"

class AVL : public Tree<NodeAVL>
{
    private:
        NodeAVL *root;
        friend std::ostream &operator<< (std::ostream &out, const AVL& tree);

    public:
        AVL();
        AVL(int value);
        virtual ~AVL();

        virtual int getRoot() override;
        NodeAVL* getRootPtr() const;
        virtual void insert(int value) override;
        AVL& operator+(int value);
        AVL& operator>>(int value);
        virtual bool find(int value) override;
        virtual void remove(int value) override;

        NodeAVL* leftLeftRotate(NodeAVL* focusNode);
        NodeAVL* leftRightRotate(NodeAVL* focusNode);
        NodeAVL* rightRightRotate(NodeAVL* focusNode);
        NodeAVL* rightLeftRotate(NodeAVL* focusNode);
        NodeAVL* balance(NodeAVL* focusNode);
        NodeAVL* diveAndBalance(NodeAVL* focusNode, const NodeAVL* targetValue);

        void printBalances(NodeAVL *focusNode, std::ostream &out) const;

};

std::ostream &operator<< (std::ostream &out, const AVL& tree);

#endif // AVL_H

