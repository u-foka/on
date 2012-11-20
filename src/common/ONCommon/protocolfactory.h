#ifndef COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
#define COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H

#include <QObject>
#include <QSharedPointer>
#include <QIODevice>
#include <QByteArray>
#include <QVector>

#include "iprotocol.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class ProtocolFactory : QObject
{
    Q_OBJECT
public:
    ProtocolFactory();
    virtual ~ProtocolFactory();

    IProtocol * CreateProtocol(QIODevice &device);
    void RegisterProtocol(IProtocol *proto);

protected:
    void sortProtocols();
    static bool protocolCmp(IProtocol *a, IProtocol *b);

private:
    const QString _logModule;

    QVector<IProtocol*> _registredProtocols;
    bool _protocolsSorted;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
