#include <Adafruit_NeoPixel.h>
#define PEDAL_BUTTON 0
#define PIN 4 //Pin for NeoPixels 
#define NUM_OF_LEDS 4

//Max pot values for 3.3v will be 675
#define MAX_POT 675

//Max pot values for 5.0v will be 1024
//#define MAX_POT 1024

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int Knob1 = A0;  // Left Pot
int Knob2 = A1;  // Right Pot

int max_pot = MAX_POT;

unsigned int Knob1_new = 0; // the latest pot value being read in
unsigned int Knob2_new = 0;
unsigned int Knob1_old = 0; // the old pot value which will be compared with the new value.
unsigned int Knob2_old = 0; //     I'm looking to see if there is a difference between these 
unsigned int Button_Press = 0;//      In order to determine if I should change the display or not.
unsigned int num = 0; 
unsigned int counter = 0; 
bool change; 

//I'm using this value for now just to keep the light somewhat dim while I proto this
float myIntensity = .02; //2% brightness 

typedef struct {
  int R;
  int G;
  int B;
} RGB;
  
RGB color;

void setup(){
  pinMode(PEDAL_BUTTON, INPUT);
  color = {0, 0, 0};
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  Knob1_Input();
  Knob2_Input();
  SetPixels();
  Time_delay();
  delay(10);
}

void Knob1_Input(){
  Knob1_new = 0.9 * Knob1_new + 0.1 * analogRead(Knob1);
    if(Knob1_new != Knob1_old){
        change = true; // Change is registered 
        counter = 0;
       }

   if(Knob1_new == Knob1_old){
    change = false;
   }
   
      if (change == true) {
        counter = 0;
         if(Knob1_new <= 15)                                                           { Off();}
             else if((Knob1_new > 15)             && (Knob1_new <= (max_pot/4)))       { Blue(); num = 1;}
             else if((Knob1_new > (max_pot/4))   && (Knob1_new <= (max_pot/2)))        { Blue(); num = 2;}
             else if((Knob1_new > (max_pot/2))   && (Knob1_new <= (max_pot/4)*3))      { Blue(); num = 3;}
             else if((Knob1_new > (max_pot/4)*3) && (Knob1_new <= (max_pot)))          { Blue(); num = 4;}  
      }

      else {
         counter++; 
      }

   Knob1_old = Knob1_new;     
}


void Knob2_Input(){
  Knob2_new = 0.9 * Knob2_new + 0.1 * analogRead(Knob2);
    if(Knob2_new != Knob2_old){
        change = true; // Change is registered 
        counter = 0;
       }

   if(Knob2_new == Knob2_old){
    change = false;
   }
   
      if (change == true) {
        counter = 0;
         if(Knob2_new <= 15)                                                           { Off();}
             else if((Knob2_new > 15)             && (Knob2_new <= (max_pot/4)))       { Green(); num = 1;}
             else if((Knob2_new > (max_pot/4))   && (Knob2_new <= (max_pot/2)))        { Green(); num = 2;}
             else if((Knob2_new > (max_pot/2))   && (Knob2_new <= (max_pot/4)*3))      { Green(); num = 3;}
             else if((Knob2_new > (max_pot/4)*3) && (Knob2_new <= (max_pot)))          { Green(); num = 4;}  
      }

      else {
         counter++; 
      }

   Knob2_old = Knob2_new;     
}

void Time_delay() {
  if( counter == 250){
    for (int j = 0; j <= 4; j++){
        Off();
        num = j;
        SetPixels();
      }
      
      counter = 0;
      change = false;
      Serial.println("Reset Counter");
      delay(800);
   }
}

void Blue() {
  color.R = color.G = 0, color.B = 250;
}

void Green() {
  color.R = color.B = 0, color.G = 250;
}

void Off(){
  color.R = color.G = color.B = 0; num = 0;
}

void SetPixels(){
  SetLED(strip.Color(color.R * myIntensity, color.G * myIntensity, color.B * myIntensity), 0, num); 
}

void SetLED(uint32_t c, uint8_t wait, int x) {
  int y = x;
  for (uint16_t i = 0; i <= x; ++i) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(y, strip.Color(0,0,0));   
    strip.show();
  }
}

