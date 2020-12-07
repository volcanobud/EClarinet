#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=57,61
AudioAnalyzePeak         peak2;          //xy=67,320
AudioAnalyzePeak         peak1;          //xy=118,255
AudioAnalyzeFFT256       myFFT;       //xy=242,46
AudioSynthKarplusStrong  string2;        //xy=262,159
AudioSynthKarplusStrong  string1;        //xy=329,111
AudioSynthKarplusStrong  string4;        //xy=455,222
AudioMixer4              mixer1;         //xy=456,171
AudioSynthKarplusStrong  string5;        //xy=456,259
AudioSynthKarplusStrong  string3;        //xy=544,102
AudioSynthKarplusStrong  string7;        //xy=619,262
AudioSynthKarplusStrong  string6;        //xy=623,217
AudioMixer4              mixer2;         //xy=634,164
AudioMixer4              mixer3;         //xy=796,161
AudioOutputI2S           i2s1;           //xy=916,154
AudioConnection          patchCord1(i2s2, 0, myFFT, 0);
AudioConnection          patchCord2(i2s2, 0, peak1, 0);
AudioConnection          patchCord3(i2s2, 1, peak2, 0);
AudioConnection          patchCord4(string2, 0, mixer1, 3);
AudioConnection          patchCord5(string1, 0, mixer1, 2);
AudioConnection          patchCord6(string4, 0, mixer2, 2);
AudioConnection          patchCord7(mixer1, 0, mixer2, 0);
AudioConnection          patchCord8(string5, 0, mixer2, 3);
AudioConnection          patchCord9(string3, 0, mixer2, 1);
AudioConnection          patchCord10(string7, 0, mixer3, 2);
AudioConnection          patchCord11(string6, 0, mixer3, 1);
AudioConnection          patchCord12(mixer2, 0, mixer3, 0);
AudioConnection          patchCord13(mixer3, 0, i2s1, 0);
AudioConnection          patchCord14(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=390,376
// GUItool: end automatically generated code
    //xy=461,448
// GUItool: end automatically generated code

// GUItool: end automatically generated code

// GUItool: end automatically generated code


int stringPin1 = 24;
int stringPin2 = 25;
int stringPin3 = 26;
int stringPin4 = 27;
int stringPin5 = 28;
int stringPin6 = 29;
int stringPin7 = 30;
int octavePotPin = 32;
int sharpPin = 31;
float x = 1;
float velocity = 1;

int lastButtonState = LOW, lastButtonState1 = LOW, lastButtonState2 = LOW, lastButtonState3 = LOW, lastButtonState4 = LOW, lastButtonState5 = LOW, lastButtonState6 = LOW;
int buttonState, buttonState1, buttonState2, buttonState3, buttonState4, buttonState5, buttonState6;
// GUItool: end automatically generated code
unsigned long lastDebounceTime = 0, lastDebounceTime1 = 0, lastDebounceTime2 = 0, lastDebounceTime3 = 0, lastDebounceTime4 = 0, lastDebounceTime5 = 0, lastDebounceTime6 = 0;
unsigned long debounceDelay = 15;

void setup() {
  AudioMemory(120);
  pinMode(stringPin1, INPUT_PULLDOWN);
  pinMode(stringPin2, INPUT_PULLDOWN);
  pinMode(stringPin3, INPUT_PULLDOWN);
  pinMode(stringPin4, INPUT_PULLDOWN);
  pinMode(stringPin5, INPUT_PULLDOWN);
  pinMode(stringPin6, INPUT_PULLDOWN);
  pinMode(stringPin7, INPUT_PULLDOWN);
  pinMode(sharpPin, INPUT_PULLDOWN);
  myFFT.windowFunction(AudioWindowHanning1024);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(55);
  //sgtl5000_1.muteHeadphone();
  Serial.begin(9600);
   
}

void loop() {
  
  int val = analogRead(octavePotPin);
  //Serial.println(val);
  if(val<=205)
  {
    x = 1./4;
  }
  else if(val>205&&val<=510)
  {
    x=1./2;
  }
  else if(val>510&&val<=715)
  {
    x = 1;
  }
  else if(val>715&&val<=920)
  {
    x = 2;
  }
   else if(val>920&&val<=1023)
   {
    x=4;
   }
   //Serial.println(val);
   
   if(peak1.available()){
      velocity = peak1.read();
   }
   
     Serial.println(velocity);
   if(digitalRead(sharpPin) ==  1)
   {

    int reading = digitalRead(stringPin1);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
      }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        //string1.noteOn(329.63,1);
        string1.noteOn(x*277.18,velocity);
      }
    }
  }
  lastButtonState = reading;

  int reading1 = digitalRead(stringPin2);
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == HIGH) {
        //string2.noteOn(246.94,1);
        string2.noteOn(311.13*x,velocity);
      }
    }
  }
  lastButtonState1 = reading1;

  int reading2 = digitalRead(stringPin3);

  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {

    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == HIGH) {
        string3.noteOn(349.23*x,velocity);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState2 = reading2;
  
  int reading3 = digitalRead(stringPin4);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      // only toggle the LED if the new button state is HIGH
      if (buttonState3 == HIGH) {
        string4.noteOn(369.99*x,velocity);
        //string4.noteOn(146.83,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState3 = reading3;

  int reading4 = digitalRead(stringPin5);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading4 != lastButtonState4) {
    // reset the debouncing timer
    lastDebounceTime4 = millis();
  }

  if ((millis() - lastDebounceTime4) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

      // only toggle the LED if the new button state is HIGH
      if (buttonState4 == HIGH) {
        string5.noteOn(415.3*x,velocity);
        //string5.noteOn(110,1);
      }
      
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState4 = reading4;
    int reading5 = digitalRead(stringPin6);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading5 != lastButtonState5) {
    // reset the debouncing timer
    lastDebounceTime5 = millis();
  }

  if ((millis() - lastDebounceTime5) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading5 != buttonState5) {
      buttonState5 = reading5;

      // only toggle the LED if the new button state is HIGH
      if (buttonState5 == HIGH) {
        string6.noteOn(466.16*x,velocity);
        //string6.noteOn(110,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState5 = reading5;
    int reading6 = digitalRead(stringPin7);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading6 != lastButtonState6) {
    // reset the debouncing timer
    lastDebounceTime6 = millis();
  }

  if ((millis() - lastDebounceTime6) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading6 != buttonState6) {
      buttonState6 = reading6;

      // only toggle the LED if the new button state is HIGH
      if (buttonState6 == HIGH) {
        string7.noteOn(523.55*x,velocity);
        //string7.noteOn(110,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState6 = reading6;

   }
   else
   {
    int reading = digitalRead(stringPin1);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //string1.noteOn(329.63,1);
        string1.noteOn(x*261.625,velocity);
        Serial.println(x*261.625);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  int reading1 = digitalRead(stringPin2);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        //string2.noteOn(246.94,1);
        string2.noteOn(293.66*x,velocity);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState1 = reading1;

  int reading2 = digitalRead(stringPin3);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
        string3.noteOn(329.63*x,velocity);
        //string3.noteOn(196.00,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState2 = reading2;
  
  int reading3 = digitalRead(stringPin4);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      // only toggle the LED if the new button state is HIGH
      if (buttonState3 == HIGH) {
        string4.noteOn(349.23*x,velocity);
        //string4.noteOn(146.83,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState3 = reading3;

  int reading4 = digitalRead(stringPin5);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading4 != lastButtonState4) {
    // reset the debouncing timer
    lastDebounceTime4 = millis();
  }

  if ((millis() - lastDebounceTime4) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

      // only toggle the LED if the new button state is HIGH
      if (buttonState4 == HIGH) {
        string5.noteOn(392*x,velocity);
        //string5.noteOn(110,1);
      }
      
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState4 = reading4;
    int reading5 = digitalRead(stringPin6);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading5 != lastButtonState5) {
    // reset the debouncing timer
    lastDebounceTime5 = millis();
  }

  if ((millis() - lastDebounceTime5) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading5 != buttonState5) {
      buttonState5 = reading5;

      // only toggle the LED if the new button state is HIGH
      if (buttonState5 == HIGH) {
        string6.noteOn(440*x,velocity);
        //string6.noteOn(110,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState5 = reading5;
    int reading6 = digitalRead(stringPin7);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading6 != lastButtonState6) {
    // reset the debouncing timer
    lastDebounceTime6 = millis();
  }

  if ((millis() - lastDebounceTime6) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading6 != buttonState6) {
      buttonState6 = reading6;

      // only toggle the LED if the new button state is HIGH
      if (buttonState6 == HIGH) {
        string7.noteOn(493.88*x,velocity);
        //string7.noteOn(110,1);
      }
    }
  }

  // set the LED:

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState6 = reading6;
   }
   }
