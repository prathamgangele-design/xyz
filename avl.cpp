#include <iostream>
using namespace std;

struct Node
{
    int player_id;
    int score;
    Node* left;
    Node* right;
    int height;
};

// Get height
int height(Node* n)
{
    if(n==NULL)
        return 0;
    return n->height;
}

// Maximum of two numbers
int max(int a,int b)
{
    return (a>b)?a:b;
}

// Create new node
Node* newNode(int player_id,int score)
{
    Node* node=new Node();
    node->player_id=player_id;
    node->score=score;
    node->left=NULL;
    node->right=NULL;
    node->height=1;

    return node;
}

// Right Rotation
Node* rightRotate(Node* y)
{
    Node* x=y->left;
    Node* T2=x->right;

    x->right=y;
    y->left=T2;

    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

    return x;
}

// Left Rotation
Node* leftRotate(Node* x)
{
    Node* y=x->right;
    Node* T2=y->left;

    y->left=x;
    x->right=T2;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;

    return y;
}

// Balance factor
int getBalance(Node* n)
{
    if(n==NULL)
        return 0;

    return height(n->left)-height(n->right);
}

// Insert Player
Node* insert(Node* node,int player_id,int score)
{
    if(node==NULL)
        return newNode(player_id,score);

    if(score < node->score)
        node->left=insert(node->left,player_id,score);

    else if(score > node->score)
        node->right=insert(node->right,player_id,score);

    else
    {
        if(player_id < node->player_id)
            node->left=insert(node->left,player_id,score);
        else
            node->right=insert(node->right,player_id,score);
    }

    node->height=1+max(height(node->left),height(node->right));

    int balance=getBalance(node);

    // LL Rotation
    if(balance>1 && score<node->left->score)
        return rightRotate(node);

    // RR Rotation
    if(balance<-1 && score>node->right->score)
        return leftRotate(node);

    // LR Rotation
    if(balance>1 && score>node->left->score)
    {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Rotation
    if(balance<-1 && score<node->right->score)
    {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find minimum node
Node* minValueNode(Node* node)
{
    Node* current=node;

    while(current->left!=NULL)
        current=current->left;

    return current;
}

// Delete Player
Node* deleteNode(Node* root,int player_id,int score)
{
    if(root==NULL)
        return root;

    if(score<root->score)
        root->left=deleteNode(root->left,player_id,score);

    else if(score>root->score)
        root->right=deleteNode(root->right,player_id,score);

    else if(player_id!=root->player_id)
    {
        root->left=deleteNode(root->left,player_id,score);
        root->right=deleteNode(root->right,player_id,score);
    }

    else
    {
        if(root->left==NULL || root->right==NULL)
        {
            Node* temp=root->left?root->left:root->right;

            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else
                *root=*temp;

            delete temp;
        }

        else
        {
            Node* temp=minValueNode(root->right);

            root->player_id=temp->player_id;
            root->score=temp->score;

            root->right=deleteNode(root->right,temp->player_id,temp->score);
        }
    }

    if(root==NULL)
        return root;

    root->height=1+max(height(root->left),height(root->right));

    int balance=getBalance(root);

    // LL
    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);

    // LR
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if(balance<-1 && getBalance(root->right)<=0)
        return leftRotate(root);

    // RL
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display Leaderboard (Descending Scores)
void leaderboard(Node* root)
{
    if(root!=NULL)
    {
        leaderboard(root->right);

        cout<<"Player ID: "<<root->player_id
            <<" | Score: "<<root->score<<endl;

        leaderboard(root->left);
    }
}

int main()
{
    Node* root=NULL;

    int choice,id,score;

    while(true)
    {
        cout<<"\n--- Multiplayer Game System ---\n";
        cout<<"1. Player Registration\n";
        cout<<"2. Display Leaderboard\n";
        cout<<"3. Remove Player\n";
        cout<<"4. Exit\n";
        cout<<"Enter Choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                cout<<"Enter Player ID and Score: ";
                cin>>id>>score;

                root=insert(root,id,score);

                cout<<"Player Registered Successfully!\n";
                break;

            case 2:
                cout<<"\nLeaderboard:\n";
                leaderboard(root);
                break;

            case 3:
                cout<<"Enter Player ID and Score to Remove: ";
                cin>>id>>score;

                root=deleteNode(root,id,score);

                cout<<"Player Removed Successfully!\n";
                break;

            case 4:
                return 0;

            default:
                cout<<"Invalid Choice!\n";
        }
    }
}
