#include <vector>
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
    void decreaseKey();
    void deleteKey();
    FibonacciHeaps(): num(0), min(NULL){};
    ~FibonacciHeaps();
private:
    int num;
    Node* min;
    void deleteFibonacciHeaps();
};

FibonacciHeaps::~FibonacciHeaps(){
    deleteFibonacciHeaps();
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
    auto node2_prev = node2->next;
    node1->next = node2;
    node2->prev = node1;
    node1_next->prev = node2_prev;
    node2_prev->next = node1_next;
}

void concatHeaps(Node* node1, Node* node2){
    node2->next = node2;
    node2->prev = node2;
    node2->parent = node1;
    if(node1->child != NULL){
        concatLists(node2, node1->child);
    }else{
        node1->child = node2;
    }
    node1->degree += 1 + node2->degree;
}

int FibonacciHeaps::extractMin(){
    if(min == NULL) return -1;
    Node* curNode = NULL;
    if(min->next != min){
        curNode = min->next;
        //insert children to the root list;
        concatLists(curNode, min->child);
    }else{
        curNode = min->child;
    }
    int minKey = min->key;
    delete min;
    min = NULL;
    auto saveCurNode = curNode;
    
    //traverse the root list to merge subtrees
    vector<Node*> nodes(num, NULL); 
    do{
        if(nodes[curNode->degree] == NULL){
            nodes[curNode->degree] = curNode;
            curNode = curNode->next;
        }else{
            auto conflictNode = nodes[curNode->degree];
            nodes[curNode->degree] = NULL;
            if(curNode->key < conflictNode->key){
                concatHeaps(curNode, conflictNode);
                curNode = curNode->next;
            }else{
                auto nextNode = curNode->next;
                concatHeaps(conflictNode, curNode);
                curNode = nextNode;
            }
        }
    }while(curNode != saveCurNode)

    //traverse the root list to find the min node
    do{
    } while(false)
    return minKey;
}
