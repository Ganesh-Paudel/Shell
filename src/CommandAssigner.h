#pragma once
#include <string>
#include <vector>
#include "Path.h"

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
    void runExecutable(const std::string &cmd, const std::string &txt);

private:
    static std::vector<std::string> commands;
    CommandType findType(const std::string &cmd);
    std::string findInPath(const std::string &cmd) const;
    std::string findCommandInPath(const std::string &command, std::string &path) const;

private:
    std::string executableCommandPath;
    Path path;
};
