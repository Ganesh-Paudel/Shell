#pragma once
#include <string>
#include <vector>

enum class CommandType
{
    Builtin,
    Invalid
};

class CommandAssigner
{
public:
    bool AssignCommands(std::string &command, std::string &input, bool &isRunning);
    CommandAssigner() = default;
    ~CommandAssigner() = default;

private:
    void echo(std::string &input);
    void exit(std::string &input, bool &isRunning);
    void type(std::string &cmd);

private:
    static std::vector<std::string> commands;
    CommandType findType(std::string &cmd);
};
