#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSharedPointer>
#include <QBuffer>

#include "../ONCommon/logger.h"
#include "../ONCommon/iprotocol.h"
#include "../ONCommon/protocolfactory.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

using ::testing::Sequence;
using ::testing::AtLeast;
using ::testing::Return;

class ProtocolFactory : public ::testing::Test {
public:
    Common::ProtocolFactory _factory;
    Sequence _seq;

    static void SetUpTestCase() {
#ifdef DEBUG
        Common::Logger::Instance()->SetLogToStdout(true);
        Common::Logger::Instance()->SetStdoutLogLevel(Common::Logger::Level::Trace);
#endif
        Common::Logger::Instance()->FlushStartupBuffer();
    }

    class MockProtocol : public Common::IProtocol {
    public:
        MockProtocol(QObject *parent = 0) : IProtocol(parent){}
        virtual ~MockProtocol(){};

        MOCK_CONST_METHOD0(HandshakeSize, int ());
        MOCK_CONST_METHOD1(CheckHandshake, Common::IProtocol * (QByteArray));
        MOCK_METHOD1(Attach, void (QIODevice &device));
        MOCK_METHOD0(Detach, void ());
        MOCK_METHOD0(DataAvailable, void ());
        MOCK_METHOD0(DataSent, void ());
    };
};

TEST_F(ProtocolFactory, Construction)
{
    // Implicit ok if the fixture can SetUp
}

TEST_F(ProtocolFactory, SuccessfullSelection)
{
    QByteArray data("TESTDATA1\nOTHER");

    MockProtocol mock1;
    MockProtocol mock2;

    EXPECT_CALL(mock1, HandshakeSize()).WillRepeatedly(Return(10));
    EXPECT_CALL(mock2, HandshakeSize()).WillRepeatedly(Return(5));

    EXPECT_CALL(mock2, CheckHandshake(QByteArray("TESTD"))).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock1, CheckHandshake(QByteArray("TESTDATA1\n"))).InSequence(_seq)
            .WillOnce(Return((Common::IProtocol*)0x4201));
    EXPECT_CALL(mock2, CheckHandshake(QByteArray("OTHER"))).InSequence(_seq)
            .WillOnce(Return((Common::IProtocol*)0x4202));

    _factory.RegisterProtocol(&mock1);
    _factory.RegisterProtocol(&mock2);

    QBuffer device(&data);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), (Common::IProtocol*)0x4201);
    EXPECT_EQ(_factory.CreateProtocol(device), (Common::IProtocol*)0x4202);
}

} // Tests
} // ON
} // IWStudio
} // Com
