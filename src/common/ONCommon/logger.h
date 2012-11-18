#ifndef COM_IWSTUDIO_ON_COMMON_LOGGER_H
#define COM_IWSTUDIO_ON_COMMON_LOGGER_H

#include <QTextStream>
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include <QString>
#include <QMutex>
#include <QFile>

#define LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Instance()-> \
        _LOG(_LEVEL_, _MODULE_, _MESSAGE_)
#define _LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Log(Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
        _MODULE_, _MESSAGE_, QString(__PRETTY_FUNCTION__).append(" @ ") \
            .append(QString(__FILE__).replace(ON_SRC_ROOT, "")).append(":%1").arg(__LINE__))

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

/**
 * @brief Logger class that writes multiple outputs
 */
class Logger
{
public:
    /**
     * @brief Available log levels
     */
    enum class Level {
        Fatal,
        Error,
        Warning,
        Info,
        Trace
    };
    const QMap<Level, QString> LevelNames;

    /**
     * @brief Available file output formats
     */
    enum class Format {
        Plain,
        Csv,
        Xml,
        Html
    };

    /**
     * @brief Returns the instance constructed on demand
     * @return Instance in a QSharedPointer
     */
    static const QSharedPointer<Logger> &Instance();
    virtual ~Logger();

    bool GetLogToStdout() const { return _logToStdout; }
    void SetLogToStdout(bool enabled) { _logToStdout = enabled; }
    bool GetLogLocationToStdout() const { return _logLocationToStdout; }
    void SetLogLocationToStdout(bool enabled) { _logLocationToStdout = enabled; }
    Level GetStdoutLogLevel() const { return _stdoutLevel; }
    void SetStdoutLogLevel(Level level) { _stdoutLevel = level; }

    QString GetLogFile() const { return _file.fileName(); }
    void SetLogFile(const QString &fileName);
    bool GetLogLocationToFile() const { return _logLocationToFile; }
    void SetLogLocationToFile(bool enabled) { _logLocationToFile = enabled; }
    Level GetFileLogLevel() const { return _fileLevel; }
    void SetFileLogLevel(Level level) { _fileLevel = level; }

    Format GetLogFormat() const { return _format; }
    void SetLogFormat(Format format);

    /**
     * @brief Writes out the startup buffer and starts immediate logging
     *
     * Logger is constructed with all outputs disabled, and buffers the messages
     * on startup into an internal buffer. After the outputs initialized,
     * this function should be called to write out the messages from the
     * startup buffer and starts immediate logging.
     */
    void FlushStartupBuffer();

    /**
     * @brief Writes out a line to log
     * @param level Log level of the message
     * @param module Module identifier of the message
     * @param message Log message
     * @param location The function name, source file and line where the log was called
     */
    void Log(Level level, const QString &module, const QString &message, const QString &location = "");

protected:
    struct LogLine {
        Level level;
        QString module;
        QString message;
        QString location;
    };

    Logger();
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;

    bool _logToStdout;
    bool _logLocationToStdout;
    Level _stdoutLevel;
    QFile _file;
    bool _logLocationToFile;
    Level _fileLevel;
    Format _format;

private:
    static QSharedPointer<Logger> _instance;

    static QMap<Level, QString> initLevelNames();

    const QString _logModule;

    QMutex _mutex;
    bool _startupCompleted;
    QVector<LogLine> _startupBuffer;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_LOGGER_H
