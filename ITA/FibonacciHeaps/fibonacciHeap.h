#include <vector>
#include <queue>
#include <iostream>

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
    Node(int key):key(key), degree(0), next(this), prev(this), parent(NULL), child(NULL){};
};

class FibonacciHeaps{
public:
//    void createHeaps();
    void insertKey(int key);
    int extractMin();
    void mergeHeaps(FibonacciHeaps* someHeap);
    void decreaseKey();
    void deleteKey();
    void printHeaps();
    bool empty();
    FibonacciHeaps(): num(0), min(NULL){};
    ~FibonacciHeaps();
private:
    int num;
    Node* min;
    void deleteFibonacciHeaps();
    void consolidate(Node* curNode);
};

void FibonacciHeaps::deleteFibonacciHeaps(){

}

FibonacciHeaps::~FibonacciHeaps(){
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

//node1, node2 belong to list1 and list2 separately
void concatLists(Node* node1, Node* node2){
    auto node1_next = node1->next;
    auto node2_prev = node2->prev;
    node1->next = node2;
    node2->prev = node1;
    node1_next->prev = node2_prev;
    node2_prev->next = node1_next;
}

void removeNodeFromList(Node* node){
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

void concatHeaps(Node* node1, Node* node2){
    removeNodeFromList(node2);

    //add node2 to node1's children list
    node2->next = node2;
    node2->prev = node2;
    node2->parent = node1;
    if(node1->child != NULL){
        concatLists(node2, node1->child);
        if(node2->key < node1->child->key){
            node1->child = node2;
        }
    }else{
        node1->child = node2;
    }
    node1->degree += 1;
}


int FibonacciHeaps::extractMin(){
    if(min == NULL) return -1;
    int minKey = min->key;
    if(min->child != NULL){
        concatLists(min, min->child);
    }

    Node* curNode = min->next;
    bool need_to_consolidate = curNode != min;

    removeNodeFromList(min);
    delete min;
    min = NULL;

    if(need_to_consolidate){
        consolidate(curNode);
    }
    -- num;
    return minKey;
}

void FibonacciHeaps::consolidate(Node* curNode){
    //traverse the root list to merge subtrees
    vector<Node*> nodes(num, NULL); 
    while(true){
        if(nodes[curNode->degree] == curNode){
            break;
        }
        if(nodes[curNode->degree] == NULL){
            nodes[curNode->degree] = curNode;
            curNode = curNode->next;
        }else{
            auto nextNode = curNode->next;
            while(nodes[curNode->degree] != NULL){
                auto conflictNode = nodes[curNode->degree];
                nodes[curNode->degree] = NULL;
                if(curNode->key < conflictNode->key){
                    concatHeaps(curNode, conflictNode);
                }else{
                    concatHeaps(conflictNode, curNode);
                    curNode = conflictNode;
                }
            }
            nodes[curNode->degree] = curNode;
            curNode = nextNode;
        }
    }

    //traverse the root list to find the min node
    int newMinKey = __INT_MAX__;
    Node* newMinNode = NULL;
    for(Node* node : nodes){
        if(node != NULL && node->key < newMinKey){
            newMinNode = node;
            newMinKey = node->key;
        }
    }
    min = newMinNode;
}


void printListAddChild(Node* nodeInList, queue<Node*>* nodes_p){
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
        curNode = curNode->next;
    }while(curNode != saveNode);
    cout<<endl;
}

void FibonacciHeaps::printHeaps(){
    if(empty())
        return;
    queue<Node*> nodes;
    nodes.push(min);
    for(; !nodes.empty();){
        auto node = nodes.front();
        printListAddChild(node, &nodes);
        nodes.pop();
    }
}
