#include <iostream>

class CPU {
public:
    void start() { std::cout << "CPU started.\n"; }
    void stop()  { std::cout << "CPU stopped.\n"; }
};

class Memory {
public:
    void load() { std::cout << "Memory loaded.\n"; }
};

class Disk {
public:
    void read() { std::cout << "Disk read.\n"; }
};

class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    Disk disk;

public:
    void startComputer() {
        cpu.start();
        memory.load();
        disk.read();
        std::cout << "Computer started successfully.\n";
    }

    void shutdownComputer() {
        cpu.stop();
        std::cout << "Computer shut down successfully.\n";
    }
};
int main() {
    ComputerFacade computer;
    computer.startComputer();
    computer.shutdownComputer();
}
