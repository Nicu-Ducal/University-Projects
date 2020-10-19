#ifndef NODE_H
#define NODE_H


class Node
{
    protected:
        int value;
        Node *leftChild;
        Node *rightChild;
        friend class BST;

    public:
        Node(int value = 0);
        virtual ~Node();

        int getValue() const;
        void setValue(int val);
        void setLeftChild(Node* left);
        Node* getLeftChild() const;
        void setRightChild(Node* right);
        Node* getRightChild() const;
};

#endif // NODE_H
