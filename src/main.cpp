#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

std::vector<std::string> commands = {"exit", "echo", "type"};

enum validCommands
{
  echo,
  cd,
  exit0,
  type,
  invalid,
};

std::string removeWhiteSpaces(const std::string &str);
std::string commandFinder(const std::string &text);
void commandAssigner(validCommands cmd, std::string &txt);
validCommands validCommand(const std::string &cmd);
std::string filePath(const std::string &command);

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  std::string command;
  bool running = true;

  while (running)
  {
    // cmd like appearance with dollar sign and input for the user
    std::cout << "$ ";
    std::getline(std::cin, input);
    // finding the command from the input using commandFinder function
    command = commandFinder(input);
    validCommands cmd = validCommand(command);

    if (cmd != invalid)
    {
      switch (cmd)
      {
      case exit0:
        running = false;
        break;
      default:
        commandAssigner(cmd, input);
      }
    }
    else
    {
      std::cout << command << ": command not found" << std::endl;
    }
  }
}

void commandAssigner(validCommands cmd, std::string &txt)
{
  switch (cmd)
  {
  case cd:

    break;
  case echo:
    txt.erase(0, txt.find(" ") + 1);
    std::cout << txt << std::endl;
    break;

  case type:
    txt.erase(0, txt.find(" ") + 1);
    if (validCommand(txt) != invalid)
    {
      std::cout << txt << " is a shell builtin\n";
    }
    else
    {
      // std::cout << txt << " not found \n";
      std::string path = filePath(txt);

      if (path.empty())
      {
        std::cout << txt << " not found \n";
      }
      else
      {
        std::cout << txt << " is " << path << std::endl;
      }
    }
    break;

  default:
    std::cout << txt << ": command not found" << std::endl;
    break;
  }
}

std::string filePath(const std::string &command)
{
  std::string pathEnv = std::getenv("PATH");
  std::stringstream ss(pathEnv);
  std::string path;

  while (!ss.eof())
  {
    std::getline(ss, path, ':');

    std::string abs_path = path + '/' + command;

    if (std::filesystem::exists(abs_path))
    {
      return abs_path;
    }
  }
  return "";
}

validCommands validCommand(const std::string &command)
{
  if (command == "echo")
    return validCommands::echo;
  if (command == "cd")
    return validCommands::cd;
  if (command == "exit")
    return validCommands::exit0;
  if (command == "type")
    return validCommands::type;

  return invalid;
}

// Second step finding the right command
std::string commandFinder(const std::string &text)
{
  // clean the data so there are no any leading or trailing whitespaces
  std::string String = removeWhiteSpaces(text);
  // this finds the first space whicch is the end of the command and the arguments starts

  size_t spacePos = String.find(' ');
  // if we find the space before the ending line
  // return the substring from beginning to spacepos
  if (spacePos != std::string::npos)
  {
    return String.substr(0, spacePos);
  }
  // else it's the whole string so return thw whole text
  return String;
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
