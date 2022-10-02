#include <iostream>
#include <vector>

struct Node{
    int value;
    Node *left, *right;
    Node *parent;

    Node(){
        value = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

class CartesianTree{
private:
    // last pointer to keep track of last node added
    Node *root, *last;

    Node * findLowestNode(Node *node, int x){
        // if(node == NULL)    // i.e. first insertion
        //     return NULL;
        
        if(node->value < x)
            return node;
        else if(node->parent != NULL)
            return findLowestNode(node->parent, x);
        else
            return NULL;
    }

public:
    Node * getRoot(){
        return root;
    }

    void addNode(int x){
        Node *new_node = new Node;
        new_node->value = x;
        if(root == NULL){
            last = new_node;
            root = new_node;
            return;
        }
        Node *z = findLowestNode(last, x);
        if(z == NULL){
            new_node->left = root;
            root->parent = new_node;
            root = new_node;
        }
        else{
            new_node->left = z->right;
            z->right = new_node;
            new_node->parent = z;
        }

        last = new_node;
    }

    CartesianTree(std::vector<int> ar){
        root = NULL;
        last = NULL;
        // Call addNode function for each element of the array
        for(auto x : ar){
            addNode(x);
        }
    }

    void InorderTraversal(Node *node){
        // To print inorder traversal of the tree
        if(node == NULL)
            return;
        InorderTraversal(node->left);
        std::cout << node->value << ' ';
        InorderTraversal(node->right);
    }
};

int main(){
    std::vector<int> ar = {1, 14, 5, 0, 8};
    
    CartesianTree tree(ar);
    tree.InorderTraversal(tree.getRoot());
    std::cout << '\n';
}