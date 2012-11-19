#ifndef COM_IWSTUDIO_ON_COMMON_LOGGER_INLINE_H
#define COM_IWSTUDIO_ON_COMMON_LOGGER_INLINE_H

#include "logger.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

template<typename T> Logger::Stream & Logger::Stream::operator<<(const T &value)
{
    _lineStream << value;
    return *this;
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_LOGGER_INLINE_H
