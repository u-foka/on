#ifndef COM_IWSTUDIO_ON_COMMON_LOG_H
#define COM_IWSTUDIO_ON_COMMON_LOG_H

#include "logger.h"

#define LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Instance()-> \
        _LOG(_LEVEL_, _MODULE_, _MESSAGE_)
#define _LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Log(Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
        _MODULE_, _MESSAGE_, QString(__PRETTY_FUNCTION__).append(" @ ") \
            .append(QString(__FILE__).replace(ON_SRC_ROOT, "")).append(":%1").arg(__LINE__))

#define LOGS(_LEVEL_, _MODULE_, _MESSAGE_) \
    _LOGS(Com::IWStudio::ON::Common::Logger::Instance(), _LEVEL_, _MODULE_, _MESSAGE_)
#define _LOGS(_LOGGER_, _LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Stream(_LOGGER_, Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
        _MODULE_, QString(__PRETTY_FUNCTION__).append(" @ ").append(QString(__FILE__).replace(ON_SRC_ROOT, "")) \
            .append(":%1").arg(__LINE__)) << _MESSAGE_

#endif // COM_IWSTUDIO_ON_COMMON_LOG_H
