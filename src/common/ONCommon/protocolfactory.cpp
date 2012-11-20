#include "protocolfactory.h"

#include <iostream>

#include "log.h"
#include "protocol.h"
#include "exception.h"
#include "quicksort.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

ProtocolFactory::ProtocolFactory()
    : _logModule("ProtocolFactory"), _protocolsSorted(true)
{
    LOG(Trace, _logModule, "Created");
}

ProtocolFactory::~ProtocolFactory()
{
    LOG(Trace, _logModule, "Destroyed");
}

IProtocol * ProtocolFactory::CreateProtocol(QIODevice &device)
{
    if (!_protocolsSorted) {
        sortProtocols();
    }

    QByteArray handshakeBuffer;

    for (auto i = _registredProtocols.begin(); i != _registredProtocols.end(); i++) {
        if (handshakeBuffer.length() < (*i)->HandshakeSize()) {
            int requiredSize = (*i)->HandshakeSize() - handshakeBuffer.length();
            QByteArray readBuffer = device.read(requiredSize);
            if (readBuffer.length() < requiredSize) {
                // Revert the read and return nullptr
                for (auto data = readBuffer.data() + (readBuffer.length() - 1); data > readBuffer.data(); data--) {
                    device.ungetChar(*data);
                }

                return nullptr;
            }

            handshakeBuffer.append(readBuffer);
        }

        IProtocol *out = (*i)->CheckHandshake(handshakeBuffer);
        if (out) {
            return out;
        }
    }

    throw Exception("Found no protocol that matches the read data.");

}

void ProtocolFactory::RegisterProtocol(IProtocol *proto)
{
    _registredProtocols.append(proto);
    _protocolsSorted = false;
}

void ProtocolFactory::sortProtocols()
{
    Algorithm::QuickSort(_registredProtocols, &protocolCmp);
    _protocolsSorted = true;
}

bool ProtocolFactory::protocolCmp(IProtocol *a, IProtocol *b)
{
    return a->HandshakeSize() < b->HandshakeSize();
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
