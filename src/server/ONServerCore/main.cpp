#include <cstdlib>
#include <iostream>
#include <signal.h>

#include <QCoreApplication>

#include <ONCommon/log.h>
#include <ONCommonPosix/unixsignalhandler.h>

#include "listener.h"

const char *_logModule = "Main";

int main(int argv, char** argc)
{
    using namespace Com::IWStudio::ON;

    LOG(Info, _logModule, "ON Server Starting Up...");
    QCoreApplication::setApplicationName("ONCoreServer");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("IWStudio");
    QCoreApplication::setOrganizationDomain("iwstudio.hu");

    QCoreApplication app(argv, argc);

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
    Common::Logger::Instance()->SetFileLogLevel(Common::Logger::Level::Trace);
    Common::Logger::Instance()->SetLogFormat(Common::Logger::Format::Csv);
    Common::Logger::Instance()->SetLogFile(QString(getenv("HOME")).append("/ONServerCore.log"));
    Common::Logger::Instance()->FlushStartupBuffer();

    LOG(Info, _logModule, "Start listening");
    ServerCore::Listener listener;
    listener.listen(3214);

    LOG(Info, _logModule, "ON Server Startup Complete");
    int exitCode = app.exec();
    LOG(Info, _logModule, "ON Server Shutting Down...");

    return exitCode;
}

