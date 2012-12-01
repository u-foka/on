#include "protocolfactory.h"

#include <iostream>

#include "log.h"
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

IProtocol * ProtocolFactory::CreateProtocol(QIODevice &device, QObject *parent)
{
    if (!_protocolsSorted) {
        sortProtocols();
    }

    QByteArray handshakeBuffer;

    for (auto i = _registredProtocols.begin(); i != _registredProtocols.end(); i++) {
        if (handshakeBuffer.length() < (*i)->HandshakeSize()) {
            int requiredSize = (*i)->HandshakeSize() - handshakeBuffer.length();
            QByteArray readBuffer = device.read(requiredSize);
            handshakeBuffer.append(readBuffer);

            if (readBuffer.length() < requiredSize) {
                // Revert the whole read and return nullptr
                auto buffer = handshakeBuffer.data();
                int len = handshakeBuffer.length();
                for (auto pos = buffer + (len-1); pos >= buffer; pos--) {
                    device.ungetChar(*pos);
                }

                return nullptr;
            }
        }

        IProtocol *out = (*i)->ConstructIfSuitable(handshakeBuffer, parent);
        if (out) {
            // Let the caller to attach te device, to give it time to setup
            // it's signal handlers before attach
            //out->Attach(&device);
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
