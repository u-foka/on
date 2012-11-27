#ifndef COM_IWSTUDIO_ON_COMMON_PROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_PROTOCOL_H

#include <cstdint>
#include <QObject>
#include <QIODevice>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {
namespace Protocol {

extern const char Magic[2];

enum class Type : char {
    Text = 'T',
    Binary = 'B'
};

struct Handshake {
    char Magic[2];       // "ON"
    char ProtocolType;   //
    char Space;          // ' '
    char MajorVersion[3];//
    char Dot;            // '.'
    char MinorVersion[3];//
    char Newline;        // '\n'

    bool IsValid() const;
    int GetMajorVersion() const;
    int GetMinorVersion() const;
};

enum class Message : uint32_t {
    Invalid = 0,
// Available from 1.000
    AvailableSecurityModes,
    SelectSecurityMode,
    Authenticate

};

extern const char* TextMessage[];

} // namespace Protocol
} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_PROTOCOL_H
