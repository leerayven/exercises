class RCObject {
public:
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;
protected:
    RCObject();
    RCObject(const RCObject& rhs);
    RCObject& operator=(const RCObject& rhs);
    virtual ~RCObject() = 0;
private:
    int refCount;
    bool shareable;
};

template<typename T>
class RCPtr{
public:
    RCPtr(T* realPtr = 0);
    RCPtr(const RCPtr& rhs);
    ~RCPtr();

    RCPtr& operator=(const RCPtr& rhs);
    T* operator->() const;
    T* operator*() const;
private:
    T* pointee;
    void init();
};

class String {
public:
    String(const char* value = "");
    const char& operator[](int index) const;
    char& operator[](int index);
private:
    struct StringValue: public RCObject {
        char* data;
        StringValue(const char* initValue);
        StringValue(const StringValue& rhs);
        void init(const char* initValue);
        ~StringValue();
    };
    RCPtr<StringValue> value;
};

