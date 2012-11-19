#include "protocolfactory.h"

#include <iostream>

#include "log.h"
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

IProtocol * ProtocolFactory::CreateProtocol(QIODevice &device)
{

}

void ProtocolFactory::RegisterProtocol(IProtocol *proto)
{
    _registredProtocols.append(proto);
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
