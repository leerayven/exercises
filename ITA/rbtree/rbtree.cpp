#include "rbtree.h"
//effective cpp
template<typename T>
rbtree<T>::rbtree()
{
    nil = new Node_t<T>();
    root = nil;
}

template<typename T>
rbtree<T>::~rbtree()
{
    //delete the tree
    
    delete nil;
}

template<typename T>
void rbtree<T>::left_rotate(Node_t<T>* node)
{
    auto orig_right = node->right;
    node->right = orig_right->left;
    if(node->right != nil){
        node->right->parent = node;
    }
    orig_right->parent = node->parent;
    if(node == root){
        root = orig_right;
    }else if(node == node->parent->left){
        node->parent->left = orig_right;
    }else{
        node->parent->right = orig_right;
    }
    orig_right->left = node;
    node->parent = orig_right;
}

template<typename T>
void rbtree<T>::right_rotate(Node_t<T>* node)
{
    auto orig_left = node->left;
    node->left = orig_left->right;
    if(node->left != nil){
        node->left->parent = node;
    }
    orig_left->right = node;
    orig_left->parent = node->parent;
    node->parent = orig_left;
    if(node->parent == nil){
        root = orig_left;
    }else if(orig_left->parent->left == node){
        orig_left->parent->left = orig_left;
    }else{
        orig_left->parent->right = orig_left;
    }
}

template<typename T>
void rbtree<T>::insert(T v){
    Node_t<T>* new_node = new Node_t<T>(v);
    new_node->parent = nil;
    new_node->left = nil;
    Node_t<T>* parent = nil, *child = root;
    while(child != nil){
        parent = child;
        if(v < child->value){
            child = child->left;
        }else{
            child = child->right;
        }
    }
    new_node->parent = parent;
    if(parent != nil){
        if(v < parent->value){
            parent->left = new_node;
        }else{
            parent->right = new_node;
        }
    }else{
        root = new_node;
    }
    //fix_up
    insert_fixup(new_node);
}

template<typename T>
static Node_t<T>* get_uncle(Node_t<T>* node){
    return node->parent->left == node ? node->parent->right : node->parent->left;
}


template<typename T>
static bool is_left(Node_t<T>* node){
    return node->parent->left == node;
}

template<typename T>
void rbtree<T>::insert_fixup(Node_t<T>* node)
{
    while(!node->parent->is_black){
        if(!get_uncle(node)->is_black){
        //case 1
            node->is_black = true;
            get_uncle(node)->is_black = true;
            node = node->parent->parent;
            node->is_black = false;
            continue;
        }
        if(!is_left(node) && is_left(node->parent)){
        //case 2
            left_rotate(node->parent);
            node = node->left;
        }else if(is_left(node) && !is_left(node->parent)){
        //mirror case 2
            right_rotate(node->parent);
            node = node->right;
        }else if(is_left(node) && is_left(node->parent)){
        //case 3
            right_rotate(node->parent->parent);
            node->parent->is_black = true;
            node->parent->right->is_black = false;
        }else{
        //mirror case 3
            left_rotate(node->parent->parent);
            node->parent->is_black = true;
            node->parent->left->is_black = false;
        }
    }
    root->is_black = true;
}

template<typename T>
void rbtree<T>::transplant(Node_t<T>* origNode, Node_t<T>* newNode)
{
    if(origNode == root){
        root = newNode;
        return;
    }
    if(is_left(origNode)){
        origNode->parent->left = newNode;
    }else{
        origNode->parent->right = newNode;
    }
    if(newNode != nil){
        newNode->parent = origNode->parent;
    }
}

template<typename T>
void rbtree<T>::remove(Node_t<T>* node)
{
    if(node->left == nil){
        transplant(node, node->right);
    }else if(node->right == nil){
        transplant(node, node->left);
    }else{
        auto rightChild = node->right;
        auto newSubRoot = rightChild;
        while(newSubRoot->left != nil){
            newSubRoot = newSubRoot->left;
        }
        if(newSubRoot != rightChild){
            transplant(newSubRoot, newSubRoot->right);
            newSubRoot->right = rightChild;
            rightChild->parent = newSubRoot;
        }
        transplant(node, newSubRoot);    
        newSubRoot->left = node->left;
        node->left->parent = newSubRoot;
    }
    remove_fixup();
}

template<typename T>
void rbtree<T>::remove(Node_t<T>* node)
{
}

template<typename T>
void rbtree<T>::remove_fixup(Node_t<T>* node)
{
}
