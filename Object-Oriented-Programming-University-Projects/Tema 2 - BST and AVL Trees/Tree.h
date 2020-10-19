#ifndef TREE_H
#define TREE_H

template <typename T>
class Tree
{
    protected:
        int nodeNumber;

    public:
        Tree(bool add = 0);
        virtual ~Tree();

        virtual int getRoot() = 0;
        virtual void insert(int value) = 0;
        virtual void remove(int value) = 0;
        virtual bool find(int value) = 0;

        void inOrderTraversal(T *focusNode, std::ostream &out) const;
        void preOrderTraversal(T *focusNode, std::ostream &out) const;
        void postOrderTraversal(T *focusNode, std::ostream &out) const;
        void printTree(T *focusNode, std::ostream &out, int space = 0) const;
        void BFS(T *root, std::ostream &out) const;
        int leavesNumber(T *focusNode) const;
        int heigth(T *focusNode) const;

        int getNodeNumber() const;
};

#endif // TREE_H
