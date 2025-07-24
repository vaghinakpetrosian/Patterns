#include <iostream>

class Button {
public:
    virtual void render() = 0;
};

class Checkbox {
public:
    virtual void render() = 0;
};

class WinButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows Button\n";
    }
};

class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac Button\n";
    }
};

class WinCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows Checkbox\n";
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac Checkbox\n";
    }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
};

class WinFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WinButton();
    }
    Checkbox* createCheckbox() override {
        return new WinCheckbox();
    }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacButton();
    }
    Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};

class Application {
private:
    Button* button;
    Checkbox* checkbox;
public:
    Application(GUIFactory* factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }
    void renderUI() {
        button->render();
        checkbox->render();
    }
};

int main() {
    GUIFactory* factory;
    string os = "mac";
    if (os == "windows")
        factory = new WinFactory();
    else
        factory = new MacFactory();
    Application app(factory);
    app.renderUI();
    delete factory;
}
