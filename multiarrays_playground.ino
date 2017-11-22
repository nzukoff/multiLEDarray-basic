#include "FastLED.h"
#define LED_PIN1    3
#define LED_PIN2    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS_PER_STRIP 8
#define BRIGHTNESS 150
CRGB leds1[NUM_LEDS_PER_STRIP];
CRGB leds2[NUM_LEDS_PER_STRIP];


// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPinX = A0;  
const int analogInPinY = A1;  
const int digitalInPin = 9;  

int JoystickValueX = 0;        // value read from the pot
int JoystickValueY = 0;        // value read from the pot
int JoystickButtonValue = 0;        // value read from the pot

int outputValue = 0;        // value output to the PWM (analog out)
int currentPositionX = 0;
int previousPositionX = 0;
int currentPositionY = 0;
int previousPositionY = 0;
boolean started = false;

void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 10
//  FastLED.addLeds<NEOPIXEL, 3>(leds1, NUM_LEDS_PER_STRIP1);
//
//  // tell FastLED there's 60 NEOPIXEL leds on pin 11
//  FastLED.addLeds<NEOPIXEL, 6>(leds2, NUM_LEDS_PER_STRIP2);

  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
  pinMode(digitalInPin, INPUT_PULLUP);  
}


void loop() {

   // read the input values
  JoystickValueX = analogRead(analogInPinX);
  JoystickValueY = analogRead(analogInPinY);
  JoystickButtonValue = digitalRead(digitalInPin);

//  // print the results to the serial monitor:
//  Serial.print(JoystickValueX);
//  Serial.print(",");
//  Serial.print(JoystickValueY);
//  Serial.print(",");
//  Serial.println(JoystickButtonValue);
//  
//
//  // wait 100 milliseconds before the next loop
//  // for the analog-to-digital converter to settle
//  // after the last reading:
//  delay(5);

  if (started == false) {
    leds1[0] = CRGB::Red;
    leds2[0] = CRGB::Blue;
    FastLED.show();  
  }
  
  if (JoystickValueX > 900) {    
    started = true;
    leds1[previousPositionX] = CRGB::Black;
    currentPositionX++;
    if (currentPositionX > NUM_LEDS_PER_STRIP-1) {
        currentPositionX = 0;
    }    
    previousPositionX = currentPositionX;
    leds1[currentPositionX] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
  
  if (JoystickValueX < 100) {    
    started = true;
    leds1[previousPositionX] = CRGB::Black;
    currentPositionX--;
    if (currentPositionX < 0) {
        currentPositionX = NUM_LEDS_PER_STRIP-1;
    }    
    previousPositionX = currentPositionX;
    leds1[currentPositionX] = CRGB::Red;
    FastLED.show();
    delay(100);
  }

    if (JoystickValueY > 900) {    
    started = true;
    leds2[previousPositionY] = CRGB::Black;
    currentPositionY++;
    if (currentPositionY > NUM_LEDS_PER_STRIP-1) {
        currentPositionY = 0;
    }    
    previousPositionY = currentPositionY;
    leds2[currentPositionY] = CRGB::Blue;
    FastLED.show();
    delay(100);
  }
  
  if (JoystickValueY < 100) {    
    started = true;
    leds2[previousPositionY] = CRGB::Black;
    currentPositionY--;
    if (currentPositionY < 0) {
        currentPositionY = NUM_LEDS_PER_STRIP-1;
    }    
    previousPositionY = currentPositionY;
    leds2[currentPositionY] = CRGB::Blue;
    FastLED.show();
    delay(100);
  }
}
