#pragma once
#include <string>

class Command
{
public:
    Command() = default;
    ~Command();
    bool validCommand(std::string &input, bool &isRunning);

private:
    enum commands
    {
        exit,
        invalid
    };

    std::string commandFinder(std::string &input);
};
