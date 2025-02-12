#include "CommandAssigner.h"
#include "CommandParser.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <cstdlib>

std::vector<std::string> CommandAssigner::commands = {"exit", "echo", "type", "pwd"};

bool CommandAssigner::AssignCommands(const std::string &command, const std::string &input, bool &isRunning)
{
    CommandType commandT = findType(command);
    switch (commandT)
    {
    case CommandType::Builtin:
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
        else if (command == "pwd")
        {
            path.printCurrentDirectory();
        }
        else
        {
            return false;
        }
        return true;

    case CommandType::Executable:
        path.runExecutable(command, input);
        return true;

    default:
        return false;
    }
    return false;
}

void CommandAssigner::exit(const std::string &input, bool &isRunning)
{
    try
    {
        int exitCode = std::stoi(input.substr(input.find(" ") + 1));
        isRunning = false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid exit code: " << input.substr(5) << e.what() << std::endl;
    }
}

void CommandAssigner::echo(const std::string &input)
{
    std::cout << input.substr(input.find(" ") + 1) << std::endl;
}

void CommandAssigner::type(const std::string &input)
{
    CommandParser parse;
    std::string cmd = parse.secondArgument(input);
    CommandType cmdType = findType(cmd);
    switch (cmdType)
    {
    case CommandType::Builtin:
        std::cout << cmd << " is a shell builtin" << std::endl;
        break;
    case CommandType::Executable:
        std::cout << cmd << " is " << executableCommandPath << std::endl;
        break;
    default:
        std::cout << cmd << ": not found" << std::endl;
        break;
    }
}

CommandType CommandAssigner::findType(const std::string &cmd)
{
    auto iterator = std::find(commands.begin(), commands.end(), cmd);
    if (iterator != commands.end())
    {
        return CommandType::Builtin;
    }

    std::string exePath = path.findInPath(cmd);
    if (!exePath.empty())
    {
        executableCommandPath = exePath;
        return CommandType::Executable;
    }

    return CommandType::Invalid;
}
