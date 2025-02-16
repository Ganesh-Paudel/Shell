#include "Path.h"
#include "CommandParser.h"
#include <filesystem>
#include <iostream>
#include <vector>

std::string Path::findInPath(const std::string &cmd) const
{
    std::string pathEnv = std::getenv("PATH");
    std::string path;

    char *p = &pathEnv[0];

    while (*p != '\0')
    {
        if (*p == ':')
        {
            std::string exePath = findCommandInPath(cmd, path);
            if (!exePath.empty())
            {
                return exePath;
            }
            path = "";
        }
        else
        {
            path += *p;
        }
        p++;
    }
    std::string exePath = findCommandInPath(cmd, path);
    if (!exePath.empty())
    {
        return exePath;
    }
    return "";
}

std::string Path::findCommandInPath(const std::string &command, std::string &path) const
{
    try
    {
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                if (entry.path().filename() == command)
                {
                    return entry.path().string();
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error accessing directory: " << path << " - " << e.what() << std::endl;
    }
    return "";
}

void Path::runExecutable(const std::string &cmd, const std::string &txt)
{
    CommandParser parse;
    if (cmd[0] == '\'' || cmd[0] == '"')
    {
        std::vector<std::string> command = parse.parseCommand(cmd);
        std::string absolutePath = command[0] + " " + txt.substr(cmd.length() + 1);
        int result = system(absolutePath.c_str());
        if (result == -1)
        {
            std::cerr << "Error running executable: " << absolutePath << std::endl;
        }
    }
    else
    {

        std::string absolutePath = cmd + " " + txt.substr(cmd.length() + 1);
        int result = system(absolutePath.c_str());
        if (result == -1)
        {
            std::cerr << "Error running executable: " << absolutePath << std::endl;
        }
    }
}

void Path::printCurrentDirectory()
{
    std::cout << std::filesystem::current_path().string() << std::endl;
}

void Path::goTo(const std::string &dir)
{
    try
    {
        if (dir == "~")
        {
            std::string homeDir;
#if defined(__linux__) || defined(__APPLE__)
            homeDir = std::getenv("HOME");
#elif defined(_WIN32)
            homeDir = std::getenv("USERPROFILE");
#endif
            if (!homeDir.empty())
            {
                std::filesystem::current_path(homeDir);
            }
        }
        else
        {

            std::filesystem::current_path(dir);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "cd: " << dir << ": No such file or directory" << std::endl;
    }
}