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
      return 0;
    }
    else if (input.find("echo ") != std::string::npos)
    {
      std::cout << input.substr(5) << std::endl;
    }
    else
    {

      std::cout << input << ": command not found" << std::endl;
    }
  }
}
