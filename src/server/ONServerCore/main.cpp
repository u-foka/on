#include <cstdlib>
#include <iostream>

#include <QCoreApplication>

#include <ONCommon/logger.h>

const char *_logModule = "Main";

int main(int argv, char** argc)
{
    using namespace Com::IWStudio::ON;

    QCoreApplication app(argv, argc);

    LOG(Info, _logModule, "ON Server Starting Up...");

    LOG(Info, _logModule, "Parsing commandline arguments");

    LOG(Info, _logModule, "Loading config file");

    Common::Logger::Instance()->SetLogToStdout(true);
    Common::Logger::Instance()->FlushStartupBuffer();

    LOG(Info, _logModule, "ON Server Startup Complete");
    return app.exec();
    LOG(Info, _logModule, "ON Server Shutting Down...");
}

