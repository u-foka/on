#ifndef COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H

#include <QObject>
#include <QMap>

#include <ONCommon/iprotocol.h>

#include "protocol.h"

class QByteArray;
class QIODevice;

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

struct ONPacket {
    Protocol::Message Message;
    QMap<QString, QByteArray> Arguments;

};

class IONProtocol : public IProtocol
{
    Q_OBJECT
public:
    IONProtocol(QObject *parent = 0) : IProtocol(parent) {}
    virtual ~IONProtocol(){}

signals:
    void PacketReceived(ONPacket packet);
    void PacketSent();

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IONPROTOCOL_H
