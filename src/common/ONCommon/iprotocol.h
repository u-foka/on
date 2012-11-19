#ifndef COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H

#include <QObject>

class QByteArray;
class QIODevice;

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class IProtocol : public QObject
{
    Q_OBJECT
public:
    IProtocol(QObject *parent = 0) : QObject(parent) {}
    virtual ~IProtocol(){}

    /**
     * @brief Returns the minimum number of bytes needed to decide if we
     *        want to parse this protocol.
     * @return Required bytes.
     */
    virtual int HandshakeSize() = 0;
    /**
     * @brief Checks if the given data is a valid handshake of the protocol.
     * @param data QByteArray of at least HandshakeSize() bytes.
     * @return A new configured instance of this protocol for this handshake if it
     *         matches or nullptr if not.
     */
    virtual IProtocol * CheckHandshake(QByteArray data) = 0;

    virtual void Attach(QIODevice &device) = 0;
    virtual void Detach() = 0;

public slots:
    virtual void DataAvailable() = 0;
    virtual void DataSent() = 0;

signals:
    void PacketReceived();
    void PacketSent();

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_IPROTOCOL_H
