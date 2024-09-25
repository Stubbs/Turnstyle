#include <Arduino.h>
#include <ezButton.h>
#include <TM1637Display.h>

ezButton button(D2);
int crowd_count = 0;

// Module connection pins (Digital Pins)
#define CLK D5
#define DIO D3

TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Booted up");

  button.setDebounceTime(50);
  button.setCountMode(COUNT_FALLING);

  // Set the onboard LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  // Switch off the onboard LED
  digitalWrite(LED_BUILTIN, HIGH);

  // Set D1 to be an output pin for the relay.
  pinMode(D1, OUTPUT);
  // Turn it off
  digitalWrite(D1, LOW);

  display.clear();
  display.setBrightness(7);
  display.showNumberDec(0, false);
}

void loop() {
  display.showNumberDec(crowd_count, false);

  button.loop();
  int count = button.getCount();

  if(crowd_count != count) {
    crowd_count = count;
    Serial.print("Crowd count: ");
    Serial.println(crowd_count);

    // digitalWrite(LED_BUILTIN, LOW);
    // Turn relay on
    digitalWrite(D1, HIGH);

    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);

    // Turn relay off
    digitalWrite(D1, LOW);
  }
}
