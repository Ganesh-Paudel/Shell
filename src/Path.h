#pragma once
#include <string>

class Path
{
public:
    Path() = default;
    ~Path() = default;

public:
    std::string findInPath(const std::string &cmd) const;
    void runExecutable(const std::string &cmd, const std::string &txt);
    void printCurrentDirectory();

private:
    std::string findCommandInPath(const std::string &command, std::string &path) const;
};
