
#include <Adafruit_CircuitPlayground.h>\
//Rainbow cycle for when puzzle is complete
#define ROTATION_RATE   100    // lower is faster
//Global Variables
//Inputs
  int buttonA = 19;
  int buttonB = 4;
  int buttonC = 12;
//LightCounters
  int lightCounter = 0;
  int counterMax = 9;
//States for buttonA
  int buttonStateA;
  int lastButtonStateA = LOW;
  unsigned long lastDebounceTime = 0;
//States for buttonB
  int buttonStateB;
  int lastButtonStateB = LOW;
  unsigned long lastDebounceTimeB = 0;
//States for buttonC
  int buttonStateC;
  int lastButtonStateC = LOW;
  unsigned long lastDebounceTimeC = 0;
// Colur variables
  uint32_t red = 0xFF0000;
  uint32_t green = 0x29CF4B; //
// Array for individual states
  bool lightState[] = {
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
};
// Colour array for completion state
  uint32_t rainbow[] = {
    0xFF0000,   
    0xFF5500,
    0xFFFF00,
    0x00FF00,
    0x00FF55,
    0x00FFFF,
    0x0000FF,
    0x5500FF,
    0xFF00FF,
    0xFFFFFF
};
int colorIndex;
int startIndex;
int completionPercent=0;

unsigned long debounceDelay = 50;  // the debounce time; increase if the output flickers

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  CircuitPlayground.begin();
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT_PULLUP);
  Serial.begin(9600);
 CircuitPlayground.setBrightness(3);
  CircuitPlayground.setPixelColor(0, red);
  CircuitPlayground.setPixelColor(1, red);
  CircuitPlayground.setPixelColor(2, red);
  CircuitPlayground.setPixelColor(3, red);
  CircuitPlayground.setPixelColor(4, red);
  CircuitPlayground.setPixelColor(5, red);
  CircuitPlayground.setPixelColor(6, red);
  CircuitPlayground.setPixelColor(7, red);
  CircuitPlayground.setPixelColor(8, red);
  CircuitPlayground.setPixelColor(9, red);
  
   
}

// the loop function runs over and over again forever
void loop() {
// Reading the buttons inputs
  int stateA = digitalRead(buttonA);
  int stateB = digitalRead(buttonB);
  int stateC = digitalRead(buttonC);
  
//Condition for Red/ Green
if(completionPercent==10){
  // Loop through and set pixels
  colorIndex = startIndex;
  for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, rainbow[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
  }
  // Increment start index into color array
  startIndex++;
  // Check value and reset if necessary
  if (startIndex > 9) startIndex = 0;
  // Wait a little bit so we don't spin too fast
  delay(ROTATION_RATE);
  }else{
 if (lightState[lightCounter]==true){
    CircuitPlayground.setPixelColor(lightCounter, green);
    } else { 
      CircuitPlayground.setPixelColor(lightCounter, red);}
      }
 
  if ((millis() - lastDebounceTime) > debounceDelay) {

//Debounce for ButtonA
    if (stateA != buttonStateA) {
      buttonStateA = stateA;
      if (buttonStateA == HIGH) {
        lightCounter++;
        if (lightCounter > 9) {
          lightCounter = 0;
        }
        CircuitPlayground.setPixelColor(lightCounter, 0, 0,   0);// blink once when the piel is "selected"
        delay(500);
      }
    }
  }
  lastButtonStateA = stateA;

//Debounce for ButtonB
  if (stateB != lastButtonStateB) {
    // reset the debouncing timer
    lastDebounceTimeB = millis();
  }

  if ((millis() - lastDebounceTimeB) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (stateB != buttonStateB) {
      buttonStateB = stateB;

      // only toggle the LED if the new button state is HIGH
      if (buttonStateB == HIGH) {
        lightCounter--;
        if (lightCounter < 0) {
          lightCounter = 9;
        }
        CircuitPlayground.setPixelColor(lightCounter, 0, 0,   0);
        delay(500);
      }
    }
  }
  lastButtonStateB = stateB;

//Debounce for Button C
  if ((millis() - lastDebounceTimeC) > 200) {

    if (stateC != buttonStateC) {
      buttonStateC = stateC;

      if (buttonStateC == HIGH) {
        lightState[lightCounter]= !lightState[lightCounter];
        if(lightState[lightCounter]==true){
          completionPercent++;
          Serial.println(completionPercent);
          }else{
            completionPercent--;
            Serial.println(completionPercent);}
      }
    }
  }
  lastButtonStateC = stateC;

}
