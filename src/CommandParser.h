#pragma once
#include <string>
#include <vector>

class CommandParser
{

public:
    CommandParser() = default;
    ~CommandParser() = default;

    std::string secondArgument(const std::string &input);
    std::vector<std::string> splitPath(const std::string &path);

private:
    std::string text;
};
