#ifndef COM_IWSTUDIO_ON_COMMON_LOG_H
#define COM_IWSTUDIO_ON_COMMON_LOG_H

#include "logger.h"

#define ON_SRC_ROOT_STR MACRO_STR(ON_SRC_ROOT)

#define LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Instance()-> \
        _LOG(_LEVEL_, _MODULE_, _MESSAGE_)
#define _LOG(_LEVEL_, _MODULE_, _MESSAGE_) \
    Log(Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
        _MODULE_, _MESSAGE_, QString(__PRETTY_FUNCTION__).append(" @ ") \
            .append(QString(__FILE__).replace(ON_SRC_ROOT_STR, "")).append(":%1").arg(__LINE__))

#define LOGS(_LEVEL_, _MODULE_, _MESSAGE_) \
    _LOGS(Com::IWStudio::ON::Common::Logger::Instance(), _LEVEL_, _MODULE_, _MESSAGE_)
#define _LOGS(_LOGGER_, _LEVEL_, _MODULE_, _MESSAGE_) \
    Com::IWStudio::ON::Common::Logger::Stream(_LOGGER_, Com::IWStudio::ON::Common::Logger::Level::_LEVEL_, \
        _MODULE_, QString(__PRETTY_FUNCTION__).append(" @ ").append(QString(__FILE__).replace(ON_SRC_ROOT_STR, "")) \
            .append(":%1").arg(__LINE__)) << _MESSAGE_

#define _ERROR(_MODULE_, _MESSAGE_) LOG(Error, _MODULE_, _MESSAGE_)
#define _WARNING(_MODULE_, _MESSAGE_) LOG(Warning, _MODULE_, _MESSAGE_)
#define _INFO(_MODULE_, _MESSAGE_) LOG(Info, _MODULE_, _MESSAGE_)
#ifdef DEBUG
#define _DEBUG(_MODULE_, _MESSAGE_) LOG(Debug, _MODULE_, _MESSAGE_)
#define _TRACE(_MODULE_, _MESSAGE_) LOG(Trace, _MODULE_, _MESSAGE_)
#else
#define _DEBUG(_MODULE_, _MESSAGE_) do{}while(0)
#define _TRACE(_MODULE_, _MESSAGE_) do{}while(0)
#endif

#define _ERRORS(_MODULE_, _MESSAGE_) LOGS(Error, _MODULE_, _MESSAGE_)
#define _WARNINGS(_MODULE_, _MESSAGE_) LOGS(Warning, _MODULE_, _MESSAGE_)
#define _INFOS(_MODULE_, _MESSAGE_) LOGS(Info, _MODULE_, _MESSAGE_)
#ifdef DEBUG
#define _DEBUGS(_MODULE_, _MESSAGE_) LOGS(Debug, _MODULE_, _MESSAGE_)
#define _TRACES(_MODULE_, _MESSAGE_) LOGS(Trace, _MODULE_, _MESSAGE_)
#else
#define _DEBUGS(_MODULE_, _MESSAGE_) do{}while(0)
#define _TRACES(_MODULE_, _MESSAGE_) do{}while(0)
#endif

#endif // COM_IWSTUDIO_ON_COMMON_LOG_H
