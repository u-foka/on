#ifndef COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H

#include <QObject>

#include <ONCommon/iprotocol.h>

#include "protocol.h"
#include "onpacket.h"

class QByteArray;
class QIODevice;

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class IONProtocol : public IProtocol
{
    Q_OBJECT
public:
    IONProtocol(QObject *parent = 0) : IProtocol(parent) {}
    virtual ~IONProtocol(){}

signals:
    void PacketReceived(const ONPacket &packet);
    void PacketSent();

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H
