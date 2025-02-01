#include <iostream>
#include <string>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  std::string exit = "exit 0";
  while (true)
  {
    std::cout << "$ ";
    std::getline(std::cin, input);

    if (input.compare(exit) == 0)
    {
      break;
    }

    std::cout << input << ": command not found" << std::endl;
  }
}
