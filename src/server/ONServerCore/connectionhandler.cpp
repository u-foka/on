#include "connectionhandler.h"

#include <QEventLoop>

#include <ONCommon/log.h>
#include <ONCommon/exception.h>
#include <ONCommonProtocol/ionprotocol.h>

#include "application.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

using Common::Exception;

const QString ConnectionHandler::_logModule("ConnectionHandler");

ConnectionHandler::ConnectionHandler(const Common::ProtocolFactory &protocolFactory, int socketDescriptor,
                                     QObject *parent)
    : QObject(parent), _protocolFactory(protocolFactory), _socketDescriptor(socketDescriptor)
{
    LOG(Trace, _logModule, "Creating");

    _loop.connect(Application::instance(), SIGNAL(aboutToQuit()), SLOT(quit()));

    LOG(Trace, _logModule, "Created");
}

ConnectionHandler::~ConnectionHandler()
{
    LOG(Trace, _logModule, "Destroyed");
}

void ConnectionHandler::run()
{
    LOG(Trace, _logModule, "Running");

    if (! _socket.setSocketDescriptor(_socketDescriptor)) {
        throw Exception("Invalid socket");
    }

    connect(&_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(dataAvailable()));

    LOG(Trace, _logModule, "Entering event loop");
    _loop.exec();
    LOG(Trace, _logModule, "Leaving event loop");

    if (_socket.state() != QAbstractSocket::UnconnectedState) {
        LOG(Trace, _logModule, "Closing socket");
        _socket.disconnectFromHost();
        if (_socket.state() != QAbstractSocket::UnconnectedState) {
            _socket.waitForDisconnected();
        }
    }

    LOG(Trace, _logModule, "Finished");
}

void ConnectionHandler::dataAvailable()
{
    try {
        _protocol = _protocolFactory.CreateProtocol(_socket, this);
    } catch(Exception &e) {
        LOG(Info, _logModule, "Client connected with unknown protocol.");
        _loop.exit(1);
        return;
    }

    if (_protocol != nullptr) {
        disconnect(this, SLOT(dataAvailable()));

        if (Common::IONProtocol *protocol = dynamic_cast<Common::IONProtocol*>(_protocol)) {
            connect(protocol, SIGNAL(PacketReceived(ONPacket)), this, SLOT(packetReceived(ONPacket)));
        } else {
            LOG(Error, _logModule, "The selected protocol is currently unsupported.");
            delete _protocol;
            _protocol = 0;
            _loop.exit(1);
            return;
        }

        LOG(Debug, _logModule, "Protocol selected successfully, attaching...");
        _protocol->Attach(&_socket);
    }
}

void ConnectionHandler::packetReceived(const ONPacket &packet)
{
    LOG(Debug, _logModule, "Packet received!");
}

void ConnectionHandler::disconnected()
{
    _loop.quit();
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
