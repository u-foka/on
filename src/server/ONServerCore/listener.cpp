#include "listener.h"

#include <ONCommon/log.h>
#include <ONCommonProtocol/onbinaryprotocol.h>

#include "connectionhandler.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

const QString Listener::_logModule("Listener");

Listener::Listener(QObject *parent) :
    QTcpServer(parent), _protocolFactory(this), _pool()
{
    _TRACE(_logModule, "Creating");

    _protocolFactory.RegisterProtocol(new Common::ONBinaryProtocol(&_protocolFactory));

    _TRACE(_logModule, "Created");
}

Listener::~Listener()
{
    _TRACE(_logModule, "Destroying");

    _INFO(_logModule, "Waiting for all connections to shut down...");
    _pool.waitForDone();

    _TRACE(_logModule, "Destroyed");
}

bool Listener::listen(const QHostAddress &address, quint16 port)
{
    _INFOS(_logModule, "Started listening on " << address.toString() << ":" << port);
    return QTcpServer::listen(address, port);
}

bool Listener::listen(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

void Listener::incomingConnection(qintptr handle)
{
    QRunnable *thread = new ConnectionThread<ConnectionHandler>(_protocolFactory, handle);
    _pool.start(thread);
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
