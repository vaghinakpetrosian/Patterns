#include <iostream>
#include <string>
#include <stack>

class Memento {
    string state;
public:
    Memento(const string& s) : state(s) {}
    string getState() const { return state; }
};

class Editor {
    string content;
public:
    void write(const string& text) {
        content += text;
    }

    void show() const {
        std::cout << "Content: " << content << std::endl;
    }

    Memento save() const {
        return Memento(content);
    }

    void restore(const Memento& m) {
        content = m.getState();
    }
};

class History {
    stack<Memento> mementos;
public:
    void backup(const Memento& m) {
        mementos.push(m);
    }

    Memento undo() {
        if (mementos.empty()) return Memento("");
        Memento m = mementos.top();
        mementos.pop();
        return m;
    }
};

int main() {
    Editor editor;
    History history;
    editor.write("Hello");
    history.backup(editor.save());
    editor.write(", world!");
    history.backup(editor.save());
    editor.show();
    editor.restore(history.undo());
    editor.show();
    editor.restore(history.undo());
    editor.show();
}
