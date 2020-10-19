#include <bits/stdc++.h>
using namespace std;
ifstream fin("abce.in");
ofstream fout("abce.out");

struct Node{
    int value;
    Node* leftChild;
    Node* rightChild;
    Node* parent;

    Node(int val) : value(val), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
};

class SplayTree{

        Node* root;

        void leftRotate(Node* target);
        void rightRotate(Node* target);
        void splay(Node* target);
        Node* findNode(int val);
        void replace(Node* a, Node* b);
        Node* treeMinimum(Node* target);

    public:
        SplayTree() : root(nullptr) {}
        void insert(int val);
        void remove(int val);
        bool find(int val);
        int lowerBound(int val);
        int upperBound(int val);
        void inOrderBound(int a, int b);
};

void SplayTree::leftRotate(Node* target){
    Node* change = target->rightChild;
    target->rightChild = change->leftChild;
    if (change->leftChild != nullptr)
        change->leftChild->parent = target;

    change->parent = target->parent;
        if (target->parent == nullptr)
            root = change;

    else if (target->parent->leftChild == target)
        target->parent->leftChild = change;

    else if (target->parent->rightChild == target)
        target->parent->rightChild = change;

    change->leftChild = target;
    target->parent = change;
}

void SplayTree::rightRotate(Node* target){
    Node* change = target->leftChild;
    target->leftChild = change->rightChild;
    if (change->rightChild != nullptr)
        change->rightChild->parent = target;

    change->parent = target->parent;
    if (target->parent == nullptr)
        root = change;

    else if (target->parent->leftChild == target)
        target->parent->leftChild = change;

    else if (target->parent->rightChild == target)
        target->parent->rightChild = change;

    change->rightChild = target;
    target->parent = change;
}

void SplayTree::splay(Node* target){
    while(target->parent != nullptr){
    // Daca nodul e copil al radacinii, avem cazul zig
    if(target->parent == root){
        if (target->parent->leftChild == target)
            rightRotate(target->parent);
        else
            leftRotate(target->parent);
        }

        else {  // Daca nu, verificam daca sunt cazurile zig-zig sau zig-zag
            Node* parent = target->parent;
            Node* grandparent = parent->parent;

            // 1. Cazurile zig-zig
            // a. Cand copilul si parintele sunt ambii copii stangi
            if (parent->leftChild == target and grandparent->leftChild == parent){
                rightRotate(grandparent);
                rightRotate(parent);
            }

            //b. Cand copilul si parintele sunt ambii copii drepti
            else if (parent->rightChild == target and grandparent->rightChild == parent){
                leftRotate(grandparent);
                leftRotate(parent);
            }

            // 2. Cazurile zig-zag
            // a. Cand nodul cautat este copil de dreapta, iar parintele e copil de stanga
            else if (parent->rightChild == target and grandparent->leftChild == parent){
                leftRotate(target->parent);
                rightRotate(target->parent);
            }

            // b. Cand nodul cautat este copil de stanga, iar parintele e copil de dreapta
            else if (parent->leftChild == target and grandparent->rightChild == parent){
                rightRotate(target->parent);
                leftRotate(target->parent);
            }
        }
    }
}

void SplayTree::replace(Node* a, Node* b){
    if(a->parent == nullptr)
        root = b;
    else if (a == a->parent->leftChild)
        a->parent->leftChild = b;
    else
        a->parent->rightChild = b;

    if (b != nullptr)
        b->parent = a->parent;
}

Node* SplayTree::treeMinimum(Node* target){
    while(target->leftChild != nullptr)
        target = target->leftChild;
    return target;
}

void SplayTree::insert(int val){
    Node* focusNode = root;
    Node* focusParent = nullptr;

    while (focusNode != nullptr){
        focusParent = focusNode;
        if (focusNode->value <= val)
            focusNode = focusNode->rightChild;
        else
            focusNode = focusNode->leftChild;
    }

    focusNode = new Node(val);
    focusNode->parent = focusParent;

    if (focusParent == nullptr)
        root = focusNode;
    else if (focusParent->value <= focusNode->value)
        focusParent->rightChild = focusNode;
    else
        focusParent->leftChild = focusNode;

    splay(focusNode);
}

Node* SplayTree::findNode(int val){
    Node* ans = root;
    Node* parent = nullptr;
    while (ans != nullptr){
        parent = ans;
        if (ans->value < val)
            ans = ans->rightChild;
        else if (ans->value > val)
            ans = ans->leftChild;
        else
            break;
    }

    if (ans != nullptr)
        splay(ans);
    else if (parent != nullptr)
        splay(parent);
    return ans;
}

bool SplayTree::find(int val){
    return (findNode(val) != nullptr);
}

void SplayTree::remove(int val){
    Node* toRemove = findNode(val);
    if (toRemove == nullptr)
        return;

    splay(toRemove);
    if (toRemove->leftChild == nullptr)
        replace(toRemove, toRemove->rightChild);
    else if (toRemove->rightChild == nullptr)
        replace(toRemove, toRemove->leftChild);
    else{
        Node* change = treeMinimum(toRemove->rightChild);
        if (change->parent != toRemove){
            replace(change, change->rightChild);
            change->rightChild = toRemove->rightChild;
            change->rightChild->parent = change;
        }
        replace(toRemove, change);
        change->leftChild = toRemove->leftChild;
        change->leftChild->parent = change;
    }

    delete toRemove;
}

int SplayTree::upperBound(int val){
    Node* target = root;
    Node* ans = nullptr;
    while (target != nullptr){
        if (target->value >= val){
            ans = target;
            target = target->leftChild;
        }
        else
            target = target->rightChild;
    }

    if (ans == nullptr)
        return -1;
    else
        return ans->value;
}

int SplayTree::lowerBound(int val){
    Node* target = root;
    Node* ans = nullptr;
    while (target != nullptr){
        if (target->value <= val){
            ans = target;
            target = target->rightChild;
        }
        else
            target = target->leftChild;
    }

    if (ans == nullptr)
        return -1;
    else
        return ans->value;
}

void SplayTree::inOrderBound(int a, int b){
    int ans = upperBound(a);
    while(ans <= b && ans != -1){
        fout << ans << " ";                 // schimb in fout
        ans = upperBound(ans + 1);
    }
}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(); cout.tie();

    int c, n, x, y;
    SplayTree tree;
    fin >> n;
    while(n--){
        fin >> c;
        if (c == 1){
            fin >> x;
            tree.insert(x);
        }
        else if (c == 2){
            fin >> x;
            tree.remove(x);
        }
        else if (c == 3){
            fin >> x;
            fout << tree.find(x) << "\n";
        }
        else if (c == 4){
            fin >> x;
            fout << tree.lowerBound(x) << "\n";
        }
        else if (c == 5){
            fin >> x;
            fout << tree.upperBound(x) << "\n";
        }
        else{
            fin >> x >> y;
            tree.inOrderBound(x, y);
            fout << "\n";
        }
    }

    return 0;
}
