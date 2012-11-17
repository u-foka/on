#include "protocolfactory.h"

#include <iostream>

#include "logger.h"
#include "protocol.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

QSharedPointer<ProtocolFactory> ProtocolFactory::_instance;

const QSharedPointer<ProtocolFactory> &ProtocolFactory::Instance()
{
    if (_instance.isNull()) {
        _instance = QSharedPointer<ProtocolFactory>(new ProtocolFactory);
    }

    return _instance;
}

ProtocolFactory::ProtocolFactory()
    : _logger(Logger::Instance()), _logModule("ProtocolFactory")
{
    LOG(Trace, _logModule, "Created");
}

ProtocolFactory::~ProtocolFactory()
{
    // Use the stored logger since the global instance may be already destructed
    _logger->_LOG(Trace, _logModule, "Destroyed");
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
