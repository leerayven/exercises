class Singleton{
public:
    static Singleton& get_instance();
private:
    Singleton();
    Singleton(const Singleton& );
};
Singleton& Singleton::get_instance(){
    static Singleton s;
    return s;
}
