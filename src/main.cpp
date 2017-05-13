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

//
int ledPin = 8;

#define LED 8

#define LED_pb 6

#define BUTTON 7

int val = 0;
int old_val = 0;
int state = 0;

void setup() {
  // initialize the Ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // set 'ledPin' in output mode
  pinMode(LED, OUTPUT);
  pinMode(LED_pb, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
    // blink the led, setting 'ledPin' to high and a second later to low
    // digitalWrite(LED, HIGH);
    // delay(1000);
    // digitalWrite(LED, LOW);
    // delay(1000);

    val = digitalRead(BUTTON);

    if ((val == HIGH) && (old_val == LOW)){
        state = 1 - state;
        delay(10);
    }

    old_val = val;

    if (state == 1) {
        digitalWrite(LED_pb, HIGH);
    } else {
        digitalWrite(LED_pb, LOW);
    }
}
