#ifndef COM_IWSTUDIO_ON_COMMON_EXCEPTION_H
#define COM_IWSTUDIO_ON_COMMON_EXCEPTION_H

#include <string>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

class Exception : public std::exception
{
public:
    Exception(const std::string &message) throw();

    virtual const char * what() const throw() override;

private:
    std::string _message;

};

} // namespace Common
} // namespace ON
} // namespace IWStudio
} // namespace Com

#endif // COM_IWSTUDIO_ON_COMMON_EXCEPTION_H
