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
            if (insideQuote)
            {
                insideQuote = false;
                activeQuote = '\0';
                currentPosition++;
                continue;
            }
            insideQuote = true;
            activeQuote = '\'';
        }
        else if (insideQuote && activeQuote == '\'')
        {
            argument += currentCharacter;
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
        }

        currentPosition++;
    }
    if (!argument.empty())
    {
        arguments.push_back(argument);
    }
    return arguments;
}
