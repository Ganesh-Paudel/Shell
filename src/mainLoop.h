#pragma once
#include <string>

class mainLoop
{
private:
    bool isRunning;
    void init();
    std::string input;

public:
    mainLoop();
    ~mainLoop() = default;
};
