#include <iostream>
#include <vector>
#include <stdio.h>
template<typename T>
struct Node_t{
    Node_t<T>* left;
    Node_t<T>* right;
    Node_t<T>* parent;
    T value;
    bool is_black;
    Node_t(T v = 0):left(NULL), right(NULL), parent(NULL), is_black(false), value(v){}
};
template<typename T>
class rbtree{
public:
    void insert(T v);//FIXME argument should be pointer to node
    void remove(Node_t<T>* node);
    void traverse_leaves(std::vector<T>& leaf_values, std::vector<int>& heights);
    void traverse(std::vector<T>& values, std::vector<int>& heights, std::vector<bool>& colors);
    void printTree();
    Node_t<T>* lookup(T v, int* black_height);
    rbtree();
    ~rbtree();
private:
    void insert_fixup(Node_t<T>* node);
    void remove_fixup(Node_t<T>* node);
    void left_rotate(Node_t<T>* node);
    void right_rotate(Node_t<T>* node);
    void transplant(Node_t<T>* origNode, Node_t<T>* newNode);
    void delete_sub_tree(Node_t<T>* node);
    void inner_traverse_leaves(Node_t<T>* node, std::vector<T>& leaf_values,\
        std::vector<int>& heights, int counter);
    void inner_traverse(Node_t<T>* root, std::vector<T>& values, std::vector<int>& heights, std::vector<bool>& colors, int height);
    void printNode(Node_t<T>* node);
    int printSubTree();
    bool is_leaf(Node_t<T>* leaf);

    Node_t<T>* root;
    Node_t<T>* nil;
    
};

template<typename T>
void rbtree<T>::traverse_leaves(std::vector<T>& leaf_values, std::vector<int>& heights){
    inner_traverse_leaves(root, leaf_values, heights, 0);
}

template<typename T>
void rbtree<T>::inner_traverse_leaves(Node_t<T>* node, std::vector<T>& leaf_values, std::vector<int>& heights, int counter){
    if(node == nil){
        return;
    }
    if(node->left != nil){
        if(node->is_black)
            inner_traverse_leaves(node->left, leaf_values, heights, counter+1);
        else
            inner_traverse_leaves(node->left, leaf_values, heights, counter);
    }
    if(node->left == nil && node->right == nil){
        int height = node->is_black ? counter+1 : counter;
        leaf_values.push_back(node->value);
        heights.push_back(height);
    }
    if(node->right != nil){
        if(node->is_black)
            inner_traverse_leaves(node->right, leaf_values, heights, counter+1);
        else
            inner_traverse_leaves(node->right, leaf_values, heights, counter);
    }
}

template<typename T>
rbtree<T>::rbtree()
{
    nil = new Node_t<T>();
    nil->is_black = true;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    root = nil;
}

template<typename T>
void rbtree<T>::delete_sub_tree(Node_t<T>* node){
    if(node == nil)
        return;
    if(node->left != nil){
        delete_sub_tree(node->left);
    }
    if(node->right != nil){
        delete_sub_tree(node->right);
    }
    delete node;
}

template<typename T>
rbtree<T>::~rbtree()
{
    //delete the tree
    delete_sub_tree(root);
    delete nil;
}

template<typename T>
void rbtree<T>::traverse(std::vector<T>& values, std::vector<int>& heights, 
    std::vector<bool>& colors)
{
    inner_traverse(root, values, heights, colors, 0);
}

template<typename T>
void rbtree<T>::inner_traverse(Node_t<T>* root, std::vector<T>& values, std::vector<int>& heights,
    std::vector<bool>& colors, int height)
{
    if(root == nil){
        return;
    }
    if(root->is_black)
        inner_traverse(root->left, values, heights, colors, height+1);
    else
        inner_traverse(root->left, values, heights, colors, height+1);

    values.push_back(root->value);
    heights.push_back(height);
    colors.push_back(root->is_black);

    if(root->is_black)
        inner_traverse(root->right, values, heights, colors, height+1);
    else
        inner_traverse(root->right, values, heights, colors, height+1);
}

template<typename T>
Node_t<T>* rbtree<T>::lookup(T v, int* black_height){
    auto node = root;
    *black_height = 0;
    while(node != nil && node->value != v){
        if(node->is_black) ++ *black_height;
        if(v < node->value){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    if(node == nil){
        *black_height = 0;
        return NULL;
    }else{
        *black_height = node->is_black ? (1+*black_height) : *black_height;
        return node;
    }
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
    if(node->parent == nil){
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
    orig_left->parent = node->parent;
    if(node->parent == nil){
        root = orig_left;
    }else if(node == node->parent->left){
        node->parent->left = orig_left;
    }else{
        node->parent->right = orig_left;
    }
    orig_left->right = node;
    node->parent = orig_left;
}

template<typename T>
void rbtree<T>::insert(T v){
    Node_t<T>* new_node = new Node_t<T>(v);
    new_node->is_black = false;
    new_node->left = nil;
    new_node->right = nil;
    new_node->parent = nil;

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
    return node->parent->parent->left == node->parent ? \
        node->parent->parent->right : node->parent->parent->left;
}


template<typename T>
static bool is_left(Node_t<T>* node){
    return node->parent->left == node;
}

template<typename T>
void rbtree<T>::insert_fixup(Node_t<T>* node)
{
    while(node->parent->is_black == false){
        if(get_uncle(node)->is_black == false){
        //case 1
            std::cout<<"case 1:"<<"node value:"<<node->value<<std::endl<<std::flush;
            node->parent->is_black = true;
            get_uncle(node)->is_black = true;
            node = node->parent->parent;
            node->is_black = false;
            continue;
        }
        if(!is_left(node) && is_left(node->parent)){
        //case 2
            std::cout<<"case 2:"<<"node value:"<<node->value<<std::endl<<std::flush;
            left_rotate(node->parent);
            node = node->left;
        }else if(is_left(node) && !is_left(node->parent)){
            std::cout<<"case 2 mirror:"<<"node value:"<<node->value<<std::endl<<std::flush;
        //mirror case 2
            right_rotate(node->parent);
            node = node->right;
        }else if(is_left(node) && is_left(node->parent)){
        //case 3
            std::cout<<"case 3:"<<"node value:"<<node->value<<std::endl<<std::flush;
            right_rotate(node->parent->parent);
            node->parent->is_black = true;
            node->parent->right->is_black = false;
        }else{
        //mirror case 3
            std::cout<<"case 3 mirror:"<<"node value:"<<node->value<<std::endl<<std::flush;
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
    }else if(is_left(origNode)){
        origNode->parent->left = newNode;
    }else{
        origNode->parent->right = newNode;
    }
    newNode->parent = origNode->parent;
}

template<typename T>
void rbtree<T>::remove(Node_t<T>* node)
{
    bool need_to_fixup = node->is_black;
    auto fixup_node = nil;
    if(node->left == nil){
        fixup_node = node->right;
        transplant(node, node->right);
    }else if(node->right == nil){
        fixup_node = node->left;
        transplant(node, node->left);
    }else{
        auto rightChild = node->right;
        auto newSubRoot = rightChild;
        while(newSubRoot->left != nil){
            newSubRoot = newSubRoot->left;
        }
        need_to_fixup = newSubRoot->is_black;
        fixup_node = newSubRoot->right;
        fixup_node->parent = newSubRoot;
        if(newSubRoot != rightChild){
            transplant(newSubRoot, newSubRoot->right);
            newSubRoot->right = rightChild;
            newSubRoot->right->parent = newSubRoot;
        }
        transplant(node, newSubRoot);    
        newSubRoot->left = node->left;
        newSubRoot->left->parent = newSubRoot;
        newSubRoot->is_black = node->is_black;
        delete node;
    }
    if(need_to_fixup){
        remove_fixup(fixup_node);
    }
}

template<typename T>
inline Node_t<T>* get_brother(Node_t<T>* node){
    return is_left(node) ? node->parent->right : node->parent->left;
}

enum TreeFixupState{
    TreeState_Case_1 = 1,
    TreeState_Case_2,
    TreeState_Case_3,
    TreeState_Case_4,
};

template<typename T>
static TreeFixupState get_tree_state(Node_t<T>* node){
    Node_t<T>* brother = get_brother(node);
    if(brother->is_black == false) 
        return TreeState_Case_1;
    else if(brother->left->is_black && brother->right->is_black)
        return TreeState_Case_2;
    else if((is_left(node)&& brother->right->is_black == false)
            || (is_left(node) == false && brother->left->is_black == false))
        return TreeState_Case_4;
    else 
        return TreeState_Case_3;
}

template<typename T>
void rbtree<T>::remove_fixup(Node_t<T>* node)
{
    
    std::cout<<"\nin remove_fixup: "<<std::endl<<std::flush;
    if(node->is_black && node->parent != nil){
        std::cout<<"\nreally in remove_fixup: "<<std::endl<<std::flush;
    }
    TreeFixupState state;
    while(node->is_black && node->parent != nil){
        std::cout<<"\nnil is_black: "<<nil->is_black<<std::endl<<std::flush;
        Node_t<T>* brother = get_brother(node);
        std::cout<<"\nbrother is nil: "<<state<<std::endl<<std::flush;
        if(brother == nil){
            node = node->parent;
            break;
        }
        state = get_tree_state(node);
        std::cout<<"\ncase: "<<state<<std::endl<<std::flush;
        switch(state){
        case TreeState_Case_1:
            if(is_left(node)){
                left_rotate(node->parent);
            }else{
                right_rotate(node->parent);
            }
            node->parent->is_black = false;
            node->parent->parent->is_black = true;
            break;
        case TreeState_Case_2:
            brother->is_black = false;
            node = node->parent;
            break;
        case TreeState_Case_3:
            if(is_left(brother)){
                left_rotate(brother);
            }else{
                right_rotate(brother);
            }
            brother->is_black = false;
            brother->parent->is_black = true;
            break;
        case TreeState_Case_4:
            if(is_left(node)){
                left_rotate(node->parent);
            }else{
                right_rotate(node->parent);
            }
            std::swap(node->parent->is_black, node->parent->parent->is_black);
            get_brother(node->parent)->is_black = true;
            return;
        default:
            return;
       }
    }
    node->is_black = true;
}

template<typename T>
bool rbtree<T>::is_leaf(Node_t<T>* node){
    return node->left == nil && node->right == nil;
}

template<typename T>
void rbtree<T>::printNode(Node_t<T>* node){
        if (node != nil) {
                  auto parent = node->parent;
                  if (parent != nil) {
                          if (node == parent->left) {
                                  std::cout<<"L:";
                          } else if (node == parent->right) {
                                  std::cout<<"R:";
                          }
                  }
                  if (node->is_black == false) {
                          //printf("R:0x%08x\n", node->value);
                          printf("R: %dx\n", node->value);
                  } else {
                          //printf("B:0x%08x\n", node->value);
                          printf("B: %dx\n", node->value);
                  }
          }

}

template<typename T>
struct node_backlog {                                                                                                                                         
    /* Node backlogged */
    Node_t<T>* node;
    /* The index next to the backtrack point, valid when >= 1 */
    int next_sub_idx;
};  
const int RBTREE_MAX_LEVEL = 64;
#define RBTREE_LEFT_INDEX  0
#define RBTREE_RIGHT_INDEX 1
template<typename T>
static inline void 
nbl_push(struct node_backlog<T> *nbl, struct node_backlog<T> **top, struct node_backlog<T> **bottom) 
{   
    if (*top - *bottom < RBTREE_MAX_LEVEL) { 
        (*(*top)++) = *nbl; 
    } 
}   

template<typename T>
static inline struct node_backlog<T> *
nbl_pop(struct node_backlog<T> **top, struct node_backlog<T> **bottom)
{   
    return *top > *bottom ? --*top : NULL;
}   
      


template<typename T>
void rbtree<T>::printTree(){
          int level = 0;
          Node_t<T>* node = root;
          struct node_backlog<T> nbl, *p_nbl = NULL;
          struct node_backlog<T> *top, *bottom, nbl_stack[RBTREE_MAX_LEVEL];
  
          top = bottom = nbl_stack;
  
          for (; ;) {
                  if (node != nil) {
                          /* Fetch the pop-up backlogged node's sub-id.
                           * If not backlogged, fetch the first sub-id. */
                          int sub_index = p_nbl != NULL ? p_nbl->next_sub_idx : RBTREE_RIGHT_INDEX;
  
                          /* backlog should be reset since node has gone deep down */
                          p_nbl = NULL;
  
                          /* Backlog the node */
                          if (is_leaf(node) || sub_index == RBTREE_LEFT_INDEX) {

                                  nbl.node = nil;
                                  nbl.next_sub_idx = RBTREE_RIGHT_INDEX;
                          } else {
                                  nbl.node = node;
                                  nbl.next_sub_idx = RBTREE_LEFT_INDEX;
                          }
                          nbl_push(&nbl, &top, &bottom);
                          level++;
  
                          /* Draw lines as long as sub_idx is the first one */
                          if (sub_index == RBTREE_RIGHT_INDEX) {
                                  int i;
                                  for (i = 1; i < level; i++) {
                                          if (i == level - 1) {
                                                  printf("%-8s", "+-------");
                                          } else {
                                                  if (nbl_stack[i - 1].node != nil) {
                                                          printf("%-8s", "|");
                                                  } else {
                                                          printf("%-8s", " ");                                                                                  
                                                  }
                                          }
                                  }
                                  printNode(node);
                          }
  
                          /* Move down according to sub_idx */
                          node = sub_index == RBTREE_LEFT_INDEX ? node->left : node->right;
                  } else {
                          p_nbl = nbl_pop(&top, &bottom);
                          if (p_nbl == NULL) {
                                  /* End of traversal */
                                  break;
                          }
                          node = p_nbl->node;
                          level--;
                  }
          }
    
}

template<typename T>
int rbtree<T>::printSubTree(){
    
}
