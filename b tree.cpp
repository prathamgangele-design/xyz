// B-tree 
#include<iostream> 
using namespace std; 
 
#define MAX 2 
 
struct Node { 
    int keys[3]; 
    Node* child[4]; 
    int count; 
    bool leaf; 
}; 
 
Node* root = NULL; 
 
Node* createNode() { 
    Node* t = new Node; 
    t->count = 0; 
    t->leaf = true; 
    for(int i=0;i<4;i++) t->child[i] = NULL; 
    return t; 
} 
 
void insertNode(Node* node, int val) { 
    int i = node->count - 1; 
    while(i >= 0 && node->keys[i] > val) { 
        node->keys[i+1] = node->keys[i]; 
        i--; 
    } 
    node->keys[i+1] = val; 
    node->count++; 
} 
 
void insert(int val) { 
    if(root == NULL) { 
        root = createNode(); 
        root->keys[0] = val; 
        root->count = 1; 
        return; 
    } 
    insertNode(root, val); 
} 
 
void levelOrder() { 
    if(root == NULL) return; 
 
    Node* q[100]; 
    int front = 0, rear = 0; 
 
    q[rear++] = root; 
 
    while(front < rear) { 
        Node* temp = q[front++]; 
 
        for(int i=0;i<temp->count;i++) 
            cout << temp->keys[i] << " "; 
        cout << "| "; 
 
        for(int i=0;i<=temp->count;i++) { 
            if(temp->child[i] != NULL) 
                q[rear++] = temp->child[i]; 
        } 
    } 
    cout << endl; 
} 
 
void deleteKey(int val) { 
    if(root == NULL) return; 
 
    for(int i=0;i<root->count;i++) { 
        if(root->keys[i] == val) { 
            for(int j=i;j<root->count-1;j++) 
                root->keys[j] = root->keys[j+1]; 
            root->count--; 
            break; 
        } 
    } 
} 
 
int main() { 
    int n, val, choice; 
 
    while(1) { 
        cout << "\n1.Insert\n2.Display\n3.Delete\n4.Exit\n"; 
        cin >> choice; 
 
        if(choice == 1) { 
            cout << "Enter value: "; 
            cin >> val; 
            insert(val); 
        } 
        else if(choice == 2) { 
            levelOrder(); 
        } 
        else if(choice == 3) { 
            cout << "Enter value to delete: "; 
            cin >> val; 
            deleteKey(val); 
        } 
        else { 
            break; 
        } 
    } 
return 0; 
} 
