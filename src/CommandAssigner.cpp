#include "CommandAssigner.h"
#include <iostream>

bool CommandAssigner::AssignCommands(std::string &command, std::string &input, bool &isRunning)
{
    if (command == "exit")
    {
        exit(input, isRunning);
    }
    else if (command == "echo")
    {
        echo(input);
    }
    else
    {
        return false;
    }
    return true;
}

void CommandAssigner::exit(std::string &input, bool &isRunning)
{
    std::string exitCode = (input.substr(input.find("") + 1));
    isRunning = false;
}

void CommandAssigner::echo(std::string &input)
{
    std::cout << input.substr(input.find(" ") + 1) << std::endl;
}