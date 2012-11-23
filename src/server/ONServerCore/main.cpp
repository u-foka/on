#include <cstdlib>
#include <iostream>
#include <signal.h>

#include <QCoreApplication>

#include <ONCommon/log.h>
#include <ONCommonPosix/unixsignalhandler.h>

const char *_logModule = "Main";

int main(int argv, char** argc)
{
    using namespace Com::IWStudio::ON;

    QCoreApplication app(argv, argc);

    LOG(Info, _logModule, "ON Server Starting Up...");
    LOG(Info, _logModule, "Installing signal handlers");
    QObject::connect(new Common::UnixSignalHandler(SIGHUP, &app),
                     SIGNAL(CoughtSignal()), &app, SLOT(quit()));
    QObject::connect(new Common::UnixSignalHandler(SIGINT, &app),
                     SIGNAL(CoughtSignal()), &app, SLOT(quit()));
    QObject::connect(new Common::UnixSignalHandler(SIGQUIT, &app),
                     SIGNAL(CoughtSignal()), &app, SLOT(quit()));
    QObject::connect(new Common::UnixSignalHandler(SIGTERM, &app),
                     SIGNAL(CoughtSignal()), &app, SLOT(quit()));

    LOG(Info, _logModule, "Parsing commandline arguments");

    LOG(Info, _logModule, "Loading config file");

    Common::Logger::Instance()->SetLogToStdout(true);
    Common::Logger::Instance()->SetStdoutLogLevel(Common::Logger::Level::Trace);
    Common::Logger::Instance()->FlushStartupBuffer();

    LOG(Info, _logModule, "ON Server Startup Complete");
    return app.exec();
    LOG(Info, _logModule, "ON Server Shutting Down...");
}

