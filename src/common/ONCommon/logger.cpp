#include "logger.h"

#include <iostream>

#include <QMutexLocker>
#include <QTextStream>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

QSharedPointer<Logger> Logger::_instance;
QMap<Logger::Level, QString> const Logger::LevelNames = initLevelNames();


QSharedPointer<Logger> & Logger::Instance()
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
    : cout(stdout, QIODevice::WriteOnly)
{

}

Logger::~Logger()
{

}

void Logger::Log(Level level, QString module, QString message, QString location)
{
    QMutexLocker locker(&_mutex);

    cout << LevelNames[level] << " " << module << " " << message << " // " << location << endl << flush;

}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
