#include <iostream>
#include <string>

bool validCommand(std::string &cmd);

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";

  std::string input;
  std::getline(std::cin, input);

  if (!validCommand(input))
  {
    std::cout << input << ": Command not found" << std::endl;
  }
}

bool validCommand(std::string &cmd)
{
  return false;
}
