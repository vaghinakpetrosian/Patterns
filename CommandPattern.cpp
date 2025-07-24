#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>

class Editor;
class Application;
class Command;

class Command {
protected:
    Application* app;
    Editor* editor;  
    std::string backup; 

public:
    Command(Application* app, Editor* editor) : app(app), editor(editor) {}
    virtual ~Command() {}

    void saveBackup() {
        backup = editor->getText();
    }

    void undo() {
        editor->setText(backup);
    }

    virtual bool execute() = 0;
};

class Editor {
public:
    std::string text;

    std::string getSelection() const {
        return text;  
    }

    void deleteSelection() {
        text.clear(); 
    }

    void replaceSelection(const std::string& newText) {
        text = newText;  
    }

    std::string getText() const {
        return text;
    }

    void setText(const std::string& newText) {
        text = newText;
    }
};

class CopyCommand : public Command {
public:
    CopyCommand(Application* app, Editor* editor) : Command(app, editor) {}

    bool execute() override {
        app->clipboard = editor->getSelection();
        std::cout << "Copy: " << app->clipboard << std::endl;
        return false; 
    }
};

class CutCommand : public Command {
public:
    CutCommand(Application* app, Editor* editor) : Command(app, editor) {}

    bool execute() override {
        saveBackup();
        app->clipboard = editor->getSelection();
        editor->deleteSelection();
        std::cout << "Cut: " << app->clipboard << std::endl;
        return true;
    }
};

class PasteCommand : public Command {
public:
    PasteCommand(Application* app, Editor* editor) : Command(app, editor) {}

    bool execute() override {
        saveBackup();
        editor->replaceSelection(app->clipboard);
        std::cout << "Paste: " << editor->getText() << std::endl;
        return true;
    }
};

class UndoCommand : public Command {
public:
    UndoCommand(Application* app, Editor* editor) : Command(app, editor) {}

    bool execute() override {
        app->undo();
        return false;
    }
};

class CommandHistory {
private:
    std::stack<std::unique_ptr<Command>> history;

public:
    void push(std::unique_ptr<Command> command) {
        history.push(std::move(command));
    }

    Command* pop() {
        if (history.empty()) return nullptr;
        Command* cmd = history.top().release();
        history.pop();
        return cmd;
    }
};
class Application {
public:
    std::string clipboard;
    Editor editor;
    CommandHistory history;

    void executeCommand(std::unique_ptr<Command> command) {
        if (command->execute()) {
            history.push(std::move(command));
        }
    }

    void undo() {
        Command* command = history.pop();
        if (command) {
            command->undo();
            delete command;
        }
    }
};

int main() {
    Application app;
    app.editor.setText("Hello, World!");
    app.executeCommand(std::make_unique<CopyCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<CutCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<PasteCommand>(&app, &app.editor));
    app.executeCommand(std::make_unique<UndoCommand>(&app, &app.editor));
}
