#include <vector>
using namespace std;
class protoVEB
{
public:
    bool find(int key);
    int getSuccessor(int key);
    void insert(int key);
    void remove(int key);
    protoVEB(size_t size);
    ~protoVEB();
private:
    size_t universalSize;
    protoVEB* summary;
    vector<protoVEB*> cluster;
};
protoVEB::protoVEB(size_t size): universalSize(size){
    
}
