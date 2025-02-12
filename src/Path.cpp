#include "Path.h"
#include <filesystem>
#include <iostream>

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
    std::string absolutePath = cmd + " " + txt.substr(cmd.length() + 1);
    int result = system(absolutePath.c_str());
    if (result == -1)
    {
        std::cerr << "Error running executable: " << absolutePath << std::endl;
    }
}

void Path::printCurrentDirectory()
{
    std::cout << std::filesystem::current_path().string() << std::endl;
}