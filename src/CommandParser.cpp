#include "CommandParser.h"
#include <iostream>

std::string CommandParser::secondArgument(const std::string &input)
{
    size_t firstWhiteSpace = input.find(" ");

    return input.substr(firstWhiteSpace + 1);
}

std::vector<std::string> CommandParser::parseCommand(const std::string &input)
{
    std::vector<std::string> argumentS;
    std::string argument;
    size_t cmdLength = input.find(" ");
    // std::cout << cmdLength << std::endl;
    size_t i = cmdLength + 1;

    while (i < input.length())
    {
        char c = input[i];
        if (c == '\'')
        {
            if (!argument.empty())
            {
                argumentS.push_back(argument);
                argument.clear();
            }
            size_t endPos = input.find("\'", i + 1);
            // std::cout << endPos << std::endl;
            if (endPos == std::string::npos)
            {
                argument = input.substr(i + 1, endPos - 2 - cmdLength);
                argumentS.push_back(argument);
                argument.clear();
            }
            else
            {
                argument = input.substr(i + 1, endPos - 2 - cmdLength);
                i = endPos + 1;
            }
        }
        else
        {
            argument.push_back(c);
            // std::cout << c << std::endl;
            i++;
        }
    }
    if (!argument.empty())
    {
        argumentS.push_back(argument);
    }
    return argumentS;
}
