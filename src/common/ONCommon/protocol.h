#ifndef COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H

#include <cstdint>
#include <QObject>
#include <QIODevice>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {
namespace Protocol {

const char[2] Magic = "ON";

enum class Type : char {
    Text = 'T',
    Binary = 'B'
};

struct Handshake {
    char[2] Magic,          // "ON"
    char    Type,           //
    char    Space,          // ' '
    char[3] MajorVersion,   //
    char    Dot,            // '.'
    char[3] MinorVersion,   //
    char    Newline         // '\n'
};

enum class Message : uint32_t {
    Invalid = -1,
// Available from 1.000
    AvailableSecurityModes = 0,
    SelectSecurityMode,
    Authenticate

};

const char** TextMessage = {
// Available from 1.000
    "AvailableSecurityModes",
    "SelectSecurityMode",
    "Authenticate"
}

} // namespace Protocol
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
