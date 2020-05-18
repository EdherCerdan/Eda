#include <iostream> 
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <math.h>
#include <string>
using namespace std; 

class Node{
public:
    int data;
    Node *left, *right;
    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST 
{ 
    public: 
    Node *root;
    BST(int val){
        root = new Node(val);
    }
    vector<int> search_path(int val){
        vector<int> path;
        Node *temp = root;
        while(temp != nullptr and temp->data!=val){
            path.push_back(temp->data);
            if (val < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp != nullptr)
            path.push_back(temp->data);
        else
            path.clear();
        return path;
    }

    void insert(int key) 
    { 
        Node* newnode = new Node(key); 
        Node* x = root; 
        Node* y = NULL;   
        while (x != NULL) { 
            y = x; 
            if (key < x->data) 
                x = x->left; 
            else
                x = x->right; 
        } 
        if (y == NULL) 
            y = newnode; 
        else if (key < y->data) 
            y->left = newnode; 
        else
            y->right = newnode; 
    } 
    void inorder(Node *n, vector<int> &vec){
        if(n != 0){
            inorder(n->left, vec); 
            vec.push_back(n->data);
            inorder(n->right, vec);
        }
    }
    void BFS(vector<int> &vec){  
        queue<Node *> q; 
        q.push(root);   
        while (q.empty() == false){ 
            Node *node = q.front();
            vec.push_back(node->data);
            q.pop(); 
            if (node->left != 0){
                q.push(node->left);
                
            }
            if (node->right != 0){
                q.push(node->right);
            }
        }
        cout<<endl;
    }
    void DFS(vector<int> &vec){
        vector<Node*> visited;
        stack<Node*> to_visit;
        to_visit.push(root);
        while(!to_visit.empty()){
            Node *curr_node = to_visit.top();
            to_visit.pop();
            if (find(visited.begin(), visited.end(), curr_node ) == visited.end()){
                vec.push_back(curr_node->data);
                visited.push_back(curr_node);
                
            }
            
            if (find(visited.begin(), visited.end(), curr_node->right ) == visited.end()){
                if (curr_node->right){
                    to_visit.push(curr_node->right);
                }
            }

            if (find(visited.begin(), visited.end(), curr_node->left ) == visited.end()){
                if (curr_node->left){
                    to_visit.push(curr_node->left);
                }
            }
    
        }
    }
    void veb(Node *t, vector<int> &vec){
        // veb from top tree
        if(t and t->left and t->right){
            vec.push_back(t->data);
            vec.push_back(t->left->data);
            vec.push_back(t->right->data);
            veb(t->left, vec);
            veb(t->right, vec);
        }

    }
    int search_blocks(vector<int> layout, int blocks, int val){
        int total_blocks = layout.size()/blocks;
        vector<int> path = search_path(val);
        if (path.size() == 0){
            cout<<"elemento no encontrado en arbol"<<endl;
            return -1;
        }

        cout<<"camino: "<<endl;
        for(int i = 0; i < path.size(); i++){
            cout<<path[i]<<" ";
        }
        cout<<endl;

        cout<<"recorrido: "<<endl;
        for(int i = 0; i < layout.size(); i++){
            if(i%blocks == 0 and i!=0)
                cout<<"- ";
            cout<<layout[i]<<" ";
        }
        cout<<endl;
        
        int n_blocks=0;
        int i = 0; // pos recorrido
        int j = 0; // post busqueda
        bool block_has_element = false;
        bool new_block = false;
        while(i < layout.size() and j < path.size()){
            if (i%blocks == 0){
                new_block = true;
                block_has_element = false;
            }
            if (layout[i] == path[j]){
                j += 1;
                block_has_element = true;
            }
            if (block_has_element and new_block){
                n_blocks += 1;
                new_block = false;
            }
            i+=1;

        }
        cout<<"numero bloques a recorrer: "<<n_blocks<<endl;
        return n_blocks;
    }
};
  
// Driver code 
int main() 
{ 
    BST tree(8);
    tree.insert(4);
    tree.insert(12);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(10);
    tree.insert(14);
    tree.insert(9);
    tree.insert(11);
    tree.insert(13);
    tree.insert(15);
    
    vector<int> vec_inorder;
    vector<int> vec_BFS;
    vector<int> vec_DFS;
    vector<int> vec_veb;

    tree.inorder(tree.root, vec_inorder);
    tree.BFS(vec_BFS);
    tree.DFS(vec_DFS);

    cout<<"inorder: "<<endl;
    for(int i = 0; i < vec_inorder.size(); i++){
        cout<<vec_inorder[i]<<" ";
    }
    cout<<endl;

    cout<<"BFS: "<<endl;
    for(int i = 0; i < vec_BFS.size(); i++){
        cout<<vec_BFS[i]<<" ";
    }
    cout<<endl;

    cout<<"DFS: "<<endl;
    for(int i = 0; i < vec_DFS.size(); i++){
        cout<<vec_DFS[i]<<" ";
    }
    cout<<endl;

    vec_veb.push_back(8);
    vec_veb.push_back(4);
    vec_veb.push_back(12);
    vec_veb.push_back(2);
    vec_veb.push_back(1);
    vec_veb.push_back(3);
    vec_veb.push_back(6);
    vec_veb.push_back(5);
    vec_veb.push_back(7);
    vec_veb.push_back(10);
    vec_veb.push_back(9);
    vec_veb.push_back(11);
    vec_veb.push_back(14);
    vec_veb.push_back(13);
    vec_veb.push_back(15);
    cout<<"vam Ende Boas: "<<endl;
    for(int i = 0; i < vec_veb.size(); i++){
        cout<<vec_veb[i]<<" ";
    }
    cout<<endl;

    while(true){
        int option;

        cout<<"ingresa recorrido a usar (inorder: 1, dfs:2 , bfs:3, van emde boas:4)"<<endl;
        cin>>option;

        int b, e;
        cout<<"ingresa tam bloque: ";cin>>b;
        // cout<<endl;
        cout<<"ingresa elemento a buscar: ";cin>>e;
        // cout<<endl;
        if(option == 1){
            tree.search_blocks(vec_inorder, b, e);
        }
        if(option == 2){
            tree.search_blocks(vec_DFS, b, e);
        }
        if(option == 3){
            tree.search_blocks(vec_BFS, b, e);
        }
        if(option == 4){
            tree.search_blocks(vec_veb, b, e);
        }
    }
    return 0; 
} 
