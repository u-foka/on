#include "protocolfactory.h"

#include <iostream>

#include "logger.h"
#include "protocol.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

ProtocolFactory::ProtocolFactory()
    : _logModule("ProtocolFactory")
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
