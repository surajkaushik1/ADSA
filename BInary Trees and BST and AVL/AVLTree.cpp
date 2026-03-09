#include<bits/stdc++.h>
using namespace std;

class TreeNode{
    public:
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
    //constructor
    TreeNode(int val){
        data = val;
        height = 1;
        left = NULL;
        right = NULL;
    }

};
int Height(TreeNode *node){
    if(node == NULL) return 0;
    return node->height;
}
TreeNode *Rightrotation(TreeNode *x){
    TreeNode *y = x->left;
    TreeNode *T2 = y->right;
    //perform rotation
    y->right = x;
    x->left = T2;
    //update heights
    x->height = 1 + max(Height(x->left), Height(x->right));
    y->height = 1 + max(Height(y->left), Height(y->right));
    //return new root

    return y;
}
TreeNode *Leftrotation(TreeNode *x){
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;
    //perform rotation
    y->left = x;
    x->right = T2;
    //update heights
    x->height = 1 + max(Height(x->left), Height(x->right));
    y->height = 1 + max(Height(y->left), Height(y->right));
    //return new root

    return y;
}
TreeNode *Insert(TreeNode *root, int val){
    //base case
    if(root == NULL) return new TreeNode(val);
    if(val < root->data){
        root->left = Insert(root->left,val);
    }
    if(val > root->data){
        root->right = Insert(root->right,val);
    }
    else return root;

    root->height = 1 + max(Height(root->left), Height(root->right));

    int balancefactot = Height(root->left) - Height(root->right);

    //4 cases
    if(balancefactot > 1 && val < root->left->data){
        //Left Left case
        return Rightrotation(root);
    }
    if(balancefactot < -1 && val > root->right->data){
        //Right Right case
        return Leftrotation(root);
    }
    if(balancefactot > 1 && val > root->left->data){
        //Left Right case
        root->left = Leftrotation(root->left);
        return Rightrotation(root);
    }
    if(balancefactot < -1 && val < root->right->data){
        //Right Left case
        root->right = Rightrotation(root->right);
        return Leftrotation(root);
    }
    return root;


}
TreeNode *BSTInsertion(vector<int>&array){
    int len = array.size();
    if(len == 0) return NULL;
    TreeNode *root = NULL;
    for(int i = 0 ; i < len ; i++){
        root = Insert(root, array[i]);
    }
    return root;
}
void Inorder(TreeNode *root){
    if(root == NULL) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}
//Search 
bool Search(TreeNode *root , int key){
    if(root==NULL) return false;
    if(root->data == key) return true;
    if(key < root->data){
        return Search(root->left,key);
    }
    else{
        return Search(root->right,key);
    }

}
TreeNode *Findmin(TreeNode *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}
TreeNode *AVLDelete(TreeNode *root, int key){

    if(root == NULL) return NULL;

    if(key < root->data){
        root->left = AVLDelete(root->left,key);
    }
    if(key > root->data){
        root->right = AVLDelete(root->right,key);
    }
    else{
        //no child 
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        //One child
        if(root->left == NULL || root->right== NULL){
            TreeNode *temp;
            if(root->left != NULL){
                temp = root->left;
            }
            else{
                temp = root->right;
            }
            free(root);
            return temp;
        }
        //two children
        else{
            TreeNode *temp = Findmin(root->right);
            root->data = temp->data;
            root->right = AVLDelete(root->right,temp->data);
        }
    }
    //update height
    root->height = 1 + max(Height(root->left), Height(root->right));
    int balancefactor = Height(root->left) - Height(root->right);
    //4 cases
    if(balancefactor > 1 && Height(root->left->left) - Height(root->left->right) >= 0){
        //Left Left case
        return Rightrotation(root);
    }
    if(balancefactor < -1 && Height(root->right->left) - Height(root->right->right) <= 0){
        //Right Right case
        return Leftrotation(root);
    }
    if(balancefactor > 1 && Height(root->left->left) - Height(root->left->right) < 0){
        //Left Right case
        root->left = Leftrotation(root->left);
        return Rightrotation(root);
    }
    if(balancefactor < -1 && Height(root->right->left) - Height(root->right->right) > 0){
        //Right Left case
        root->right = Rightrotation(root->right);
        return Leftrotation(root);
    }
    
    return root;
}
int main(){
   
   vector<int>array = {3,2,1,5,6,4};
   TreeNode *root = BSTInsertion(array);
   Inorder(root);

   int key = 5;
   bool find = Search(root,key);

   root = AVLDelete(root,key);
   


}
