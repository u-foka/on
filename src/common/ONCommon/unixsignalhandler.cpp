#include "unixsignalhandler.h"

#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>

#include "logger.h"
#include "exception.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

int UnixSignalHandler::_sigFd[2] = {-1, -1};

UnixSignalHandler::UnixSignalHandler(int signal, QObject *parent) :
    QObject(parent), _logModule("UnixSignalHandler"), _signal(signal)
{
    LOG(Trace, _logModule, "Creating");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, _sigFd)) {
        throw Exception("Couldn't create socketpair");
    }

    _sn = new QSocketNotifier(_sigFd[1], QSocketNotifier::Read, this);
    connect(_sn, SIGNAL(activated(int)), this, SLOT(HandleSignal()));

    struct sigaction sig;
    sig.sa_handler = SignalHandler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags |= SA_RESTART;

    LOG(Debug, _logModule, QString("Setting up handler: %1").arg(strsignal(signal)));
    if (sigaction(signal, &sig, 0) > 0)
        throw Exception("Failed to install handler");

    LOG(Trace, _logModule, "Created");
}

UnixSignalHandler::~UnixSignalHandler()
{
    LOG(Trace, _logModule, "Destroying");
    delete _sn;
    LOG(Trace, _logModule, "Destroyed");
}

 void UnixSignalHandler::SignalHandler(int)
{
    char a = 1;
    ::write(_sigFd[0], &a, sizeof(a));
}

void UnixSignalHandler::HandleSignal()
{
    _sn->setEnabled(false);
    char tmp;
    ::read(_sigFd[1], &tmp, sizeof(tmp));

    LOG(Trace, _logModule, QString("Cought signal: %1").arg(strsignal(_signal)));
    emit CoughtSignal();

    _sn->setEnabled(true);
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
