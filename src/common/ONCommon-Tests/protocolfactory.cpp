#include <gtest/gtest.h>

#include <QSharedPointer>

#include "../ONCommon/logger.h"
#include "../ONCommon/protocolfactory.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

class ProtocolFactory : public ::testing::Test {
public:
    Common::ProtocolFactory _factory;

    static void SetUpTestCase() {
#ifdef DEBUG
        Common::Logger::Instance()->SetLogToStdout(true);
        Common::Logger::Instance()->SetStdoutLogLevel(Common::Logger::Level::Trace);
#endif
        Common::Logger::Instance()->FlushStartupBuffer();
    }
};

TEST_F(ProtocolFactory, Construction)
{
    // Implicit ok if the fixture can SetUp
}

} // Tests
} // ON
} // IWStudio
} // Com
