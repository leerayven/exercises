#define NULL 0
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
    void insert(T v);
    bool remove(T v);
    rbtree();
    ~rbtree();
private:
    void insert_fixup(Node_t<T>* node);
    void remove_fixup(Node_t<T>* node);
    void left_rotate(Node_t<T>* node);
    void right_rotate(Node_t<T>* node);

    Node_t<T>* root;
    Node_t<T>* nil;
};

