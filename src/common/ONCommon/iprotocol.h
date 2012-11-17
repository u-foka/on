#ifndef COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H

#include <QObject>
#include <QIODevice>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class IProtocol : public QObject
{
public:
    Q_OBJECT

    virtual void Attach(QIODevice &device) = 0;
    virtual void Detach() = 0;

signals:
    void PacketReceived();
    void PacketSent();

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H