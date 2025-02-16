#include "Command.h"
#include "CommandAssigner.h"
#include <iostream>

bool Command::validCommand(std::string &input, bool &isRunning)
{
    std::string command = commandFinder(input);
    // std::cout << command << std::endl;
    CommandAssigner assigner;

    if (!assigner.AssignCommands(command, input, isRunning))
    {
        std::cout << command << ": command not found" << std::endl;
    }
    return true;
}

std::string Command::commandFinder(std::string &input)
{
    if (input[0] == '\'' || input[0] == '"')
    {
        std::string command;
        if (input[0] == '\'')
        {
            size_t endPos = input.find('\'', 1);
            // std::cout << input.substr(0, endPos);
            return input.substr(1, endPos - 1);
        }
        else
        {
            // std::cout << "here";
            size_t currentPosition = 1;
            while (true)
            {
                char currentCharacter = input[currentPosition];
                if (currentCharacter == '"')
                {
                    break;
                }
                if (currentCharacter == '\\' && currentPosition + 1 < input.length())
                {
                    if (input[currentPosition + 1] == '\n')
                        command += '\n';
                    else if (input[currentPosition + 1] == '"')
                        command += '"';
                    else if (input[currentPosition + 1] == '\\')
                        command += '\\';
                    else
                    {
                        command += '\\';
                        command += input[currentPosition + 1];
                    }
                    currentPosition++;
                }
                else
                {
                    command += currentCharacter;
                }
                currentPosition++;
            }
        }
        return command;
    }
    else
    {
        size_t firstWhiteSpace = input.find(" ");
        return input.substr(0, firstWhiteSpace);
    }
}

Command::~Command()
{
}