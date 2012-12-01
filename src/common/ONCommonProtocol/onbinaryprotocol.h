#ifndef COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H

#include "ionprotocol.h"

#include <QByteArray>

class QIODevice;

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class ONBinaryProtocol : public IONProtocol
{
    Q_OBJECT
public:
    explicit ONBinaryProtocol(QObject *parent = 0);

    virtual int HandshakeSize() const override;
    virtual IProtocol * ConstructIfSuitable(const QByteArray &data, QObject *parent = 0) const override;

    virtual void Attach(QIODevice *device) override;
    virtual void Detach() override;

    struct BinaryPacketHeader
    {
        uint32_t Message;
        uint32_t MessageLength; ///< @brief Length of the message EXCLUDING the header
    };

    struct BinaryArgumentHeader
    {
        uint32_t Argument;
        uint32_t ArgumentLength; ///< @brief Length of the argument EXCLUDING the header
    };
    
signals:

public slots:
    
private slots:
    void dataAvailable();

private:

    static const int MajorVersion;

    QIODevice *_device;
    QByteArray _buffer;
    ONPacket _currentPacket;

    void parseBuffer();
    
};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H
