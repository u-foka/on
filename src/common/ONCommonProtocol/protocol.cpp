#include "protocol.h"

#include <cstdlib>
#include <cstring>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {
namespace Protocol {

const char Magic[2] = {'O', 'N'};

const char *TextMessage[] = {
    "Invalid",
// Available from 1.000
    "AvailableSecurityModes",
    "SelectSecurityMode",
    "Authenticate"
};

const char *TextMessageArgument[] {
    "Invalid",
// Available from 1.000
    "SecurityMode"
};

bool Handshake::IsValid() const
{
    if (! (memcmp(Magic, Protocol::Magic, sizeof(Protocol::Magic)) == 0)) return false;
    if (! (Space == ' ')) return false;
    if (! (Dot == '.')) return false;
    if (! (Newline == '\n')) return false;
    if (! (GetMajorVersion() >= 0)) return false;
    if (! (GetMinorVersion() >= 0)) return false;
    return true;

    return
            memcmp(Magic, Protocol::Magic, sizeof(Protocol::Magic)) == 0
            && Space == ' '
            && Dot == '.'
            && Newline == '\n'
            && GetMajorVersion() >= 0
            && GetMinorVersion() >= 0;
}

int Handshake::GetMajorVersion() const
{
    char *pos = const_cast<char*>(MajorVersion);
    int value = strtol(MajorVersion, &pos, 10);
    if (pos != MajorVersion + 3) return -1;
    return value;
}

int Handshake::GetMinorVersion() const
{
    char *pos = const_cast<char*>(MinorVersion);
    int value = strtol(MinorVersion, &pos, 10);
    if (pos != MinorVersion + 3) return -1;
    return value;
}

} // namespace Protocol
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
