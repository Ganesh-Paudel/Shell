#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

std::vector<std::string> commands = {"exit", "echo", "type"};

enum commandTypes
{
  Builtin,
  Executable,
  invalid,
};

struct Command
{
  commandTypes type;
  std::string path;
};

std::string removeWhiteSpaces(const std::string &str);
std::string commandFinder(const std::string &text);
void commandAssigner(Command cmd, std::vector<std::string> &args);
Command validCommand(const std::string &cmd);
std::string filePath(const std::string &command);
std::vector<std::string> splitArguments(std::string &txt, const char &splitter);
std::string findCommandInPath(const std::string &command, const std::string &path);

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  std::vector<std::string> arguments;
  bool running = true;

  while (running)
  {
    // cmd like appearance with dollar sign and input for the user
    std::cout << "$ ";
    std::getline(std::cin, input);
    // finding the command from the input using commandFinder function
    arguments = splitArguments(input, ' ');
    // command = commandFinder(input);
    Command command = validCommand(arguments[0]);

    if (command.type != invalid)
    {
      if (arguments[0] == "exit")
      {
        int exit_Code = static_cast<int>(std::stoi(arguments[1]));
        return exit_Code;
      }
      commandAssigner(command, arguments);
    }
    else
    {
      std::cout << arguments[0] << ": command not found" << std::endl;
    }
  }
}

void commandAssigner(Command cmd, std::vector<std::string> &args)
{

  if (cmd.type == Builtin)
  {

    if (args[0] == "echo")
    {
      for (int arg = 1; arg < args.size(); arg++)
      {
        if (arg != 1)
        {
          std::cout << " ";
        }
        std::cout << args[arg];
      }
      std::cout << "\n";
    }
    else if (args[0] == "type")
    {
      std::string commandArg = args[1];
      Command secondCommand = validCommand(args[1]);

      switch (secondCommand.type)
      {
      case Builtin:
        std::cout << commandArg << " is a shell builtin\n";
        break;
      case Executable:
        std::cout << commandArg << " is " << secondCommand.path << "\n";
        break;
      case invalid:
        std::cout << commandArg << ": not found\n";
        break;
      default:
        break;
      }
    }
    else if (args[0] == "pwd")
    {
      std::cout << std::filesystem::current_path().string() << std::endl;
    }
    else if (args[0] == "cd" && args[1].size() > 0)
    {
      std::string newPath = args[1];
      std::filesystem::path currentPath = std::filesystem::current_path();
      try
      {
        if (newPath[0] == '/' || newPath[0] == '\\')
        {
          if (std::filesystem::exists(newPath))
          {
            currentPath = newPath;
          }
        }
        else if (newPath[0] == '.')
        {
          std::filesystem::path filePath = currentPath / newPath;
          if (std::filesystem::exists(filePath))
          {
            currentPath = filePath;
          }
        }
        else
        {
          std::vector<std::string> dirs = splitArguments(newPath, '/');
          for (const std::string dir : dirs)
          {
            if (dir == "..")
            {
              currentPath = currentPath.parent_path();
            }
            else if (dir != "")
            {
              std::filesystem::path filePath = currentPath / dir;
              if (std::filesystem::exists(filePath))
              {
                currentPath = filePath;
              }
            }
          }
        }

        std::filesystem::current_path(currentPath);
      }
      catch (const std::filesystem::filesystem_error &e)
      {
        std::cout << args[0] << ": " << newPath << ": No such file or directory" << std::endl;
      }
    }
  }
  else if (cmd.type == Executable)
  {
    std::string commandWithPath = std::filesystem::path(cmd.path).filename().string();
    for (int i = 1; i < args.size(); i++)
    {
      commandWithPath += " ";
      commandWithPath += args[i];
    }

    const char *commandPtr = commandWithPath.c_str();
    system(commandPtr);
  }
}

std::string filePath(const std::string &command)
{
  std::string pathEnv = std::getenv("PATH");
  std::string path;

  char *p = &pathEnv[0];

  while (*p != '\0')
  {
    if (*p == ':')
    {
      std::string exe_path = findCommandInPath(command, path);
      if (exe_path != "")
      {
        return exe_path;
      }
      path = "";
    }
    else
    {
      path += *p;
    }
    p++;
  }
  std::string exe_path = findCommandInPath(command, path);
  if (exe_path != "")
  {
    return exe_path;
  }
  return "";
}

std::string findCommandInPath(const std::string &command, const std::string &path)
{
  for (const auto &entry : std::filesystem::directory_iterator(path))
  {
    if (entry.path().filename() == command)
    {
      return entry.path().string();
    }
  }
  return "";
}

Command validCommand(const std::string &command)
{
  std::vector<std::string> builtInCommands = {"echo", "exit", "type", "pwd", "cd"};

  for (const std::string &cmd : builtInCommands)
  {
    if (cmd == command)
    {
      Command comm;
      comm.type = commandTypes::Builtin;
      return comm;
    }
  }

  std::string executable_path = filePath(command);
  if (executable_path != "")
  {
    Command comm;
    comm.type = commandTypes::Executable;
    comm.path = executable_path;
    return comm;
  }

  Command comm;
  comm.type = commandTypes::invalid;
  return comm;
}

std::string removeWhiteSpaces(const std::string &str)
{
  size_t start = str.find_first_not_of(" \t\n\r\f\v");
  size_t end = str.find_last_not_of(" \t\n\r\f\v");

  if (start == std::string::npos || end == std::string::npos)
  {
    return "";
  }
  return str.substr(start, end - start + 1);
}

std::vector<std::string> splitArguments(std::string &txt, const char &splitter)
{
  std::vector<std::string> args;
  std::string arg;

  for (char c : txt)
  {
    if (c == splitter)
    {
      args.push_back(arg);
      arg = "";
    }
    else
    {
      arg += c;
    }
  }
  if (arg != "")
  {
    args.push_back(arg);
  }
  return args;
}