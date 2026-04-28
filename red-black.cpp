// Redbalck-tree 
#include<iostream> 
using namespace std; 
 
enum Color {RED, BLACK}; 
 
struct Node { 
    string name; 
    Color color; 
    Node *le , *right, *parent; 
}; 
 
Node *root = NULL; 
 
Node* createNode(string name) { 
    Node* temp = new Node; 
    temp->name = name; 
    temp->color = RED; 
    temp->le = temp->right = temp->parent = NULL; 
    return temp; 
} 
 
void rotateLe (Node* &root, Node* &pt) { 
    Node* pt_right = pt->right; 
    pt->right = pt_right->le ; 
 
    if(pt->right != NULL) 
        pt->right->parent = pt; 
 
    pt_right->parent = pt->parent; 
 
    if(pt->parent == NULL) 
        root = pt_right; 
    else if(pt == pt->parent->le ) 
        pt->parent->le = pt_right; 
    else 
        pt->parent->right = pt_right; 
 
    pt_right->le = pt; 
    pt->parent = pt_right; 
} 
 
void rotateRight(Node* &root, Node* &pt) { 
    Node* pt_le = pt->le ; 
    pt->le = pt_le->right; 
 
    if(pt->le != NULL) 
        pt->le->parent = pt; 
 
    pt_le->parent = pt->parent; 
 
    if(pt->parent == NULL) 
        root = pt_le ; 
    else if(pt == pt->parent->le ) 
        pt->parent->le = pt_le ; 
    else 
        pt->parent->right = pt_le ; 
 
    pt_le->right = pt; 
    pt->parent = pt_le ; 
} 
 
void fixInsert(Node* &root, Node* &pt) { 
    Node* parent_pt = NULL; 
    Node* grand_parent_pt = NULL; 
 
    while((pt != root) && (pt->color != BLACK) && 
          (pt->parent->color == RED)) { 
 
        parent_pt = pt->parent; 
        grand_parent_pt = pt->parent->parent; 
 
        if(parent_pt == grand_parent_pt->le ) { 
            Node* uncle_pt = grand_parent_pt->right; 
 
            if(uncle_pt != NULL && uncle_pt->color == RED) { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
            else { 
                if(pt == parent_pt->right) { 
                    rotateLe (root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
                rotateRight(root, grand_parent_pt); 
                Color t = parent_pt->color; 
                parent_pt->color = grand_parent_pt->color; 
                grand_parent_pt->color = t; 
                pt = parent_pt; 
            } 
        } 
        else { 
            Node* uncle_pt = grand_parent_pt->le ; 
 
            if((uncle_pt != NULL) && (uncle_pt->color == RED)) { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
            else { 
                if(pt == parent_pt->le ) { 
                    rotateRight(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
                rotateLe (root, grand_parent_pt); 
                Color t = parent_pt->color; 
                parent_pt->color = grand_parent_pt->color; 
                grand_parent_pt->color = t; 
                pt = parent_pt; 
            } 
        } 
    } 
    root->color = BLACK; 
} 
 
void insert(string name) { 
    Node* pt = createNode(name); 
 
    Node* y = NULL; 
    Node* x = root; 
 
    while(x != NULL) { 
        y = x; 
        if(pt->name < x->name) 
            x = x->le ; 
        else 
            x = x->right; 
    } 
 
    pt->parent = y; 
 
    if(y == NULL) 
        root = pt; 
    else if(pt->name < y->name) 
        y->le = pt; 
    else 
        y->right = pt; 
 
    if(pt->parent == NULL) { 
        pt->color = BLACK; 
        return; 
    } 
 
    if(pt->parent->parent == NULL) 
        return; 
 
    fixInsert(root, pt); 
} 
 
Node* search(Node* root, string key) { 
    if(root == NULL || root->name == key) 
        return root; 
    if(key < root->name) 
        return search(root->le , key); 
    return search(root->right, key); 
} 
 
Node* minValue(Node* node) { 
    while(node->le != NULL) 
        node = node->le ; 
    return node; 
} 
 
Node* deleteNode(Node* root, string key) { 
    if(root == NULL) return root; 
 
    if(key < root->name) 
        root->le = deleteNode(root->le , key); 
    else if(key > root->name) 
        root->right = deleteNode(root->right, key); 
    else { 
        if(root->le == NULL) { 
            Node* temp = root->right; 
            delete root; 
            return temp; 
        } 
        else if(root->right == NULL) { 
            Node* temp = root->le ; 
            delete root; 
            return temp; 
        } 
 
        Node* temp = minValue(root->right); 
        root->name = temp->name; 
        root->right = deleteNode(root->right, temp->name); 
    } 
    return root; 
} 
 
void inorder(Node* root) { 
    if(root == NULL) return; 
    inorder(root->le ); 
    cout << root->name << "(" << (root->color==RED?"R":"B") << ") "; 
    inorder(root->right); 
} 
 
int main() { 
    int ch; 
    string name; 
 
    while(1) { 
        cout << "\n1.Insert\n2.Delete\n3.Display\n4.Exit\n"; 
        cin >> ch; 
 
        if(ch == 1) { 
            cout << "Enter directory name: "; 
            cin >> name; 
            insert(name); 
        } 
        else if(ch == 2) { 
            cout << "Enter directory to delete: "; 
            cin >> name; 
            root = deleteNode(root, name); 
        } 
        else if(ch == 3) { 
            inorder(root); 
            cout << endl; 
        } 
        else break; 
    } 
    return 0; 
} 
