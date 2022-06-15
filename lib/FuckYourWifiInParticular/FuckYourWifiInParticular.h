#ifndef _FuckYourWifiInParticular_H_
#define _FuckYourWifiInParticular_H_

bool sendDeauth(uint8_t* apMac, uint8_t* stMac, uint8_t reason, uint8_t ch);

bool sendPacket(uint8_t* packet, uint16_t packetSize, uint8_t ch, bool force_ch);

#endif
