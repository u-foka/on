#ifndef COM_IWSTUDIO_ON_SERVERCORE_LISTENER_H
#define COM_IWSTUDIO_ON_SERVERCORE_LISTENER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <ONCommon/iprotocol.h>
#include <ONCommon/protocolfactory.h>

#include "connectionthread.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

class Listener : public QTcpServer
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = 0);
    virtual ~Listener();

    bool listen(const QHostAddress &address, quint16 port = 0);
    bool listen(quint16 port = 0);

signals:
    //void Accepted(ConnectionThread *thread);
    void ProtocolSelectionFailed(QTcpSocket *socket);
    
public slots:

protected:
    virtual void incomingConnection(int handle) override;
    
private:
    static const QString _logModule;

    Common::ProtocolFactory _protocolFactory;

};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_SERVERCORE_LISTENER_H
