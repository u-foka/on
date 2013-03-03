#ifndef COM_IWSTUDIO_ON_SERVERCORE_APPLICATION_H
#define COM_IWSTUDIO_ON_SERVERCORE_APPLICATION_H

#include <QString>
#include <QCoreApplication>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv);
    virtual ~Application();

    int run();
    
signals:
    
public slots:
    
private:
    static const QString _logModule;

};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_SERVERCORE_APPLICATION_H
