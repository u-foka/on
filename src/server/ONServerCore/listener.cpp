#include "listener.h"

#include <QThreadPool>

#include <ONCommon/log.h>
#include <ONCommonProtocol/onbinaryprotocol.h>

#include "connectionhandler.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

const QString Listener::_logModule("Listener");

Listener::Listener(QObject *parent) :
    QTcpServer(parent), _protocolFactory(this)
{
    LOG(Trace, _logModule, "Creating");

    _protocolFactory.RegisterProtocol(new Common::ONBinaryProtocol(&_protocolFactory));

    LOG(Trace, _logModule, "Created");
}

Listener::~Listener()
{
    LOG(Trace, _logModule, "Destroyed");
}

bool Listener::listen(const QHostAddress &address, quint16 port)
{
    LOGS(Info, _logModule, "Started listening on " << address.toString() << ":" << port);
    QTcpServer::listen(address, port);
}

bool Listener::listen(quint16 port)
{
    listen(QHostAddress::Any, port);
}

void Listener::incomingConnection(int handle)
{
    QRunnable *thread = new ConnectionThread<ConnectionHandler>(_protocolFactory, handle);
    QThreadPool::globalInstance()->start(thread);
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
