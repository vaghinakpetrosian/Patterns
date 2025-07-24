#include <iostream>
#include <vector>

class ElementA;
class ElementB;

class Visitor {
public:
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;
};

class Element {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Element() = default;
};

class ElementA : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    void operationA() {
        std::cout << "ElementA operation\n";
    }
};

class ElementB : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    void operationB() {
        std::cout << "ElementB operation\n";
    }
};

class ConcreteVisitor : public Visitor {
public:
    void visit(ElementA* element) override {
        element->operationA();
        std::cout << "Visited ElementA\n";
    }
    void visit(ElementB* element) override {
        element->operationB();
        std::cout << "Visited ElementB\n";
    }
};

int main() {
    vector<Element*> elements = { new ElementA(), new ElementB() };
    ConcreteVisitor visitor;
    for (auto* e : elements) {
        e->accept(&visitor);
    }
    for (auto* e : elements) {
        delete e;
    }
}
