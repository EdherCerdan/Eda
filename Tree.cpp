#include<iostream>
#include<queue>
#include<stack>
#include <algorithm>
using namespace std;
 

class BTreeNode
{
    int *keys;  
    int t;      
    BTreeNode **C;
    int n;    
    bool leaf;
public:
    BTreeNode(int _t, bool _leaf);  
 
    void insertNonFull(int k);
     
    void splitChild(int i, BTreeNode *y);
   
    void traverse();
   
    BTreeNode *search(int k);  
 


friend class BTree;
};
 

class BTree
{
    BTreeNode *root;
    int t;  
public:
   
    BTree(int _t)
    {  root = NULL;  t = _t; }

    void inorder()
    {  if (root != NULL) root->traverse(); }

    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }

    void insert(int k);
    void BFS();
    void DFS();
    void veb();
};
 
// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;
 
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
 
    // Initialize the number of keys as 0
    n = 0;
}
 
void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        // cout<<"n: "<<n<<endl;
        if (leaf == false) {
            // cout<<endl;
            C[i]->traverse();
        }
        cout<<" "<<keys[i];
    }
    if (leaf == false) {
        cout<<endl;
        C[i]->traverse();
    }
}
 

BTreeNode *BTreeNode::search(int k)
{
   
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
   
    if (keys[i] == k)
        return this;
 
   
    if (leaf == true)
        return NULL;
 
   
    return C[i]->search(k);
}
 

void BTree::insert(int k)
{
   
    if (root == NULL)
    {
       
        root = new BTreeNode(t, true);
        root->keys[0] = k;  
        root->n = 1;  
    }
    else
    {
       
        if (root->n == 2*t-1)
        {
           
            BTreeNode *s = new BTreeNode(t, false);
           
            s->C[0] = root;
 
            s->splitChild(0, root);      
           
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
 
           
            root = s;
        }
        else  
            root->insertNonFull(k);
    }
}
 



void BTreeNode::insertNonFull(int k)
{
   
    int i = n-1;
 
   
    if (leaf == true)
    {
       
       
       
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
 
       
        keys[i+1] = k;
        n = n+1;
    }
    else
    {
       
        while (i >= 0 && keys[i] > k)
            i--;
 
       
        if (C[i+1]->n == 2*t-1)
        {
           
            splitChild(i+1, C[i+1]);
 
           
           
           
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 


void BTreeNode::splitChild(int i, BTreeNode *y)
{
   
   
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
 
   
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
 
   
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
 
   
    y->n = t - 1;
 
   
   
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
   
    C[i+1] = z;
 
   
   
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
 
   
    keys[i] = y->keys[t-1];
 
   
    n = n + 1;
}
 
void BTree::BFS(){
   
    if (root == NULL)  return;
 
   
    queue<BTreeNode *> q;
 
   
    q.push(root);
 
    while (q.empty() == false)
    {
       
        BTreeNode *node = q.front();
       
       
       
        for(int i = 0; i < node->n; i++){
            cout << node->keys[i]<<"-";
        }
        q.pop();
        cout<<endl;
        if (node->leaf == false){
            for(int i = 0; i < node->n +1; i++){
                q.push(node->C[i]);
            }
        }
    }
}

void BTree::DFS(){
vector<BTreeNode*> visited;

stack<BTreeNode*> to_visit;
to_visit.push(root);
while(!to_visit.empty()){
BTreeNode *curr_node = to_visit.top();
to_visit.pop();
if (find(visited.begin(), visited.end(), curr_node ) != visited.end()){

}
else{
for(int i = 0; i < curr_node->n;i++){
cout<<curr_node->keys[i]<<" ";
}
cout<<endl;
visited.push_back(curr_node);

}

for(int i = curr_node->n + 1 ; i > -1;i--){
if (find(visited.begin(), visited.end(), curr_node->C[i] ) != visited.end()){

}
else{
if (curr_node->C[i]){


to_visit.push(curr_node->C[i]);
}
}
}
}
}

void BTree::veb(){
int h = 0;
BTreeNode *temp = root;
while(temp != 0){
h+=1;

temp = temp->C[0];


}

temp = root;
queue<BTreeNode*> q;
vector<BTreeNode*> previous_level;
    q.push(root);
    int counter = 0;
    int total_nodes = 1;
    int prev_level = 1;
    for(int i = 1; i < h/2 + 1; i++){
   
    total_nodes += i*(2*root->t - 1);
    }
    for(int i = 1; i < h/2; i++){
   
    prev_level += i*(2*root->t - 1);
    }
    while (counter < total_nodes)
    {
        BTreeNode *node = q.front();
        if (counter < prev_level){
        for(int i = 0; i < node->n; i++){
           cout << node->keys[i]<<"-";
        }
        cout<<endl;
        }
        q.pop();
        if (node->leaf == false){
            for(int i = 0; i < node->n +1; i++){
                q.push(node->C[i]);
            }
        }
        if (counter >=prev_level){
        previous_level.push_back(node);
        }
    counter += 1;
    }
    cout<<endl;
    for(int i = 0; i < previous_level.size(); i++){
   
    queue<BTreeNode*> q2;
    q2.push(previous_level[i]);
    while (!q2.empty())
    {
        BTreeNode *node2 = q2.front();
        for(int i = 0; i < node2->n; i++){
           cout << node2->keys[i]<<"-";
        }
        q2.pop();
        cout<<endl;
        if (node2->leaf == false){
           for(int i = 0; i < node2->n +1; i++){
                q2.push(node2->C[i]);
            }
        }
    }
    }
}

int main()
{
    BTree t(2);
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);
    t.insert(60);
    t.insert(70);
    t.insert(80);
    t.insert(90);
    t.insert(100);
    t.insert(110);
    t.insert(120);
    t.insert(130);
    t.insert(140);
    t.insert(150);

   
    t.inorder();
    cout<<endl;
    t.BFS();
    cout<<endl;
    t.DFS();
    cout<<endl;
    t.veb();
 
    return 0;
} 