#include <iostream>
using namespace std;

// Prortotypes
struct treeNode;

// Queue required for Tree
struct node
{
    treeNode *address;
    node *next;
};

class queue
{
    node *front, *rear;

public:
    queue()
    {
        front = NULL;
        rear = NULL;
    }
    void enQueue(treeNode *);
    treeNode *deQueue();
} Q;
void queue::enQueue(treeNode *item)
{
    node *temp = new node;
    temp->address = item;
    temp->next = NULL;
    if (front == NULL)
    {
        front = temp;
        rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }
}
treeNode *queue::deQueue()
{
    treeNode *temp = front->address;
    front = front->next;
    return (temp);
}

// Node of Tree
struct treeNode
{
    int data;
    treeNode *left;
    treeNode *right;
};

// Implementating TREE Data Structure
class tree
{
    treeNode *root;

public:
    tree()
    {
        root = NULL;
    }
    void insertTree(int);
    treeNode *rtnRoot();
};

// Insert function
// (To insert new nodes in Tree)
void tree::insertTree(int item)
{
    treeNode *temp = new treeNode;
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    if (root == NULL)
    {
        root = temp;
        Q.enQueue(root);
        Q.enQueue(root);
    }
    else
    {
        treeNode *TEMP = Q.deQueue();
        if (TEMP->left == NULL)
        {
            TEMP->left = temp;
            Q.enQueue(TEMP->left);
            Q.enQueue(TEMP->left);
        }
        else
        {
            TEMP->right = temp;
            Q.enQueue(TEMP->right);
            Q.enQueue(TEMP->right);
        }
    }
}
// root return function
treeNode *tree::rtnRoot()
{
    return (root);
}

// preOrder Traversal
void preOrder(treeNode *root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Main function
int main()
{
    tree T;
    for (int i = 1; i <= 10; i++)
    {
        T.insertTree(i);
    }

    preOrder(T.rtnRoot());
    return 0;
}

