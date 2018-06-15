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
void insert_fixup(Node_t<T>* node)
{
}
