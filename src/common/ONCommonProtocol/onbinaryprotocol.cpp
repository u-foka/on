#include "onbinaryprotocol.h"

#include <ONCommon/exception.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

const int ONBinaryProtocol::MajorVersion = 1;

ONBinaryProtocol::ONBinaryProtocol(QObject *parent) :
    IONProtocol(parent), _device(0)
{}

int ONBinaryProtocol::HandshakeSize() const
{
    return sizeof(Protocol::Handshake);
}

IProtocol * ONBinaryProtocol::ConstructIfSuitable(const QByteArray data) const
{
    auto handshake = reinterpret_cast<const Protocol::Handshake *>(data.data());

    if (handshake->IsValid() && handshake->GetMajorVersion() == MajorVersion) {
        return new ONBinaryProtocol(parent());
    }

    return 0;
}

void ONBinaryProtocol::Attach(QIODevice *device)
{
    if (_device != nullptr) {
        throw Exception("Already attached");
    }

    if (device == nullptr) {
        throw Exception("Can't attach to a nullptr");
    }

    _device = device;
    connect(_device, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
}

void ONBinaryProtocol::Detach()
{
    disconnect(this, SLOT(dataAvailable()));

    _device = nullptr;
}

void ONBinaryProtocol::dataAvailable()
{

}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
