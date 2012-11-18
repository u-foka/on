#ifndef COM_IWSTUDIO_ON_COMMON_UNIXSIGNALHANDLER_H
#define COM_IWSTUDIO_ON_COMMON_UNIXSIGNALHANDLER_H

#include <QObject>
#include <QSocketNotifier>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class UnixSignalHandler : public QObject
{
Q_OBJECT

public:
    UnixSignalHandler(int signal, QObject *parent = 0);
    ~UnixSignalHandler();

    static void SignalHandler(int unused);

public slots:
    void HandleSignal();

signals:
    void CoughtSignal();

private:
    static int _sigFd[2];

    const QString _logModule;

    QSocketNotifier *_sn;
    int _signal;

 };

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_UNIXSIGNALHANDLER_H
