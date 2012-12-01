#include "onpacket.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

bool operator ==(const ONPacket &a, const ONPacket &b)
{
    return
            a.Message == b.Message
            && a.Arguments == b.Arguments;
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
