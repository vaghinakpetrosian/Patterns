#include <iostream>
#include <string>

class Internet {
public:
    virtual void connectTo(const string& site) = 0;
    virtual ~Internet() = default;
};

class RealInternet : public Internet {
public:
    void connectTo(const string& site) override {
        std::cout << "Connecting to " << site << endl;
    }
};

class ProxyInternet : public Internet {
private:
    RealInternet realInternet;
    string bannedSites[3] = { "facebook.com", "instagram.com", "tiktok.com" };

public:
    void connectTo(const string& site) override {
        for (const auto& banned : bannedSites) {
            if (site == banned) {
                std::cout << "Access Denied to " << site << endl;
                return;
            }
        }
        realInternet.connectTo(site);
    }
};

int main() {
    Internet* net = new ProxyInternet();
    net->connectTo("geeksforgeeks.org");
    net->connectTo("facebook.com");
    delete net;
}
