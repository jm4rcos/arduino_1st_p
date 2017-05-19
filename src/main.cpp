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

#define SENSOR 0
#define BUTTON 7
#define LED_pb 6
#define LED_9 9
#define LED13 13

int ledPin = 8;
int val = 0;
int old_val = 0;
int state = 0;
int i = 0;
int brightness =128;
unsigned long  startTime = 0;


void setup() {
  // initialize the Ethernet device
  //Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // set 'ledPin' in output mode
  pinMode(LED13, OUTPUT);
  pinMode(LED_pb, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LED_9, OUTPUT);
  Serial.begin(9600);   // open the serial port to send
                        // data back to the computer at
                        // 9600 bits per second
}

void fadeInOutTheLed_9() {
    for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
        analogWrite(LED_9, i);
        // set the LED brightness
        delay(10); // Wait 10ms because analogWrite
        // is instantaneous and we would
        // not see any change
    }
    for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)
        analogWrite(LED_9, i); // set the LED brightness
        delay(10);
        // Wait 10ms
    }
}

void fadeInLed_9() {
    for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
        analogWrite(LED_9, i);
        // set the LED brightness
        delay(10); // Wait 10ms because analogWrite
        // is instantaneous and we would
        // not see any change
    }
}

void fadeOutLed_9() {
    for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)
        analogWrite(LED_9, i); // set the LED brightness
        delay(10);
        // Wait 10ms
    }
}

void blinkTheLed_13() {
    // Blink the led 13, setting 'ledPin' to high and a second later to low
    // If you have SPI configured (ethernet shield) LED will not blink because
    // pins 10,11,12 and 13 are user for SPI.
    digitalWrite(LED13, HIGH);
    delay(1000);
    digitalWrite(LED13, LOW);
    delay(1000);

}

void pressButton() {
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

void pressButtonToFade() {
    val = digitalRead(BUTTON);
    if ((val == HIGH) && (old_val == LOW)){
        state = 1 - state;
        delay(10);
    }
    old_val = val;
    if (state == 1) {
        fadeInLed_9();
    }
    else {
        fadeOutLed_9();
    }

}


void dimLed_9() {
    val = digitalRead(BUTTON);  // read input value and store it
                                // yum, fresh
    // check if there was a transition
    if ((val == HIGH) && (old_val == LOW)) {
        state = 1 - state;  // change the state from off to on
                            // or vice-versa
        startTime = millis();   // millis() is the Arduino clock
                                // it returns how many milliseconds
                                // have passed since the board has
                                // been reset.
                                // (this line remembers when the button
                                // was last pressed)
        delay(10);
    }

    // check whether the button is being held down
    if ((val == HIGH) && (old_val == HIGH)) {
        // If the button is held for more than 500ms.
        if (state == 1 && (millis() - startTime) > 500) {
            brightness++;       // increment brightness by 1
            delay(10);          // delay to avoid brightness going up too fast
            if (brightness > 255) {         // 255 is the max brightness
                brightness = 0;             // if we go over 255
                                            // let’s go back to 0
            }
        }
    }

    old_val = val;                          // val is now old, let’s store it

    if (state == 1) {
        analogWrite(LED_9, brightness);     // turn LED ON at the
                                            // current brightness level
    } else {
        analogWrite(LED_9, 0);              // turn LED OFF
    }
}

void analogBlinkLed_13() { // read analog 0 pin (A0) and write digital  (pin 9)

    val = analogRead(0);        // read the value from the sensor

    digitalWrite(13, HIGH);     // turn the LED on
    delay(val);                 // stop the program for some time
    digitalWrite(13, LOW);      // turn the LED off
    delay(val);                 // stop the program for some time
}


void analogBlinkLed_9() { // read analog 0 pin (A0) and write pwm output (pin 9)

    val = analogRead(0);            // read the value from
                                    // the sensor

    analogWrite(LED_9, val/4);      // turn the LED on at the brightness set
                                    // by the sensor
                                    // val is divided by 4 to adapt to pwm
                                    // output range (0-255)

    delay(10);                      // stop the program for some time
}


void analogToSerial() {
    val = analogRead(SENSOR);   // read the value from
                                // the sensor
    Serial.println(val);        // print the value to
                                // the serial port
    delay(100);                 // wait 100ms between
                                // each send
}

void loop() {

    //blinkTheLed_13();
    //pressButton();
    //fadeInOutTheLed_9();
    //pressButtonToFade();
    //dimLed_9();
    //analogBlinkLed_13();
    //analogBlinkLed_9();
    //analogToSerial();
}
