#include "onbinaryprotocol.h"

#include <arpa/inet.h>

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

IProtocol * ONBinaryProtocol::ConstructIfSuitable(const QByteArray &data, QObject *parent) const
{
    auto handshake = reinterpret_cast<const Protocol::Handshake *>(data.data());

    if (handshake->IsValid() && handshake->GetMajorVersion() == MajorVersion
            && handshake->ProtocolType == Protocol::Type::Binary) {
        return new ONBinaryProtocol(parent);
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

    _buffer.append(_device->readAll());
    parseBuffer();
}

void ONBinaryProtocol::Detach(bool keepBuffer)
{
    disconnect(this, SLOT(dataAvailable()));

    _device = nullptr;

    if (! keepBuffer) {
        _buffer.clear();
    }
}

void ONBinaryProtocol::dataAvailable()
{
    _buffer.append(_device->readAll());
}

void ONBinaryProtocol::parseBuffer()
{
    const char *data = _buffer.constData();
    const char *bufferEnd = data + _buffer.length();

    do {
        auto header = reinterpret_cast<const BinaryPacketHeader *>(data);
        if (data + ntohl(header->MessageLength) > bufferEnd) {
            break;
        }
        // Increment data after break, since if we havent have enough data, we will need the header next time.
        data += sizeof(BinaryPacketHeader);

        _currentPacket.Message = static_cast<Protocol::Message>(ntohl(header->Message));
        _currentPacket.Arguments.clear();

        const char *dataEnd = data + ntohl(header->MessageLength);
        while (dataEnd > data) {
            if (data + sizeof(BinaryArgumentHeader) > dataEnd) {
                throw Exception("Message argument header is missing");
            }

            auto argHeader = reinterpret_cast<const BinaryArgumentHeader *>(data);
            data += sizeof(BinaryArgumentHeader);

            if (data + ntohl(argHeader->ArgumentLength) > dataEnd) {
                throw Exception("Message argument is too long");
            }

            _currentPacket.Arguments.insert(
                    static_cast<Protocol::MessageArgument>(ntohl(argHeader->Argument)),
                    QByteArray(data, ntohl(argHeader->ArgumentLength))
                );
            data += ntohl(argHeader->ArgumentLength);
        }

        emit PacketReceived(_currentPacket);
    } while (data < bufferEnd);

    _buffer.remove(0, data - _buffer.constData());
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
