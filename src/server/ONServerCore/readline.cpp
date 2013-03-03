#include "readline.h"

#include <config.h>

#include <iostream>
#if HAVE_READLINE == 1
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include <ONCommon/exception.h>

#define FDSTDIN 0

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

using Common::Exception;

Readline *Readline::_instance = nullptr;
QMutex Readline::_instanceGuard;

Readline::Readline(QString prompt, QObject *parent)
    : QObject(parent), _notifier(FDSTDIN, QSocketNotifier::Read), _enabled(true), _enabledGuard(), _prompt(prompt),
      _savedLine(0), _savedPoint(0)
{
    QMutexLocker lockInstance(&_instanceGuard);

    if (_instance != nullptr) {
        throw Exception("Only one instance of Readline is allowed");
    }
    _instance = this;

    rl_callback_handler_install("on> ", &sLineCallback);
    connect(&_notifier, SIGNAL(activated(int)), SLOT(socketActivated(int)));
}

Readline::~Readline()
{
    QMutexLocker lockEnabled(&_enabledGuard);
    _notifier.setEnabled(false);
    _enabled = false;

    rl_callback_handler_remove();
}

bool Readline::isEnabled()
{
    QMutexLocker lock(&_enabledGuard);

    return _enabled;
}

QString Readline::getPrompt()
{
    return _prompt;
}

void Readline::setPrompt(QString prompt)
{
    _prompt = prompt;

    QMutexLocker lock(&_enabledGuard);

    if (_enabled) {
        rl_set_prompt(_prompt.toUtf8());
        rl_redisplay();
    }
}

void Readline::Enable()
{
    QMutexLocker lock(&_enabledGuard);

    if (_enabled) return;

    rl_set_prompt(_prompt.toUtf8());
    rl_replace_line(_savedLine, 0);
    rl_point = _savedPoint;
    rl_redisplay();

    _notifier.setEnabled(true);
    _enabled = true;
}

void Readline::Disable()
{
    QMutexLocker lock(&_enabledGuard);

    if (!_enabled) return;

    _notifier.setEnabled(false);

    _savedPoint = rl_point;
    _savedLine = rl_copy_text(0, rl_end);

    rl_set_prompt("");
    rl_replace_line("", 0);
    rl_redisplay();

    std::cout << '\r' << std::flush;
    _enabled = false;
}

void Readline::socketActivated(int socket)
{
    switch (socket) {
    case FDSTDIN:
            rl_callback_read_char();
            break;

    default:
        throw Exception("Invalid socket activation");
    }
}

void Readline::sLineCallback(char *line)
{
    QMutexLocker lock(&_instanceGuard);

    _instance->lineCallback(line);
}

void Readline::lineCallback(char *line)
{
    if (line == 0) {
        std::cout << std::endl;
        emit EndSignal();
        return;
    }

    if (strlen(line) > 0) {
        add_history(line);
        emit LineRead(line);
    }
    rl_free(line);
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com
