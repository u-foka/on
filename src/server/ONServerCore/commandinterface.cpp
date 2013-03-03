#include "commandinterface.h"

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
    if (command.compare("exit", Qt::CaseInsensitive) == 0 ||
        command.compare("quit", Qt::CaseInsensitive) == 0) {
        emit Quit();
    }
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
