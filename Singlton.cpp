#include <iostream>

class Singleton {
private:
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance; 
        return instance;
    }

    void doSomething() {
        std::cout << "Singleton is doing something.\n";
    }
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    s1.doSomething();
    Singleton& s2 = Singleton::getInstance();
    s2.doSomething();
    std::cout << "Addresses: " << &s1 << " == " << &s2 << "\n";
}
