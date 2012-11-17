#ifndef COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
#define COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H

#include <QSharedPointer>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class Logger;
class ProtocolFactory
{
public:
    const static QSharedPointer<ProtocolFactory> & Instance();
    virtual ~ProtocolFactory();

protected:
    ProtocolFactory();
    ProtocolFactory(ProtocolFactory const&) = delete;
    ProtocolFactory& operator=(ProtocolFactory const&) = delete;

private:
    static QSharedPointer<ProtocolFactory> _instance;


    const QString _logModule;
    const QSharedPointer<Logger> _logger;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_PROTOCOLFACTORY_H
