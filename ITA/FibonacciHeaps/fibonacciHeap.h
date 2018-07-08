#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>

#ifndef NULL
#define NULL nullptr
#endif
using namespace std;
struct Node{
    int key;
    int degree;
    Node* next;
    Node* prev;
    Node* parent;
    Node* child;
    bool marked;
    Node(int key):key(key), degree(0), next(this), prev(this), parent(NULL), child(NULL), marked(false){};
};

class FibonacciHeaps{
public:
//    void createHeaps();
    void insertKey(int key);
    int extractMin();
    void mergeHeaps(FibonacciHeaps* someHeap);
    void decreaseKey(Node* node, int key);
    void deleteKey();
    void printHeaps(Node* node);
    bool empty();
    FibonacciHeaps(): num(0), min(NULL){};
    ~FibonacciHeaps();
private:
    int num;
    Node* min;
    void deleteFibonacciHeaps();
    void consolidate(Node* curNode);
    void cascadingMoveToRootList(Node* node);
};

void removeNodeFromList(Node* node){
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node;
    node->prev = node;
}

//node1, node2 belong to list1 and list2 separately
void concatLists(Node* node1, Node* node2){
    auto node1_next = node1->next;
    auto node2_prev = node2->prev;
    node1->next = node2;
    node2->prev = node1;
    node1_next->prev = node2_prev;
    node2_prev->next = node1_next;
}

void FibonacciHeaps::cascadingMoveToRootList(Node* node){
    if(node->parent == NULL){
        return;
    }
    auto parent = node->parent;
    if(node->next == node){
        parent->child = NULL;
    }else{
        parent->child = node->next;
        removeNodeFromList(node);
    }
    -- parent->degree;
    node->parent = NULL;
    node->marked = false;
    concatLists(node, min);
    if(node->key < min->key){
        min = node;
    }
    if(parent->marked == false){
        parent->marked = true;
    }else{
        cascadingMoveToRootList(parent);
    }
    
}

void FibonacciHeaps::decreaseKey(Node* node, int key){
    if(node->key <= key)
        return;
    node->key = key;
    cascadingMoveToRootList(node);
}

void FibonacciHeaps::deleteFibonacciHeaps(){
    if(min == NULL) return;
    queue<Node*> nodes;
    nodes.push(min);
    while(!nodes.empty()){
        auto node = nodes.front();
        auto saveNode = node;
        do{
            if(node->child != NULL){
                nodes.push(node->child);
            }
            auto nextNode = node->next;
            delete node;
            cout<<"delete in destructor."<<endl;
            node = nextNode;
        }while(node != saveNode);
        nodes.pop();
    }
}

FibonacciHeaps::~FibonacciHeaps(){
    cout<<"$#$#$#$#$#$#$#$#$#$#$#$\n";
    deleteFibonacciHeaps();
}

bool FibonacciHeaps::empty(){
    return num == 0;
}

void FibonacciHeaps::insertKey(int key){
    Node* node = new Node(key);
    if(min == NULL){
        min = node;
    }else{
        node->prev = min->prev;
        node->next = min;
        node->prev->next = node;
        min->prev = node; 
        if(key < min->key){
            min = node;
        }
    }
    ++ num;
}

void concatHeaps(Node* node1, Node* node2){
    removeNodeFromList(node2);
    //add node2 to node1's children list
    node2->parent = node1;
    ++ node1->degree;
    if(node1->child != NULL){
        concatLists(node2, node1->child);
        if(node2->key < node1->child->key){
            node1->child = node2;
        }
    }else{
        node1->child = node2;
    }
}


int FibonacciHeaps::extractMin(){
    if(min == NULL) return -1;
    int minKey = min->key;
    if(min->child != NULL){
        auto node = min->child;
        do{
            node->parent = NULL;
            node = node->next;
        }while(node != min->child);
        concatLists(min, min->child);
    }

    Node* curNode = min->next;
    bool need_to_consolidate = (curNode != min);
    if(need_to_consolidate){
        cout<<"consolidate: curNode key:"<<curNode->key<<endl;
    }else{
        cout<<"need not to conso, curNode key:" <<curNode->key<<endl;
    }

    removeNodeFromList(min);
    cout<<"the only delete happens here"<<endl;
    delete min;
    min = NULL;
    -- num;

    if(need_to_consolidate){
        consolidate(curNode);
        /*
        auto saveNode = curNode;
        min = curNode;
        do{
            if(curNode->key < min->key){
                min = curNode;
            }
            curNode = curNode->next;
        }while(curNode != saveNode);
        */
    }
    return minKey;
}

void FibonacciHeaps::consolidate(Node* curNode){
    //traverse the root list to merge subtrees
    cout<<"|||||||||||| start consolidate"<<endl;
    printHeaps(curNode);
    vector<Node*> nodes(100, NULL); 
    unordered_set<Node*> nodes_seen;
    while(true){
        cout<<"curNode key:"<<curNode->key<<", degree:"<<curNode->degree<<"confilict:"<<(nodes[curNode->degree]!=NULL)<<endl;
        if(nodes_seen.find(curNode) == nodes_seen.end()){
            nodes_seen.insert(curNode);
        }else{
            break;
        }
        auto nextNode = curNode->next;
        if(nodes[curNode->degree] == NULL){
            nodes[curNode->degree] = curNode;
        }else{
            while(nodes[curNode->degree] != NULL){
                cout<<"curNode key is:"<<curNode->key<<", degree:"<<curNode->degree<<"; the conflict key is"<<nodes[curNode->degree]->key<<", degree:"<<nodes[curNode->degree]->degree<<endl;
                auto conflictNode = nodes[curNode->degree];
                nodes[curNode->degree] = NULL;
                if(curNode->key < conflictNode->key){
                    concatHeaps(curNode, conflictNode);
                }else{
                    concatHeaps(conflictNode, curNode);
                    curNode = conflictNode;
                }
                printHeaps(curNode);
            }
            nodes[curNode->degree] = curNode;
        }
        curNode = nextNode;
    }

    //traverse the root list to find the min node
    int newMinKey = 100000;//__INT_MAX__;
    Node* newMinNode = NULL;
    for(Node* node : nodes){
        if(node != NULL && node->key < newMinKey){
            newMinNode = node;
            newMinKey = node->key;
        }
    }
    min = newMinNode;
    if(min == NULL){
        cout<<"curNode: NULL\n";
    }else{
        cout<<"curNode key: "<<min->key<<endl;
    }
}


void printListAddChild(Node* nodeInList, queue<Node*>* nodes_p, int& count){
    auto saveNode = nodeInList, curNode = nodeInList;
    do{
        if(curNode == saveNode){
            cout<<curNode->key<<"("<<curNode->degree<<")*"<<"  ";
        }else{
            cout<<curNode->key<<"("<<curNode->degree<<")"<<"  ";
        }
        if(curNode->child){
            nodes_p->push(curNode->child);
        }
        ++ count;
        curNode = curNode->next;
    }while(curNode != saveNode);
    cout<<endl;
}

void FibonacciHeaps::printHeaps(Node* tnode){
    if(tnode == NULL)
        return;
    int count = 0;
    queue<Node*> nodes;
    nodes.push(tnode);
    for(; !nodes.empty();){
        auto node = nodes.front();
        printListAddChild(node, &nodes, count);
        nodes.pop();
    }
    cout<<"node count:" <<count<<endl;
}
