#include <Adafruit_NeoPixel.h>
#define PEDAL_BUTTON 0
#define PIN 4 //Pin for NeoPixels 
#define NUM_OF_LEDS 4

//Max pot values for 3.3v will be 675
#define MAX_POT 675

//Max pot values for 5.0v will be 1024
//#define MAX_POT 1024

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//Drive and Level are what brandon uses 
int Knob1 = A0;  // Left Pot
int Knob2 = A1;  // Right Pot

int max_pot = MAX_POT;

unsigned int Knob1_new = 0; // the latest pot value being read in
unsigned int Knob2_new = 0;
unsigned int Knob1_old = 0; // the old pot value which will be compared with the new value.
unsigned int Knob2_old = 0; //     I'm looking to see if there is a difference between these 
unsigned int Button_Press = 0;//      In order to determine if I should change the display or not.

//I'm using this value for now just to keep the light somewhat dim while I proto this
float myIntensity = .02;  //2% brightness 

typedef struct {
  int R;
  int G;
  int B;
  int intensity;
} RGB;
  
RGB color, colorPrime;

void setup()
{
  pinMode(PEDAL_BUTTON, INPUT);
  color = {0, 0, 0, 5};
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}


int Clamp(int x) {        //I'm not sure if I need this in yet or if I can take it out. 
  if (x < 0) 
  return 0;
  
  else if (x > 255)
  return 255;
  
  else 
  return x;
}

void loop() 
{
  Knob1_Input();
  Knob2_Input();
  strip.show();
}

void Knob1_Input(){
  Knob1_new = analogRead(Knob1);
  //Serial.print("New = ");
  //Serial.println(Knob1_new);

  //Serial.print("Old = ");
  //Serial.print(Knob1_old);
  // Try this out if my first idea doesn't work
     // if(((Knob1_new - Knob1_old) == 5) || ((Knob1_old - Knob1_new) == 5)){
   if((Knob1_new < Knob1_old)||(Knob1_new > Knob1_old)){
      if(Knob1_new <= 5)                                                   { strip.setPixelColor(0, strip.Color(0,0,0));  strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob1_new > 5)             && (Knob1_new <= (max_pot/4)))        { strip.setPixelColor(0, strip.Color(0,20,0)); strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob1_new > (max_pot/4))   && (Knob1_new <= (max_pot/2)))        { strip.setPixelColor(0, strip.Color(0,20,0)); strip.setPixelColor(1, strip.Color(0,20,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob1_new > (max_pot/2))   && (Knob1_new <= (max_pot/4)*3))      { strip.setPixelColor(0, strip.Color(0,20,0)); strip.setPixelColor(1, strip.Color(0,20,0)); strip.setPixelColor(2, strip.Color(0,20,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob1_new > (max_pot/4)*3) && (Knob1_new <= (max_pot)))          { strip.setPixelColor(0, strip.Color(0,20,0)); strip.setPixelColor(1, strip.Color(0,20,0)); strip.setPixelColor(2, strip.Color(0,20,0)); strip.setPixelColor(3, strip.Color(0,20,0));}
  }

  else {
   //  strip.setPixelColor(0, strip.Color(0,0,0));  strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));
  }
  
  Knob1_old = Knob1_new;
  delay(20);
}


void Knob2_Input(){
  Knob2_new = analogRead(Knob2);
  //Serial.print("New = ");
  //Serial.println(Knob2_new);

  //Serial.print("Old = ");
  //Serial.print(Knob2_old);
  // Try this out if my first idea doesn't work
     // if(((Knob2_new - Knob2_old) == 5) || ((Knob2_old - Knob2_new) == 5)){
   if((Knob2_new < Knob2_old)||(Knob2_new > Knob2_old)){
      if(Knob2_new <= 5)                                                   { strip.setPixelColor(0, strip.Color(0,0,0));  strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob2_new > 5)             && (Knob2_new <= (max_pot/4)))        { strip.setPixelColor(0, strip.Color(0,0,20)); strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob2_new > (max_pot/4))   && (Knob2_new <= (max_pot/2)))        { strip.setPixelColor(0, strip.Color(0,0,20)); strip.setPixelColor(1, strip.Color(0,0,20)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob2_new > (max_pot/2))   && (Knob2_new <= (max_pot/4)*3))      { strip.setPixelColor(0, strip.Color(0,0,20)); strip.setPixelColor(1, strip.Color(0,0,20)); strip.setPixelColor(2, strip.Color(0,0,20)); strip.setPixelColor(3, strip.Color(0,0,0));}
      if((Knob2_new > (max_pot/4)*3) && (Knob2_new <= (max_pot)))          { strip.setPixelColor(0, strip.Color(0,0,20)); strip.setPixelColor(1, strip.Color(0,0,20)); strip.setPixelColor(2, strip.Color(0,0,20)); strip.setPixelColor(3, strip.Color(0,0,20));}
  }

  else {
     //strip.setPixelColor(0, strip.Color(0,0,0));  strip.setPixelColor(1, strip.Color(0,0,0)); strip.setPixelColor(2, strip.Color(0,0,0)); strip.setPixelColor(3, strip.Color(0,0,0));
  }
  
  Knob2_old = Knob2_new;
  delay(20);
}


void SetPixels(){
  //Serial.println(colorPrime.intensity);
  SetLED(strip.Color(colorPrime.R * colorPrime.intensity*myIntensity, colorPrime.G * colorPrime.intensity*myIntensity, colorPrime.B * colorPrime.intensity*myIntensity), 0); 
}

void SetLED(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}




