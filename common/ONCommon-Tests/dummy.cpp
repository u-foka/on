#include <gtest/gtest.h>

#include "../ONCommon/test.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

TEST(Dummy, DummyTest)
{
    auto test = new Common::Test();
    ASSERT_NE(test, nullptr);
    test->Print("Testing the test class :D");
    delete test;
    test = 0;
}

} // Tests
} // ON
} // IWStudio
} // Com
