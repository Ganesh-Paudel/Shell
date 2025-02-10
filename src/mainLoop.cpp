#include "mainLoop.h"
#include "Command.h"
#include <iostream>

mainLoop::mainLoop() : isRunning(true), input("")
{
    init();
}

void mainLoop::init()
{
    Command command;

    while (isRunning)
    {
        // Flush after every std::cout / std:cerr
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;

        std::cout << "$ ";
        std::getline(std::cin, input);
        if (!command.validCommand(input))
        {
            std::cout << input << ": command not found" << std::endl;
        }
    }
}
