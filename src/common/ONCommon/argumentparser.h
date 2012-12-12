#ifndef COM_IWSTUDIO_ON_COMMON_ARGUMENTPARSER_H
#define COM_IWSTUDIO_ON_COMMON_ARGUMENTPARSER_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QMap>
#include <QVariantMap>

namespace Com {
namespace IWstudio {
namespace ON {
namespace Common {

class ArgumentParser
{
public:
    typedef QMap<QString, QVariant::Type> ArgumentsMap;

    ArgumentParser(const ArgumentsMap &availableArguments, const QStringList &programArguments);
    virtual ~ArgumentParser();

private:
    QVariantMap _arguments;

};

} // namespace Common
} // namespace ON
} // namespace IWstudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_ARGUMENTPARSER_H
