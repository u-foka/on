#ifndef COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H

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

} // namespace Protocol
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
