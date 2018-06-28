#include <iostream>
template <typename BeingCounted> 
class Counted {
public:
    class TooManyObjects{};
    int objectNum(){return numCounted;}
protected:
    Counted();
    Counted(const Counted& rhs);
    ~Counted(){--numCounted;};
private:
    static int numCounted;
    static const int maxCounted;
    void init();
};
template<typename BeingCounted>
Counted<BeingCounted>::Counted(){
    init();
}

template<typename BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&){
    init();
}

template<typename BeingCounted>
void Counted<BeingCounted>::init(){
    if(numCounted >= maxCounted) throw TooManyObjects();
    ++numCounted;
}

class Printer: private Counted<Printer> {
public:
    using Counted<Printer>::objectNum;
    Printer(){std::cout<<objectNum()<<'\n';}
};

template<typename Printer>
int Counted<Printer>::numCounted;

template<typename Printer>
const int Counted<Printer>::maxCounted=2;

int main(){
    Printer* p1 = new Printer();
    Printer* p2 = new Printer();
    delete p1;
    Printer* p3 = new Printer();
    delete p2;
    delete p3;
}

