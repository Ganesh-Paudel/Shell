#pragma once
#include <string>

class Command
{
public:
    Command() = default;
    ~Command() = default;
    bool validCommand(std::string &input);

private:
};
