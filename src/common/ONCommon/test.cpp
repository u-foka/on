#include "test.h"

#include <iostream>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Common {

Test::Test()
{
    Print("Test is created.");
}

void Test::Print(const QString ctext)
{
    std::cout << ctext.toUtf8().constData() << std::endl;
}

} // Tests
} // ON
} // IWStudio
} // Com
