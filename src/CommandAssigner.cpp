#include "CommandAssigner.h"

bool CommandAssigner::AssignCommands(std::string &command, std::string &input, bool &isRunning)
{
    if (command == "exit")
    {
        exit(input, isRunning);
        return true;
    }
    return false;
}

void CommandAssigner::exit(std::string &input, bool &isRunning)
{
    std::string exitCode = (input.substr(input.find("") + 1));
    isRunning = false;
}