#ifndef COM_IWSTUDIO_ON_COMMON_ONPACKET_H
#define COM_IWSTUDIO_ON_COMMON_ONPACKET_H

#include <QMultiMap>

#include "protocol.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

struct ONPacket {
    Protocol::Message Message;
    QMultiMap<Protocol::MessageArgument, QByteArray> Arguments;

};

bool operator ==(const ONPacket &a, const ONPacket &b);

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_ONPACKET_H
