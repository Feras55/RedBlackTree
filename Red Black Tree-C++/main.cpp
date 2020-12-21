#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class RedBlackTree{

private:
    struct node{
        int key;
        string data;
        bool black;
        node* left;
        node* right;
        node* parent;
    };
    node* root;

    void clear(node* t){
        if (t == NULL)
            return;
        clear(t->left);
        clear(t->right);
        delete t;
        t = NULL;
    }

    node* find(node* t, int k){
        if (t == NULL)
            return NULL;
        if (k == t->key)
            return t;

        if (k < t->key)
            return find(t->left, k);
        return find(t->right, k);
    }

    node* rotateRight(node* t){
        node* A = t->left;
        node* B = t;
        node* y = t->left->right;
        node* p = t->parent;
        B->left = y;
        if (y != NULL) y->parent = B;
        A->right = B;
        B->parent = A;

        A->parent = p;
        if (p != NULL && p->right == B) p->right = A;
        else if (p != NULL) p->left = A;

        return A;
    }

    node* rotateLeft(node* t){
        node* B = t->right;
        node* A = t;
        node* y = t->right->left;
        node* p = t->parent;
        B->left = A;
        A->parent = B;
        A->right = y;
        if (y != NULL) y->parent = A;

        B->parent = p;
        if (p != NULL && p->right == A) p->right = B;
        else if (p != NULL) p->left = B;

        return B;
    }

    int checkInvarient(node* t){
        if (t == NULL) return 0;

        int blackNodeLeft = checkInvarient(t->left), blackNodesRight = checkInvarient(t->right);

        if (blackNodeLeft != blackNodesRight) cout<<"Invariant broken!!!"<<endl;

        return (t->black ? 1 : 0) + blackNodeLeft;
    }

    void insertFix(node* t){
        if (t->parent == NULL){
            t->black = true;
            return;
        }
        if (t->parent->black){
            return;
        }

        node* parent = t->parent;
        node* grandParent = parent->parent;
        bool leftParent = (grandParent->left == parent);
        node* uncle = (leftParent ? grandParent->right : grandParent->left);

        if (uncle->black){
            if (leftParent){
                bool leftCase = (parent->left == t);
                if (!leftCase) parent = rotateLeft(parent);
                grandParent = rotateRight(grandParent);
                swap(grandParent->black, grandParent->right->black);
            }
            else{
                bool rightCase = (parent->right == t);
                if (!rightCase) parent = rotateRight(parent);
                grandParent = rotateLeft(grandParent);
                swap(grandParent->black, grandParent->left->black);
            }
        }
        else{
            parent->black = true;
            uncle->black = true;
            grandParent->black = false;
            insertFix(grandParent);
        }
    }

    node* insert(node* t, node* p, int k, string& s){
        if (t == NULL){
            t = new node;
            t->key = k, t->data = s;
            t->left = t->right = NULL;
            t->parent = p;
            if (t->parent == NULL)
                t->black = true;
            else if (t->parent->black)
                t->black = false;
            else {
                t->black = false;
                insertFix(t);
            }
        }
        else if (k < t->key)
            t->left = insert(t->left, t, k, s);
        else if (k > t->key)
            t->right = insert(t->right, t, k, s);

        return t;
    }

    void removeFix(node* p, node* s, bool leftChild){
        if (p == NULL){
            return;
        }
        if (leftChild){
            if ((s == NULL || s->black)){
                if ((s == NULL || s->left == NULL || s->left->black) && (s == NULL || s->right == NULL || s->right->black)){
                    if (s) s->black = false;
                    removeFix(p->parent, (p->parent ? (p == p->parent->left ? p->parent->right : p->parent->left) : NULL), (p->parent? p == p->parent->left : false));
                }
                else{
                    if (!s || !s->right || s->right->black) { s = rotateRight(s); s->black = true; s->right->black = false; }
                    p = rotateLeft(p);
                    p->right->black = true;
                }
            }
            else{
                p = rotateLeft(p);
                p->black = true;
                if (p->left->right) p->left->right->black = false;
            }
        }
        else{
            if ((s == NULL || s->black)){
                if ((s == NULL || s->left == NULL || s->left->black) && (s == NULL || s->right == NULL || s->right->black)){
                    if (s) s->black = false;
                    removeFix(p->parent, (p->parent ? (p == p->parent->left ? p->parent->right : p->parent->left) : NULL), (p->parent ? p == p->parent->left : false));
                }
                else{
                    if (!s || !s->left || s->left->black) s = rotateLeft(s);
                    p = rotateRight(p);
                    p->left->black = true;
                }
            }
            else{
                p = rotateRight(p);
                p->black = true;
                if (p->right->left) p->right->left->black = false;
            }
        }
    }

    node* remove(node* t, int k){
        if (t == NULL)
            return NULL;
        if (k == t->key){
            if (t->left != NULL && t->right != NULL){
                node* s = successor(t);
                t->key = s->key, t->data = s->data;
                t->right = remove(t->right, s->key);
            }
            else {
                bool isblack = t->black;
                node* p = t->parent;

                node* s = NULL; bool leftChild = false;
                if (p && t == p->left) leftChild = true, s = p->right;
                else if (p) s = p->left;

                if (t->left == NULL && t->right == NULL){
                    if (leftChild && t->parent) t->parent->left = NULL;
                    else if (t->parent) t->parent->right = NULL;
                    node* tmp = t;
                    t = NULL;
                    delete tmp;
                }
                else if (t->left == NULL){
                    t->right->parent = t->parent;
                    if (leftChild) t->parent->left = t->right;
                    else t->parent->right = t->right;
                    node* tmp = t;
                    t = t->right;
                    delete tmp;
                }
                else if (t->right == NULL){
                    t->left->parent = t->parent;
                    if (leftChild) t->parent->left = t->left;
                    else t->parent->right = t->left;
                    node* tmp = t;
                    t = t->left;
                    delete tmp;
                }
                if (isblack && (t == NULL || t->black)) removeFix(p, s, leftChild);
                else if (isblack) t->black = true;
            }
        }

        else if (k < t->key)
            t->left = remove(t->left, k);
        else if (k > t->key)
            t->right = remove(t->right, k);
        return t;
    }

    node* findMin(node* t){
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    }

    node* findMax(node* t){
        if (t == NULL)
            return NULL;
        if (t->right == NULL)
            return t;
        return findMax(t->right);
    }

    node* successor(node* t){
        if (t == NULL || t->right == NULL)
            return NULL;
        return findMin(t->right);
    }

    node* predecessor(node* t){
        if (t == NULL || t->left == NULL)
            return NULL;
        return findMax(t->left);
    }

    void inorder(node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->key << ":" << t->data << " - ";
        inorder(t->right);
    }

public:
    RedBlackTree(){
        root = NULL;
    }
    void clear(){
        clear(root);
    }
    node* find(int k){
        return find(root, k);
    }
    void insert(int k, string s){
        root = insert(root, NULL, k, s);
    }
    node* findMin(){
        return findMin(root);
    }
    node* findMax(){
        return findMax(root);
    }
    void remove(int k){
        root = remove(root, k);
        while (root && root->parent) root = root->parent;
    }
    void display() {
        inorder(root);
        cout << endl;
    }
    void checkInvarient(){
        checkInvarient(root);
    }
    ~RedBlackTree(){
        clear(root);
    }
};

int main(){
    RedBlackTree t;
    t.insert(20, "hello");
    t.checkInvarient();
    t.display();
    t.insert(25, "friends");
    t.checkInvarient();
    t.display();
    t.insert(15, "how");
    t.checkInvarient();
    t.display();
    t.insert(10, "are");
    t.checkInvarient();
    t.display();
    t.insert(30, "you");
    t.checkInvarient();
    t.display();
    t.remove(20);
    t.checkInvarient();
    t.display();
    t.remove(25);
    t.checkInvarient();
    t.display();
    t.remove(30);
    t.checkInvarient();
    t.display();
    t.remove(10);
    t.remove(15);
    t.checkInvarient();
    t.display();
    return 0;
}
