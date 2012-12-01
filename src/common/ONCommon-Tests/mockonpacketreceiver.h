#ifndef COM_IWSTUDIO_ON_TESTS_MOCKONPACKETRECEIVER_H
#define COM_IWSTUDIO_ON_TESTS_MOCKONPACKETRECEIVER_H

#include <gmock/gmock.h>

#include <ONCommonProtocol/ionprotocol.h>

namespace Com {
namespace IWStudio {
namespace ON {
namespace Tests {

using Common::ONPacket;

class MockONPacketReceiver : public QObject
{
    Q_OBJECT
public:
    MockONPacketReceiver(QObject *parent = 0) : QObject(parent){}
    virtual ~MockONPacketReceiver(){}

    MOCK_METHOD1(PacketReceivedMock, void(const ONPacket &packet));

public slots:
    void PacketReceived(const ONPacket &packet)
    {
        PacketReceivedMock(packet);
    }

};

} // Tests
} // ON
} // IWStudio
} // Com

#endif // COM_IWSTUDIO_ON_TESTS_MOCKONPACKETRECEIVER_H
