#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>

// define mac address for ethernet interface on ethhernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// define ip address, mask(subnet), dns and gateway for ethernet interface
IPAddress ip(192, 168, 254, 177);
IPAddress myDns(192, 168, 254, 1);
IPAddress gateway(192, 168, 254, 1);
IPAddress subnet(255, 255, 255, 0);

// ways to define a variable
int ledPin = 8;
#define LED 8

void setup() {
  // initialize the Ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  // set 'ledPin' in output mode
  pinMode(LED, OUTPUT);
}

void loop() {
    // blink the led, setting 'ledPin' to high and a second later to low
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
}
