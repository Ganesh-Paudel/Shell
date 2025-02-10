#include "Command.h"
#include "CommandAssigner.h"
#include <iostream>

bool Command::validCommand(std::string &input, bool &isRunning)
{
    std::string command = commandFinder(input);
    CommandAssigner assigner;

    if (!assigner.AssignCommands(command, input, isRunning))
    {
        return false;
    }
    return true;
}

std::string Command::commandFinder(std::string &input)
{
    size_t firstWhiteSpace = input.find(" ");
    return input.substr(0, firstWhiteSpace);
}

Command::~Command()
{
}