#pragma once
#include <string>

class CommandParser
{

public:
    CommandParser() = default;
    ~CommandParser() = default;

    std::string secondArgument(std::string &input);

private:
    std::string text;
};
