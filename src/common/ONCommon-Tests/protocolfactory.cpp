#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSharedPointer>
#include <QBuffer>

#include "../ONCommon/logger.h"
#include "../ONCommon/iprotocol.h"
#include "../ONCommon/protocolfactory.h"
#include "../ONCommon/exception.h"

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
        MOCK_CONST_METHOD1(ConstructIfSuitable, Common::IProtocol * (QByteArray));
        MOCK_METHOD1(Attach, void (QIODevice *device));
        MOCK_METHOD0(Detach, void ());
    };
};

TEST_F(ProtocolFactory, Construction)
{
    // Implicit ok if the fixture can SetUp
}

TEST_F(ProtocolFactory, SuccessfullSelection)
{
    QByteArray data("TESTDATA1\nOTHER_REMAINING");

    MockProtocol mock1;
    MockProtocol mock2;

    EXPECT_CALL(mock1, HandshakeSize()).WillRepeatedly(Return(10));
    EXPECT_CALL(mock2, HandshakeSize()).WillRepeatedly(Return(5));

    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("TESTD"))).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TESTDATA1\n"))).InSequence(_seq)
            .WillOnce(Return((Common::IProtocol*)0x4201));
    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("OTHER"))).InSequence(_seq)
            .WillOnce(Return((Common::IProtocol*)0x4202));

    _factory.RegisterProtocol(&mock1);
    _factory.RegisterProtocol(&mock2);

    QBuffer device(&data);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), (Common::IProtocol*)0x4201);
    EXPECT_EQ(_factory.CreateProtocol(device), (Common::IProtocol*)0x4202);
    EXPECT_EQ(device.read(10), QByteArray("_REMAINING"));
    device.close();
}

TEST_F(ProtocolFactory, SelectFragmented)
{
    QByteArray data1("TEST");
    QByteArray data2("TESTDATA1\nOTHER");

    MockProtocol mock1;
    MockProtocol mock2;

    EXPECT_CALL(mock1, HandshakeSize()).WillRepeatedly(Return(2));
    EXPECT_CALL(mock2, HandshakeSize()).WillRepeatedly(Return(10));

    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TE"))).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TE"))).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("TESTDATA1\n"))).InSequence(_seq)
            .WillOnce(Return((Common::IProtocol*)0x4201));

    _factory.RegisterProtocol(&mock1);
    _factory.RegisterProtocol(&mock2);

    QBuffer device;

    device.setBuffer(&data1);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), nullptr);
    EXPECT_EQ(device.read(15), QByteArray("TEST"));
    device.close();

    device.setBuffer(&data2);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), (Common::IProtocol*)0x4201);
    EXPECT_EQ(device.read(5), QByteArray("OTHER"));
    device.close();
}

TEST_F(ProtocolFactory, ThrowUnmatched)
{
    QByteArray data("TEST");

    MockProtocol mock;

    EXPECT_CALL(mock, HandshakeSize()).WillRepeatedly(Return(2));

    EXPECT_CALL(mock, ConstructIfSuitable(QByteArray("TE"))).InSequence(_seq)
            .WillOnce(Return(nullptr));

    _factory.RegisterProtocol(&mock);

    QBuffer device;

    device.setBuffer(&data);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();
}

} // Tests
} // ON
} // IWStudio
} // Com
