#pragma once
#include <string>
#include <vector>
#include "Path.h"
#include "CommandParser.h"

enum class CommandType
{
    Builtin,
    Executable,
    Invalid
};

class CommandAssigner
{
public:
    bool AssignCommands(const std::string &command, const std::string &input, bool &isRunning);
    CommandAssigner() = default;
    ~CommandAssigner() = default;

private:
    void echo(const std::string &input);
    void exit(const std::string &input, bool &isRunning);
    void type(const std::string &cmd);
    void cd(const std::string &input);

private:
    static std::vector<std::string> commands;
    CommandType findType(const std::string &cmd);

private:
    std::string executableCommandPath;
    CommandParser parse;
    Path path;
};
