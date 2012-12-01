#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSharedPointer>
#include <QBuffer>

#include <ONCommon/logger.h>
#include <ONCommon/iprotocol.h>
#include <ONCommon/protocolfactory.h>
#include <ONCommonProtocol/ionprotocol.h>
#include <ONCommonProtocol/onbinaryprotocol.h>
#include <ONCommon/exception.h>

#include "mockonpacketreceiver.h"

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

using ::testing::_;
using ::testing::Sequence;

using Common::ONPacket;
using namespace Common::Protocol;

class ONBinaryProtocol : public ::testing::Test {
public:
    Common::ProtocolFactory _factory;
    Sequence _seq;

    static void SetUpTestCase()
    {
#ifdef DEBUG
        Common::Logger::Instance()->SetLogToStdout(true);
        Common::Logger::Instance()->SetStdoutLogLevel(Common::Logger::Level::Trace);
#endif
        Common::Logger::Instance()->FlushStartupBuffer();
    }

    virtual void SetUp() override
    {
        _factory.RegisterProtocol(new Common::ONBinaryProtocol(&_factory));
    }
};

TEST_F(ONBinaryProtocol, Construction)
{
    // Implicit ok if the fixture can SetUp
}

TEST_F(ONBinaryProtocol, Parse)
{
    QByteArray data(
                "ONB 001.000\n"

                "\x00\x00\x00\x01"
                "\x00\x00\x00\x2A"
                "\x00\x00\x00\x01"
                "\x00\x00\x00\x06"
                "DIGEST"
                "\x00\x00\x00\x01"
                "\x00\x00\x00\x04"
                "NTLM"
                "\x00\x00\x00\x01"
                "\x00\x00\x00\x08"
                "KERBEROS"

                "\x00\x00\x00\x02"
                "\x00\x00\x00\x0E"
                "\x00\x00\x00\x01"
                "\x00\x00\x00\x06"
                "DIGEST"

                , 84
    );

    QBuffer device(&data);
    device.open(QIODevice::ReadOnly);

    auto proto = reinterpret_cast<Common::IONProtocol*>(_factory.CreateProtocol(device));
    ASSERT_NE(proto, nullptr);

    MockONPacketReceiver receiver;

    ONPacket packet1;
    packet1.Message = Message::AvailableSecurityModes;
    packet1.Arguments.insert(MessageArgument::SecurityMode, QByteArray("DIGEST", 6));
    packet1.Arguments.insert(MessageArgument::SecurityMode, QByteArray("NTLM", 4));
    packet1.Arguments.insert(MessageArgument::SecurityMode, QByteArray("KERBEROS", 8));
    EXPECT_CALL(receiver, PacketReceivedMock(packet1)).InSequence(_seq);

    ONPacket packet2;
    packet2.Message = Message::SelectSecurityMode;
    packet2.Arguments.insert(MessageArgument::SecurityMode, QByteArray("DIGEST", 6));
    EXPECT_CALL(receiver, PacketReceivedMock(packet2)).InSequence(_seq);

    QObject::connect(proto, SIGNAL(PacketReceived(const ONPacket &)), &receiver, SLOT(PacketReceived(const ONPacket &)));
    proto->Attach(&device);

    delete proto;

    device.close();
}

TEST_F(ONBinaryProtocol, DetectInvalidHeader)
{
    QBuffer device;
    QByteArray data1("ONB 00!.000\n");
    QByteArray data2("ONB 001.ZZZ\n");
    QByteArray data3("ONB 001.000 ");
    QByteArray data4("ONB 001 000\n");
    QByteArray data5("ONBX001.000\n");
    QByteArray data6("ONX 001.000\n");
    QByteArray data7("BNB 001.000\n");
    QByteArray dataSuccess("ONB 001.000\n");

    device.setBuffer(&data1);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data2);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data3);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data4);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data5);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data6);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&data7);
    device.open(QIODevice::ReadOnly);
    EXPECT_THROW(_factory.CreateProtocol(device), Common::Exception);
    device.close();

    device.setBuffer(&dataSuccess);
    device.open(QIODevice::ReadOnly);
    auto proto = _factory.CreateProtocol(device);
    EXPECT_NE(proto, nullptr);
    EXPECT_NE(dynamic_cast<Common::IONProtocol*>(proto), nullptr);
    EXPECT_NE(dynamic_cast<Common::ONBinaryProtocol*>(proto), nullptr);
    delete proto;
    device.close();

}

} // Tests
} // ON
} // IWStudio
} // Com
