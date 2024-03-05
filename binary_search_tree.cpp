#include<bits/stdc++.h>
using namespace std;
typedef	long long ll;
class BinarySearchTree{
private:
    int key;
    BinarySearchTree * left;
    BinarySearchTree * right;
    BinarySearchTree * parent;



public:
    BinarySearchTree(){
        left = right = parent = NULL;
        key = 0;
    }
    BinarySearchTree(int key):key(key){
        left = right = parent = NULL;
    }

    static BinarySearchTree * Insert(BinarySearchTree * root , int key)
    {
        if(root == NULL){
            return new BinarySearchTree(key);
        }
        else if(root->key <= key){
            root->right = Insert(root->right , key);
            root->right->parent = root;
        }
        else{
            root->left = Insert(root->left , key);
            root->left->parent = root;
        }

        return  root;

    }
    static BinarySearchTree *  Search(BinarySearchTree * root , int key){
        if(root == NULL){
            return root;
        }
        else if(root->key  > key){
            Search(root->left , key);
        }
        else if(root->key  < key){
            Search(root->right , key);
        }
        else{
            return root;
        }


    }
    static void TraverseInorder(BinarySearchTree * root){
        if(root == NULL){
            return;
        }
        TraverseInorder(root->left);
        cout<<root->key<<' ';
        TraverseInorder(root->right);
    }
    static BinarySearchTree * FindMax(BinarySearchTree * root){
        if(root == NULL){
            return root;
        }
        if(root->right == NULL){
            return root;
        }
        else{
            FindMax(root->right);
        }
    }

    static BinarySearchTree * FindMin(BinarySearchTree * root){
        if(root == NULL){
            return root;
        }
        if(root->left == NULL){
            return root;
        }
        else{
            FindMin(root->left);
        }
    }
    /*
     *    Successor mean get next inorder value
     *                  20
     *                 /  \
     *                8    22
     *               / \
     *              4  12
     *                 / \
     *                10 14
     *     Successor(8) = 10 , Successor(10) = 12 , Successor(14) = 20
     *     Predecessor(20) = 10 , Predecessor(8) = 4
     */
    static BinarySearchTree * Successor(BinarySearchTree * root , int key){
        // Search for element to you want to get Successor for it
        BinarySearchTree * target = BinarySearchTree::Search(root , key);
        if(target == NULL){
            return target;
        }

        else if(target->right){
            return FindMin(target->right);
        }
        else{
            BinarySearchTree *parent = target->parent;
            while (parent != NULL && parent->key < key){
                parent = parent->parent;
            }
            return parent;
        }
    }
    static BinarySearchTree * Predecessor(BinarySearchTree * root , int key){
        // Search for element to you want to get predecessor for it
        BinarySearchTree * target = BinarySearchTree::Search(root , key);
        if(target == NULL){
            return target;
        }

        else if(target->left){
            return FindMax(target->left);
        }
        else{
            BinarySearchTree *parent = target->parent;
            while (parent != NULL && parent->key > key){
                parent = parent->parent;
            }
            return parent;
        }
    }
static BinarySearchTree  *  Remove(BinarySearchTree *   root , int key)
{
    // Search for element to you want to remove it
    BinarySearchTree * target = BinarySearchTree::Search(root , key);

   // Case node found
    if(target != NULL ){

        // Case this node is leaf
        if(target->left == NULL && target->right == NULL)
        {
            // check this node not root
            if(root != target){
                // check case this node is left or right of it's parent to remove it
                if(target->parent->left->key == key){
                    target->parent->left = NULL;
                }
                else if(target->parent->right->key == key){
                    target->parent->right = NULL;
                }
                target = NULL;
            }
            else
                root = NULL;

        }
        // Case node has one of children only
        /*
         *      50                  50
         *      / \                 / \
         *     25  75              25 75
         *     /\       ------>    /\
         *    12 30               6 30
         *    /
         *    6
         *
         */
        else if(target->left == NULL || target->right == NULL){
            BinarySearchTree * child = (target->right ? target->right : target->left);
            target->key = child->key;
            target->left = child->left;
            target->right = child->right;
            child = NULL;
            delete child;
        }
        // case node has 2 child
        // replace node with inorder for it
        /*
         * This example case want to delete 50 , so get successor(50) = 52 and replace with it
         *        50                   52
         *      /    \                /  \
         *     25    75              25  75
         *     /\    /     ------>   /\  /
         *    12 30  60             6 30 60
         *    /      /\                   \
         *    6     52 70                  70
         */
        else{
            BinarySearchTree * successor = BinarySearchTree::Successor(root , key);
            target->key = successor->key;
            if(successor->parent->left->key == successor->key){
                successor->parent->left = NULL;
            }
            else if(successor->parent->right->key == successor->key){
                successor->parent->right = NULL;
            }
            successor = NULL;
        }

    }



    return root;

}

    int getKey(){
        return this->key;
    }

};
int main()
{
    BinarySearchTree * root = NULL;
    while(true){
        cout<<"1- Insert Node in Binary Search Tree\n";
        cout<<"2- Print Binary Search Tree\n";
        cout<<"3- Search For Element\n";
        cout<<"4- Find Maximum Value\n";
        cout<<"5- Find Minimum Value\n";
        cout<<"6- Find Successor for Specific value\n";
        cout<<"7- Find Predecessor for Specific value\n";
        cout<<"8- Remove Specific value\n";
        cout<<"9- Exit\n";
        int op;
        cin>>op;
        if(op == 1){
            int key;
            cout<<"Enter the value do you want to insert: ";
            cin>>key;
            root = BinarySearchTree::Insert(root , key);
        }
        else if(op == 2){
            BinarySearchTree::TraverseInorder(root);
            cout<<'\n';
        }
        else if(op == 3){
            int key;
            cout<<"Enter the value do you want to search: ";
            cin>>key;
            BinarySearchTree * element = BinarySearchTree::Search(root , key);
            if(element){
                cout<<"Element found\n";
            }
            else{
                cout<<"Element of value =  "<<key<<" not found\n";
            }
        }
        else if(op == 4){
            BinarySearchTree * maxElement = BinarySearchTree::FindMax(root);
            if(maxElement){
                cout<<"MAX Element : "<<maxElement->getKey()<<'\n';
            }
        }
        else if(op == 5){
            BinarySearchTree * minElement = BinarySearchTree::FindMin(root);
            if(minElement){
                cout<<"Min Element : "<<minElement->getKey()<<'\n';
            }
        }
        else if(op == 6){
            int key;
            cout<<"Enter the value do you want to get Successor for it: ";
            cin>>key;
            BinarySearchTree * element = BinarySearchTree::Successor(root , key);
            if(element){
                cout<<"Successor of ("<<key<<") : "<<element->getKey()<<"\n";
            }
            else{
                cout<<"No Successor for value =   "<<key<<"\n";
            }
        }
        else if(op == 7){
            int key;
            cout<<"Enter the value do you want to get Predecessor for it: ";
            cin>>key;
            BinarySearchTree * element = BinarySearchTree::Predecessor(root , key);
            if(element){
                cout<<"Predecessor of ("<<key<<") : "<<element->getKey()<<"\n";
            }
            else{
                cout<<"No Successor for value =   "<<key<<"\n";
            }
        }
        else if(op == 8){
            int key;
            cout<<"Enter the value do you want to remove: ";
            cin>>key;
            root = BinarySearchTree::Remove(root , key);
        }
        else if(op == 9){
            break;
        }



    }

}
