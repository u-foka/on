#ifndef COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H
#define COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H

#include "ionprotocol.h"

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
    virtual IProtocol * ConstructIfSuitable(const QByteArray data) const override;

    virtual void Attach(QIODevice *device) override;
    virtual void Detach() override;
    
signals:

public slots:
    
private slots:
    void dataAvailable();

private:
    static const int MajorVersion;

    QIODevice *_device;
    
};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_ONBINARYPROTOCOL_H
