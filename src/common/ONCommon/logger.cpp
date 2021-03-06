#include "logger.h"
#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#include <QMutexLocker>
#include <QTextStream>

#include "exception.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

QSharedPointer<Logger> Logger::_instance;
QMutex Logger::_instanceMutex;

const QSharedPointer<Logger> & Logger::Instance()
{
    if (_instance.isNull()) {
        QMutexLocker locker(&_instanceMutex);
        if (_instance.isNull()) {
            _instance = QSharedPointer<Logger>(new Logger);
        }
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
    out[Level::Debug] = "Debug";
    out[Level::Trace] = "Trace";

    return out;
}

Logger::Logger()
    : LevelNames(initLevelNames()), _logToStdout(false), _logLocationToStdout(false), _stdoutLevel(Level::Info),
      _logLocationToFile(true), _fileLevel(Level::Trace), _format(Format::Plain), _logModule("Logger"),
      _mutex(QMutex::Recursive), _startupCompleted(false)
{
#ifdef DEBUG
    _LOG(Trace, _logModule, "Created");
#endif
}

Logger::~Logger()
{
#ifdef DEBUG
    _LOG(Trace, _logModule, "Destroyed");
#endif
}

bool Logger::SetLogFile(const QString &fileName)
{
    if (_file.isOpen()) {
        throw Exception("Log file already open");
    }

    _file.setFileName(fileName);
    bool success = _file.open(QIODevice::WriteOnly | QIODevice::Append);

    if (! success) {
        _LOGS(_instance, Warning, _logModule, "Failed to open log file: " << _file.errorString()
              << " (filename: " << _file.fileName() << ")");
    }

    return success;
}

void Logger::SetLogFormat(Format format)
{
    if (_file.isOpen()) {
        throw Exception("Log file already open");
    }

    _format = format;
}

void Logger::FlushStartupBuffer()
{
    QMutexLocker locker(&_mutex);

    if (_startupCompleted) {
        return;
    }

    _startupCompleted = true;

    for (auto i = _startupBuffer.begin(); i != _startupBuffer.end(); i++) {
        Log(i->level, i->module, i->message, i->location);
    }
}

void Logger::Log(Level level, const QString &module, const QString &message, const QString &location)
{
    QMutexLocker locker(&_mutex);

    if (! _startupCompleted) {
        _startupBuffer.append({
                .level = level,
                .module = module,
                .message = message,
                .location = location
            });

        return;
    }

    // date and time to display in log
    time_t now = time(0);
    tm    *ltm = localtime(&now);
    char  dateline[20];
    strftime(dateline,20,"%Y/%m/%d %H:%M:%S",ltm);
    QString datestring = QString::fromLocal8Bit(dateline);

    emit BeforeLogLine();

    if (_logToStdout && _stdoutLevel >= level) {
        using namespace std;

        cout <<
            setw(23) << left << datestring.toUtf8().constData() <<
            setw(10) << left << LevelNames[level].toUtf8().constData() <<
            setw(20) << left << module.toUtf8().constData() <<
            message.toUtf8().constData();
        if (! location.isEmpty() && _logLocationToStdout) {
            cout << " // " << location.toUtf8().constData();
        }
        cout << endl;
    }

    if (_file.isOpen() && _fileLevel >= level) {
        std::stringstream line;

        switch (_format) {
        case Format::Plain:
            using namespace std;

            line <<
                setw(23) << left << datestring.toUtf8().constData() <<
                setw(10) << left << LevelNames[level].toUtf8().constData() <<
                setw(20) << left << module.toUtf8().constData() <<
                message.toUtf8().constData();
            if (! location.isEmpty() && _logLocationToFile) {
                line << " // " << location.toUtf8().constData();
            }
            line << endl;

            break;
        case Format::Csv:
            using namespace std;

            line <<
                "\"" << datestring.toUtf8().constData() << "\"," <<
                "\"" << LevelNames[level].toUtf8().constData() << "\"," <<
                "\"" << module.toUtf8().constData() << "\"," <<
                "\"" << message.toUtf8().constData() << "\"";
            if (! location.isEmpty() && _logLocationToFile) {
                line << ",\"" << location.toUtf8().constData() << "\"";
            }
            line << endl;

            break;
        default:
            throw Exception("Invalid log format");

            break;
        }

        std::string lineStr = line.str();
        _file.write(lineStr.data(), lineStr.length());
        _file.flush();
    }

    emit AfterLogLine();
}

Logger::Stream::Stream(const QSharedPointer<Logger> &logger, Level level, const QString &module,
                       const QString &location)
    : _logger(logger), _level(level), _module(module), _location(location), _line(),
      _lineStream(&_line, QIODevice::WriteOnly)
{
}

Logger::Stream::~Stream()
{
    _lineStream.flush();
    _logger->Log(_level, _module, _line, _location);
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
