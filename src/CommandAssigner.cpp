#include "CommandAssigner.h"
#include "CommandParser.h"
#include <iostream>
#include <algorithm>
#include <filesystem>

std::vector<std::string> CommandAssigner::commands = {"exit", "echo", "type"};

bool CommandAssigner::AssignCommands(const std::string &command, const std::string &input, bool &isRunning)
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

    std::string exePath = findInPath(cmd);
    if (!exePath.empty())
    {
        executableCommandPath = exePath;
        return CommandType::Executable;
    }

    return CommandType::Invalid;
}

std::string CommandAssigner::findInPath(const std::string &cmd) const
{
    std::string pathEnv = std::getenv("PATH");
    std::string path;

    char *p = &pathEnv[0];

    while (*p != '\0')
    {
        if (*p == ':')
        {
            std::string exePath = findCommandInPath(cmd, path);
            if (!exePath.empty())
            {
                return exePath;
            }
            path = "";
        }
        else
        {
            path += *p;
        }
        p++;
    }
    std::string exePath = findCommandInPath(cmd, path);
    if (!exePath.empty())
    {
        return exePath;
    }
    return "";
}

std::string CommandAssigner::findCommandInPath(const std::string &command, std::string &path) const
{
    try
    {
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                if (entry.path().filename() == command)
                {
                    return entry.path().string();
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error accessing directory: " << path << " - " << e.what() << std::endl;
    }
    return "";
}