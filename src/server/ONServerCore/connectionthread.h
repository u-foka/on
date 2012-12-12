#ifndef COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONTHREAD_H
#define COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

#include <ONCommon/protocolfactory.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

template<typename Handler>
class ConnectionThread : public QRunnable
{
public:
    explicit ConnectionThread(const Common::ProtocolFactory &protocolFactory, int socketDescriptor);
    ~ConnectionThread();

    virtual void run() override;

private:
    static const QString _logModule;

    const Common::ProtocolFactory &_protocolFactory;
    int _socketDescriptor;

};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#include "connectionthread_inline.h"

#endif // COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONTHREAD_H
