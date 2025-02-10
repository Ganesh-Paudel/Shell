#pragma once
#include <string>

class CommandAssigner
{
public:
    bool AssignCommands(std::string &command, std::string &input, bool &isRunning);
    CommandAssigner() = default;
    ~CommandAssigner() = default;

private:
    void echo(std::string &input);
    void exit(std::string &input, bool &isRunning);
};
