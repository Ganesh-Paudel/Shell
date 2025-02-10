#include "CommandAssigner.h"
#include "CommandParser.h"
#include <iostream>
#include <algorithm>

std::vector<std::string> CommandAssigner::commands = {"exit", "echo", "type"};

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
    else if (command == "type")
    {
        type(input);
    }
    else
    {
        return false;
    }
    return true;
}

void CommandAssigner::exit(std::string &input, bool &isRunning)
{
    std::string exitCode = (input.substr(input.find(" ") + 1));
    isRunning = false;
}

void CommandAssigner::echo(std::string &input)
{
    std::cout << input.substr(input.find(" ") + 1) << std::endl;
}

void CommandAssigner::type(std::string &input)
{
    CommandParser parse;
    std::string cmd = parse.secondArgument(input);
    CommandType cmdType = findType(cmd);
    switch (cmdType)
    {
    case CommandType::Builtin:
        std::cout << cmd << " is a shell builtin" << std::endl;
        break;
    default:
        std::cout << cmd << ": not found" << std::endl;
        break;
    }
}

CommandType CommandAssigner::findType(std::string &cmd)
{
    auto iterator = std::find(commands.begin(), commands.end(), cmd);
    if (iterator != commands.end())
    {
        return CommandType::Builtin;
    }
    else
    {
        return CommandType::Invalid;
    }
}