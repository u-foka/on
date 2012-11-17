#include "protocolfactory.h"

#include <iostream>

#include "logger.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

QSharedPointer<ProtocolFactory> ProtocolFactory::_instance;
const QString ProtocolFactory::_logModule = "ProtocolFactory";

QSharedPointer<ProtocolFactory> & ProtocolFactory::Instance()
{
    if (_instance.isNull()) {
        _instance = QSharedPointer<ProtocolFactory>(new ProtocolFactory);
    }

    return _instance;
}

ProtocolFactory::ProtocolFactory()
{
    LOG(Trace, _logModule, "Created");
}

ProtocolFactory::~ProtocolFactory()
{
    LOG(Trace, _logModule, "Destroyed");
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
