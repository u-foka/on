#ifndef COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
#define COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H

#include <QObject>
#include <QSharedPointer>
#include <QIODevice>
#include <QByteArray>
#include <QVector>
#include <QReadWriteLock>

#include "iprotocol.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class ProtocolFactory : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolFactory(QObject *parent = 0);
    virtual ~ProtocolFactory();

    IProtocol * CreateProtocol(QIODevice &device, QObject *parent = 0) const;
    void RegisterProtocol(IProtocol *proto);

protected:
    void sortProtocols() const;
    static bool protocolCmp(IProtocol *a, IProtocol *b);

private:
    static const QString _logModule;

    mutable QReadWriteLock _lock;
    mutable QVector<IProtocol*> _registredProtocols;
    mutable bool _protocolsSorted;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
