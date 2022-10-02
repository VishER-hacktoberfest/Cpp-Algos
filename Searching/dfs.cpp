#include<iostream>
#include<stack>
using namespace std;
#define NODE 6
typedef struct node{
   int val;
   int state; //status
}node;
int graph[NODE][NODE] = {
   {0, 1, 1, 1, 0, 0},
   {1, 0, 0, 1, 1, 0},
   {1, 0, 0, 1, 0, 1},
   {1, 1, 1, 0, 1, 1},
   {0, 1, 0, 1, 0, 1},
   {0, 0, 1, 1, 1, 0}
};
void dfs(node *vertex, node start){
   node u;
   stack<node> myStack;
   for(int i = 0; i<NODE; i++){
      vertex[i].state = 0;//not visited
      }
   myStack.push(start);
      while(!myStack.empty()){
         //pop and print node
         u = myStack.top();
         myStack.pop();
         cout << char(u.val+'A') << " ";
         if(u.state != 1){
            //update vertex status to visited
            u.state = 1;
            vertex[u.val].state = 1;
            for(int i = 0; i<NODE; i++){
            if(graph[i][u.val]){
               if(vertex[i].state == 0){
                  myStack.push(vertex[i]);
                  vertex[i].state = 1;
               }  
            }
         }
      }
   }
}
int main(){
   node vertices[NODE];
   node start;
   char s;
   for(int i = 0; i<NODE; i++){
      vertices[i].val = i;
   }
   s = 'C';//starting vertex C
   start.val = s-'A';
   cout << "DFS Traversal: ";
   dfs(vertices, start);
   cout << endl;
}