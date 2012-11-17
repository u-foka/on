#ifndef COM_IWSTUDIO_ON_COMMON_LOGGER_H
#define COM_IWSTUDIO_ON_COMMON_LOGGER_H

#include <QTextStream>
#include <QSharedPointer>
#include <QMap>
#include <QString>
#include <QMutex>

#define LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Instance()-> \
        Log(Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
            _MODULE_, _MESSAGE_, QString(__PRETTY_FUNCTION__).append(" @ ") \
                .append(QString(__FILE__).replace(ON_SRC_ROOT, "")).append(":%1").arg(__LINE__))

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class Logger
{
public:
    enum class Level {
        Fatal,
        Error,
        Warning,
        Info,
        Trace
    };
    static const QMap<Level, QString> LevelNames;

    static QSharedPointer<Logger> & Instance();
    virtual ~Logger();

    void Log(Level level, QString module, QString message, QString location = "");

protected:
    Logger();
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;

private:
    static QSharedPointer<Logger> _instance;
    static QMap<Level, QString> initLevelNames();

    QMutex _mutex;
    QTextStream cout;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_LOGGER_H
