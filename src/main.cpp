#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
std::vector<std::string> commands = {"exit", "echo", "type"};

std::string removeWhiteSpaces(const std::string &str);
std::string commandFinder(const std::string &text);
bool validCommand(const std::string &command);
void commandAssigner(const std::string &cmd, const std::string &txt);

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  std::string command;
  std::string exit = "exit 0";
  while (true)
  {
    std::cout << "$ ";
    std::getline(std::cin, input);

    command = commandFinder(input);
    if (validCommand(command))
    {
      if (command == "exit")
      {
        return 0;
      }
      commandAssigner(command, input);
    }
    else
    {
      std::cout << command << ": command not found" << std::endl;
    }
  }
}

std::string commandFinder(const std::string &text)
{
  std::string String = removeWhiteSpaces(text);
  size_t spacePos = String.find(' ');
  if (spacePos != std::string::npos)
  {
    return String.substr(0, spacePos);
  }
  return String;
}

bool validCommand(const std::string &command)
{
  auto it = std::find(commands.begin(), commands.end(), command);
  return it != commands.end();
}

void commandAssigner(const std::string &cmd, const std::string &txt)
{
  if (cmd.compare("echo") == 0)
  {
    if (txt.size() >= 5)
    {
      std::cout << txt.substr(5) << std::endl;
    }
    else
    {
      std::cout << "Error: Invalid echo command argument" << std::endl;
    }
  }
  else if (cmd.compare("type") == 0)
  {
    if (txt.size() >= 5)
    {

      std::string subCommand = txt.substr(5);
      if (validCommand(subCommand))
      {
        std::cout << subCommand << " is a shell builtin" << std::endl;
      }
      else
      {
        std::cout << subCommand << ": not found" << std::endl;
      }
    }
    else
    {
      std::cout << "Error: Invalid type command" << std::endl;
    }
  }
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