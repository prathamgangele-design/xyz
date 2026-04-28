//BST dic onary 
#include <iostream> 
#include <queue> 
using namespace std; 
 
struct Node { 
    string key, value; 
    Node* le ; 
    Node* right; 
}; 
 
Node* createNode(string key, string value) { 
    Node* temp = new Node(); 
    temp->key = key; 
    temp->value = value; 
    temp->le = temp->right = NULL; 
    return temp; 
} 
 
Node* insert(Node* root, string key, string value) { 
    if (root == NULL) 
        return createNode(key, value); 
 
    if (key < root->key) 
        root->le = insert(root->le , key, value); 
    else if (key > root->key) 
        root->right = insert(root->right, key, value); 
    else 
        root->value = value; 
 
    return root; 
} 
 
Node* minValueNode(Node* root) { 
    Node* curr = root; 
    while (curr && curr->le != NULL) 
        curr = curr->le ; 
    return curr; 
} 
 
Node* deleteNode(Node* root, string key) { 
    if (root == NULL) return root; 
 
    if (key < root->key) 
        root->le = deleteNode(root->le , key); 
    else if (key > root->key) 
        root->right = deleteNode(root->right, key); 
    else { 
        if (root->le == NULL) { 
            Node* temp = root->right; 
            delete root; 
            return temp; 
        } 
        else if (root->right == NULL) { 
            Node* temp = root->le ; 
            delete root; 
            return temp; 
        } 
 
        Node* temp = minValueNode(root->right); 
        root->key = temp->key; 
        root->value = temp->value; 
        root->right = deleteNode(root->right, temp->key); 
    } 
    return root; 
} 
 
void search(Node* root, string key) { 
    if (root == NULL) { 
        cout << "Word not found\n"; 
        return; 
    } 
 
    if (key == root->key) 
        cout << "Found: " << root->key << " -> " << root->value << endl; 
    else if (key < root->key) 
        search(root->le , key); 
    else 
        search(root->right, key); 
} 
 
void inorder(Node* root) { 
    if (root != NULL) { 
        inorder(root->le ); 
        cout << root->key << " -> " << root->value << endl; 
        inorder(root->right); 
    } 
} 
 
Node* mirror(Node* root) { 
    if (root == NULL) return NULL; 
 
    Node* temp = root->le ; 
    root->le = mirror(root->right); 
    root->right = mirror(temp); 
 
    return root; 
} 
 
Node* copyTree(Node* root) { 
    if (root == NULL) return NULL; 
 
    Node* newNode = createNode(root->key, root->value); 
    newNode->le = copyTree(root->le ); 
    newNode->right = copyTree(root->right); 
 
    return newNode; 
} 
 
void levelOrder(Node* root) { 
    if (root == NULL) return; 
 
    queue<Node*> q; 
    q.push(root); 
 
    while (!q.empty()) { 
        Node* curr = q.front(); 
        q.pop(); 
 
        cout << curr->key << " -> " << curr->value << endl; 
 
        if (curr->le != NULL) q.push(curr->le ); 
        if (curr->right != NULL) q.push(curr->right); 
    } 
} 
 
int main() { 
    Node* root = NULL; 
    Node* copyRoot = NULL; 
    int choice; 
    string key, value; 
 
    while (true) { 
        cout << "\n--- Dic onary BST ---\n"; 
        cout << "1. Insert Word\n"; 
        cout << "2. Delete Word\n"; 
        cout << "3. Search Word\n"; 
        cout << "4. Display Dic onary (Inorder)\n"; 
        cout << "5. Mirror Dic onary\n"; 
        cout << "6. Copy Dic onary\n"; 
        cout << "7. Display Copy\n"; 
        cout << "8. Level Order Display\n"; 
        cout << "9. Exit\n"; 
        cout << "Enter choice: "; 
        cin >> choice; 
 
        switch (choice) { 
            case 1: 
                cin >> key >> value; 
                root = insert(root, key, value); 
                break; 
 
            case 2: 
                cin >> key; 
                root = deleteNode(root, key); 
                break; 
 
            case 3: 
                cin >> key; 
                search(root, key); 
                break; 
 
            case 4: 
                inorder(root); 
                break; 
 
            case 5: 
                root = mirror(root); 
                cout << "Tree Mirrored\n"; 
                break; 
 
            case 6: 
                copyRoot = copyTree(root); 
                cout << "Tree Copied\n"; 
                break; 
 
            case 7: 
                inorder(copyRoot); 
                break; 
 
            case 8: 
                levelOrder(root); 
                break; 
 
            case 9: 
                return 0; 
 
            default: 
                cout << "Invalid Choice\n"; 
        } 
    } 
}
