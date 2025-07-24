#include <iostream>
#include <memory>

class Light {
public:
    void turnOn() { std::cout << "Light is ON\n"; }
    void turnOff() { std::cout << "Light is OFF\n"; }
};

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class TurnOnCommand : public Command {
private:
    Light* light;
public:
    TurnOnCommand(Light* l) : light(l) {}
    void execute() override { light->turnOn(); }
};

class TurnOffCommand : public Command {
private:
    Light* light;
public:
    TurnOffCommand(Light* l) : light(l) {}
    void execute() override { light->turnOff(); }
};

class RemoteControl {
private:
    Command* command;
public:
    void setCommand(Command* cmd) { command = cmd; }
    void pressButton() { command->execute(); }
};

int main() {
    Light livingRoomLight;
    TurnOnCommand on(&livingRoomLight);
    TurnOffCommand off(&livingRoomLight);
    RemoteControl remote;
    remote.setCommand(&on);
    remote.pressButton();
    remote.setCommand(&off);
    remote.pressButton(); 
}
