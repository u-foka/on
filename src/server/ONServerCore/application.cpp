#include "application.h"

#include <cstdlib>
#include <iostream>
#include <signal.h>

#include <QCoreApplication>

#include <ONCommon/log.h>
#include <ONCommonPosix/unixsignalhandler.h>
#include <ONCommonPosix/readline.h>

#include "listener.h"
#include "commandinterface.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace ServerCore {

const QString Application::_logModule = "Application";

Application::Application(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
}

Application::~Application()
{
}

int Application::run()
{
    std::cout << "***********************************************************" << std::endl <<
                 "* ON  Server  v" << MACRO_STR(DETECTED_ON_VERSION) <<
                            "    (built on " << MACRO_STR(BUILD_DATE) << ")" << std::endl <<
                 "* (c) Copyright 2009 - " << MACRO_STR(BUILD_YEAR) << " IWStudio" << std::endl <<
                 "* Released under GNU General Public License, vesion 2" << std::endl <<
                 "*" << std::endl <<
                 std::endl;


    _INFO(_logModule, "ON Server Starting Up...");
    setApplicationName("ONCoreServer");
    setApplicationVersion(MACRO_STR(DETECTED_ON_VERSION));
    setOrganizationName("IWStudio");
    setOrganizationDomain("iwstudio.hu");

    _INFO(_logModule, "Installing signal handlers");
    connect(new Common::UnixSignalHandler(SIGHUP, this),
            SIGNAL(CoughtSignal()), SLOT(quit()));
    connect(new Common::UnixSignalHandler(SIGINT, this),
            SIGNAL(CoughtSignal()), SLOT(quit()));
    connect(new Common::UnixSignalHandler(SIGQUIT, this),
            SIGNAL(CoughtSignal()), SLOT(quit()));
    connect(new Common::UnixSignalHandler(SIGTERM, this),
            SIGNAL(CoughtSignal()), SLOT(quit()));

    _INFO(_logModule, "Parsing commandline arguments");

    _INFO(_logModule, "Loading config file");

    _INFO(_logModule, "Setting up logger");
    Common::Logger::Instance()->SetLogToStdout(true);
    Common::Logger::Instance()->SetStdoutLogLevel(Common::Logger::Level::Trace);
    Common::Logger::Instance()->SetFileLogLevel(Common::Logger::Level::Trace);
    Common::Logger::Instance()->SetLogFormat(Common::Logger::Format::Csv);
    Common::Logger::Instance()->SetLogFile(QString(getenv("HOME")).append("/ONServerCore.log"));
    Common::Logger::Instance()->FlushStartupBuffer();

    _INFO(_logModule, "Setting up command interface");
    ServerCore::CommandInterface commander;
    connect(&commander, SIGNAL(Quit()), SLOT(quit()));

    _INFO(_logModule, "Starting Readline");
    ServerCore::Readline readline("on> ");
    readline.connect(Common::Logger::Instance().data(), SIGNAL(BeforeLogLine()), SLOT(Disable()),
                     Qt::DirectConnection);
    readline.connect(Common::Logger::Instance().data(), SIGNAL(AfterLogLine()), SLOT(Enable()),
                     Qt::DirectConnection);
    connect(&readline, SIGNAL(EndSignal()), SLOT(quit()));
    commander.connect(&readline, SIGNAL(LineRead(QString)), SLOT(ProcessCommand(QString)));

    _INFO(_logModule, "Start listening");
    ServerCore::Listener listener;
    listener.listen(3214);

    _INFO(_logModule, "ON Server Startup Complete");
    int exitCode = QCoreApplication::exec();
    _INFO(_logModule, "ON Server Shutting Down...");

    Common::Logger::Instance()->disconnect(&readline);
    readline.Disable();

    return exitCode;
}

} // namespace ServerCore
} // namespace ON
} // namespace IWStudio
} // namespace Com

int main(int argc, char **argv) {
    Com::IWStudio::ON::ServerCore::Application app(argc, argv);

    return app.run();
}
