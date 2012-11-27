#include "protocol.h"

#include <cstdlib>
#include <cstring>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {
namespace Protocol {

const char Magic[2] = {'O', 'N'};

const char* TextMessage[] = {
    "Invalid",
// Available from 1.000
    "AvailableSecurityModes",
    "SelectSecurityMode",
    "Authenticate"
};

bool Handshake::IsValid() const
{
    return
            memcmp(Magic, Protocol::Magic, sizeof(Protocol::Magic))
            && GetMajorVersion() != 0
            && GetMinorVersion() != 0;
}

int Handshake::GetMajorVersion() const
{
    return strtol(MajorVersion, nullptr, 10);
}

int Handshake::GetMinorVersion() const
{
    return strtol(MinorVersion, nullptr, 10);
}

} // namespace Protocol
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
