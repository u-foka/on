#include <gtest/gtest.h>

#include <QSharedPointer>

#include "../ONCommon/protocolfactory.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

class ProtocolFactory : public ::testing::Test {
public:
    QSharedPointer<Common::ProtocolFactory> _factory;

    virtual void SetUp() override
    {
        _factory = Common::ProtocolFactory::Instance();
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
