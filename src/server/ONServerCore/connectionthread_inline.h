#include "connectionthread.h"

#include <QThread>

#include <ONCommon/exception.h>
#include <ONCommon/log.h>

#include <ONCommonProtocol/ionprotocol.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

using Common::Exception;

template<typename Handler>
const QString ConnectionThread<Handler>::_logModule("ConnectionThread");

template<typename Handler>
ConnectionThread<Handler>::ConnectionThread(const Common::ProtocolFactory &protocolFactory, int socketDescriptor)
    : _protocolFactory(protocolFactory), _socketDescriptor(socketDescriptor)
{
    LOG(Trace, _logModule, "Created");
}

template<typename Handler>
ConnectionThread<Handler>::~ConnectionThread()
{
    LOG(Trace, _logModule, "Destroyed");
}

template<typename Handler>
void ConnectionThread<Handler>::run()
{
    LOG(Trace, _logModule, "Running");

    Handler handler(_protocolFactory, _socketDescriptor);
    handler.run();

    LOG(Trace, _logModule, "Finished");
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
