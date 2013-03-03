#ifndef COM_IWSTUDIO_ON_SERVERCORE_COMMANDINTERFACE_H
#define COM_IWSTUDIO_ON_SERVERCORE_COMMANDINTERFACE_H

#include <QObject>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

class CommandInterface : public QObject
{
    Q_OBJECT
public:
    explicit CommandInterface(QObject *parent = 0);
    
signals:
    void Quit();
    
public slots:
    void ProcessCommand(QString command);
};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_SERVERCORE_COMMANDINTERFACE_H
