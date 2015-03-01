#ifndef COM_IWSTUDIO_ON_SERVERCORE_READLINE_H
#define COM_IWSTUDIO_ON_SERVERCORE_READLINE_H

#include <QObject>
#include <QMutex>
#include <QSocketNotifier>

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

class Readline : public QObject
{
    Q_OBJECT
public:
    explicit Readline(QString prompt = "", QObject *parent = 0);
    virtual ~Readline();

    bool isEnabled();

    QString getPrompt();
    void setPrompt(QString prompt);
    
signals:
    void LineRead(QString line);
    void EndSignal();
    
public slots:
    void Disable();
    void Enable();

private slots:
    void socketActivated(int socket);

private:
    static Readline *_instance;
    static QMutex _instanceGuard;
#if HAVE_READLINE == 1
    static void sLineCallback(char *line);
#endif // HAVE_READLINE == 1

    QSocketNotifier _notifier;
    bool _enabled;
    QMutex _enabledGuard;
    QString _prompt;

#if HAVE_READLINE == 1
    char* _savedLine;
    int _savedPoint;

    void lineCallback(char *line);
#endif // HAVE_READLINE == 1

};

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_SERVERCORE_READLINE_H
