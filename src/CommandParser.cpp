#include "CommandParser.h"
#include <iostream>

std::string CommandParser::secondArgument(const std::string &input)
{
    size_t firstWhiteSpace = input.find(" ");

    return input.substr(firstWhiteSpace + 1);
}

std::vector<std::string> CommandParser::parseCommand(const std::string &input)
{
    /*
    vector that will store the arguments
    Approach:
    loop
     check the current character
         if it is a single quote
             then start single quote
             add all the character literally to it till the end of the quote
             once end is reached just end single quote
         if it is a space
             then check if argument is empty or not
             if empty
                 increment the character position
             else
                 just add the argument to the vector
                 clear the argument
                 increment the character position

     check if argument is empty
     if not:
         add the argument to the vector
     return the vector

    */
    std::vector<std::string> arguments;
    std::string argument;
    bool insideQuote = false;
    char activeQuote = '\0';

    size_t currentPosition = input.find(" ") + 1;

    while (currentPosition < input.length())
    {
        char currentCharacter = input[currentPosition];
        if (currentCharacter == '\'')
        {
            if (insideQuote && activeQuote == currentCharacter)
            {
                insideQuote = false;
                activeQuote = '\0';
                currentPosition++;
                continue;
            }
            else if (!insideQuote)
            {
                insideQuote = true;
                activeQuote = '\'';
            }
            else
            {
                argument += currentCharacter;
            }
        }
        else if (currentCharacter == '"')
        {
            if (insideQuote && activeQuote == currentCharacter)
            {
                insideQuote = false;
                activeQuote = '\0';
                currentPosition++;
                continue;
            }
            else if (!insideQuote)
            {

                insideQuote = true;
                activeQuote = '"';
            }
        }
        else if (insideQuote && activeQuote == '\'')
        {
            argument += currentCharacter;
        }
        else if (insideQuote && activeQuote == '"')
        {
            if (currentCharacter == '\\' && currentPosition + 1 < input.length())
            {
                if (input[currentPosition + 1] == '\n')
                    argument += '\n';
                else if (input[currentPosition + 1] == '"')
                    argument += '"';
                else if (input[currentPosition + 1] == '\\')
                    argument += '\\';
                else
                {
                    argument += '\\';
                    argument += input[currentPosition + 1];
                }
                currentPosition++;
            }
            else
            {
                argument += currentCharacter;
            }
        }
        else if (currentCharacter == '\\' && !insideQuote)
        {
            if (currentPosition + 1 < input.length())
            {
                if (input[currentPosition + 1] == '\n')
                {
                    currentPosition++;
                }
                else
                {
                    argument += input[currentPosition + 1];
                    currentPosition++;
                }
            }
        }
        else if (currentCharacter == ' ' && !insideQuote)
        {
            if (!argument.empty())
            {
                arguments.push_back(argument);
                argument.clear();
            }
        }
        else
        {
            argument += currentCharacter;
        // }
        // std::cout << "new loop: ->";
        // std::cout << "current character: " << currentCharacter << std::endl;
        // std::cout << "ARgument till now: " << argument << std::endl;
        // std::cout << std::endl;
        currentPosition++;
    }
    if (!argument.empty())
    {
        arguments.push_back(argument);
    }
    return arguments;
}
