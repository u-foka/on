#include "commandinterface.h"

#include <iostream>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

CommandInterface::CommandInterface(QObject *parent) :
    QObject(parent)
{
}

CommandInterface::~CommandInterface()
{
}

void CommandInterface::ProcessCommand(QString command)
{
    if (command.compare("help", Qt::CaseInsensitive) == 0) {
        std::cout << std::endl <<
                     "ON Server CLI help" << std::endl <<
                     std::endl <<
                     "Available commands:" << std::endl <<
                     "exit / quit: Terminates the server" << std::endl <<
                     "help: Shows this help message" << std::endl <<
                     std::endl <<
                     "For detailed help on a specific command use: help <cmd>" << std::endl <<
                     std::endl;

    } else if (command.compare("exit", Qt::CaseInsensitive) == 0 ||
        command.compare("quit", Qt::CaseInsensitive) == 0) {
        emit Quit();
    } else {
        std::cout << "Unknown command" << std::endl;
        std::cout << "Enter help to list the available commands." << std::endl;
    }
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
