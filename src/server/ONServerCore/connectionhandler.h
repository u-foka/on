#ifndef COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONHANDLER_H
#define COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QEventLoop>

#include <ONCommonProtocol/onpacket.h>
#include <ONCommon/protocolfactory.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

using Common::ONPacket;

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(const Common::ProtocolFactory &protocolFactory, int socketDescriptor,
                               QObject *parent = 0);
    virtual ~ConnectionHandler();

    void run();
    
signals:
    
public slots:

private slots:
    void dataAvailable();
    void packetReceived(const ONPacket &packet);
    void disconnected();

private:
    static const QString _logModule;

    QEventLoop _loop;
    const Common::ProtocolFactory &_protocolFactory;
    int _socketDescriptor;
    QTcpSocket _socket;
    Common::IProtocol *_protocol;

};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_SERVERCORE_CONNECTIONHANDLER_H
