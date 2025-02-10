#pragma once
#include <string>

class CommandAssigner
{
public:
    bool AssignCommands(std::string &command, std::string &input, bool &isRunning);
    CommandAssigner() = default;
    ~CommandAssigner() = default;

private:
    void echo();
    void exit(std::string &input, bool &isRunning);
};
