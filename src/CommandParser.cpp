#include "CommandParser.h"

std::string CommandParser::secondArgument(const std::string &input)
{
    size_t firstWhiteSpace = input.find(" ");

    return input.substr(firstWhiteSpace + 1);
}
