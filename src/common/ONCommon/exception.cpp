#include "exception.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

Exception::Exception(const std::string &message) throw()
    : _message(message)
{
}

const char * Exception::what() const throw()
{
    return _message.c_str();
}

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com
