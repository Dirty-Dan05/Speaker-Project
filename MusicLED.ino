#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            3
#define PIN2           5
#define PIN3           6
#define NUMPIXELS      8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
int analogPin=A0;
int strobePin=11;
int resetPin=10;
int spectrumValue[7];
int filter=80;

void setup(){
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH); 
  pixels.begin(); 
  pixels2.begin();
  pixels3.begin(); 
}

void loop(){
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (int i=0;i<7;i++){
    digitalWrite(strobePin, LOW);
    delay(30);
    spectrumValue[i]=analogRead(analogPin);
    spectrumValue[i]=constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i]=map(spectrumValue[i], filter, 1023, 0, 255);
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
    }
  Serial.println();
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    
    if (spectrumValue[6] > 35) {
      //pixels.setPixelColor(i, pixels.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6]));
      pixels.setPixelColor(i, pixels.Color(0,(spectrumValue[6] + 50),0));
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[6] = 0;
      //pixels.setPixelColor(i, pixels.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels.setPixelColor(i, pixels.Color(0,spectrumValue[6],0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }

    if (spectrumValue[4] > 50) {
    //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
    pixels2.setPixelColor(i, pixels2.Color(0,0,spectrumValue[4])); // Moderately bright green color.
    pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[4] = 0;
      //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels2.setPixelColor(i, pixels2.Color(0,0,spectrumValue[4])); // Moderately bright green color.
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }

    if (spectrumValue[1] > 80) {
    //pixels3.setPixelColor(i, pixels3.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
    pixels3.setPixelColor(i, pixels3.Color(255,0,0)); // Moderately bright green color.
    pixels3.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[1] = 0;
      //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels3.setPixelColor(i, pixels3.Color(spectrumValue[1],0,0)); // Moderately bright green color.
      pixels3.show(); // This sends the updated pixel color to the hardware.
    }

  }
  
}
