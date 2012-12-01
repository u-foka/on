#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSharedPointer>
#include <QBuffer>

#include <ONCommon/logger.h>
#include <ONCommon/iprotocol.h>
#include <ONCommon/protocolfactory.h>
#include <ONCommon/exception.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

using ::testing::_;
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
        virtual ~MockProtocol(){}

        MOCK_CONST_METHOD0(HandshakeSize, int ());
        MOCK_CONST_METHOD2(ConstructIfSuitable, Common::IProtocol * (const QByteArray &, QObject *));
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
    QBuffer device(&data);

    MockProtocol mock1;
    MockProtocol mock2;
    MockProtocol mock1Output;
    MockProtocol mock2Output;

    EXPECT_CALL(mock1, HandshakeSize()).WillRepeatedly(Return(10));
    EXPECT_CALL(mock2, HandshakeSize()).WillRepeatedly(Return(5));

    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("TESTD"), nullptr)).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TESTDATA1\n"), nullptr)).InSequence(_seq)
            .WillOnce(Return(&mock1Output));
    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("OTHER"), nullptr)).InSequence(_seq)
            .WillOnce(Return(&mock2Output));

    _factory.RegisterProtocol(&mock1);
    _factory.RegisterProtocol(&mock2);

    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), &mock1Output);
    EXPECT_EQ(_factory.CreateProtocol(device), &mock2Output);
    EXPECT_EQ(device.read(10), QByteArray("_REMAINING"));
    device.close();
}

TEST_F(ProtocolFactory, SelectFragmented)
{
    QBuffer device;
    QByteArray data1("TEST");
    QByteArray data2("TESTDATA1\nOTHER");

    MockProtocol mock1;
    MockProtocol mock2;
    MockProtocol mockOutput;

    EXPECT_CALL(mock1, HandshakeSize()).WillRepeatedly(Return(2));
    EXPECT_CALL(mock2, HandshakeSize()).WillRepeatedly(Return(10));

    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TE"), nullptr)).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock1, ConstructIfSuitable(QByteArray("TE"), nullptr)).InSequence(_seq)
            .WillOnce(Return(nullptr));
    EXPECT_CALL(mock2, ConstructIfSuitable(QByteArray("TESTDATA1\n"), nullptr)).InSequence(_seq)
            .WillOnce(Return(&mockOutput));

    _factory.RegisterProtocol(&mock1);
    _factory.RegisterProtocol(&mock2);

    device.setBuffer(&data1);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), nullptr);
    EXPECT_EQ(device.read(15), QByteArray("TEST"));
    device.close();

    device.setBuffer(&data2);
    device.open(QIODevice::ReadOnly);
    EXPECT_EQ(_factory.CreateProtocol(device), &mockOutput);
    EXPECT_EQ(device.read(5), QByteArray("OTHER"));
    device.close();
}

TEST_F(ProtocolFactory, ThrowUnmatched)
{
    QByteArray data("TEST");

    MockProtocol mock;

    EXPECT_CALL(mock, HandshakeSize()).WillRepeatedly(Return(2));

    EXPECT_CALL(mock, ConstructIfSuitable(QByteArray("TE"), nullptr)).InSequence(_seq)
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
