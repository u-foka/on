#include "logger.h"

#include <iostream>

#include <QMutexLocker>
#include <QTextStream>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

QSharedPointer<Logger> Logger::_instance;

const QSharedPointer<Logger> & Logger::Instance()
{
    if (_instance.isNull()) {
        _instance = QSharedPointer<Logger>(new Logger);
    }

    return _instance;
}

QMap<Logger::Level, QString> Logger::initLevelNames()
{
    QMap<Level, QString> out;

    out[Level::Fatal] = "Fatal";
    out[Level::Error] = "Error";
    out[Level::Warning] = "Warning";
    out[Level::Info] = "Info";
    out[Level::Trace] = "Trace";

    return out;
}

Logger::Logger()
    : LevelNames(initLevelNames()), _logModule("Logger")
{
    _LOG(Trace, _logModule, "Created");
}

Logger::~Logger()
{
    _LOG(Trace, _logModule, "Destroyed");
}

void Logger::Log(Level level, QString module, QString message, QString location)
{
    QMutexLocker locker(&_mutex);

    std::cout << LevelNames[level].toUtf8().constData() << " " <<
                 module.toUtf8().constData() << " " <<
                 message.toUtf8().constData();
    if (! location.isEmpty()) {
        std::cout << " // " << location.toUtf8().constData();
    }
    std::cout << std::endl;
    std::cout.flush();
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
