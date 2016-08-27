#include <Adafruit_NeoPixel.h>
#define PIN 4 //Pin for NeoPixels 
#define NUM_OF_LEDS 16

//Max pot values for 3.3v will be 675
#define MAX_POT 675

//Max pot values for 5.0v will be 1024
//#define MAX_POT 1024

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int pattern[16]= {0,1,2,3,4,11,12,13,14,15,8,7,6,5,10,9};
int Knob1 = A0;  // Left Pot
int Knob2 = A1;  // Right Pot
int max_pot = MAX_POT;

unsigned int Knob1_new = 0; // the latest pot value being read in
unsigned int Knob2_new = 0;
unsigned int Knob1_old = 0; // the old pot value which will be compared with the new value.
unsigned int Knob2_old = 0; //     I'm looking to see if there is a difference between these 
unsigned int LED_num = 0;
unsigned int counter = 0;
unsigned int counter2 = 0;
float step_amount = (max_pot/NUM_OF_LEDS);
int display_time = 150;

//I'm using this value for now just to keep the light somewhat dim while I proto this
float myIntensity = .04; //4% brightness 

typedef struct {
  int R;
  int G;
  int B;
} RGB;
  
RGB color;

void setup(){
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
  Serial.print("Counter = ");
  Serial.println(counter);
  Serial.print("Counter2 = ");
  Serial.println(counter2);
  delay(5);
}

void Knob1_Input(){
  Knob1_new = (0.9 * Knob1_new + 0.1 * analogRead(Knob1));    //This funny looking equation helps smooth out the Pot values so they are stable.
    if(Knob1_new != Knob1_old){
      for (int k = 1; k <= NUM_OF_LEDS; k++){
           if(Knob1_new <= step_amount) { Off();}  //Pot value for the very first step, if condition is met, the the whole set of lights are off
           else if((Knob1_new > (step_amount*k)) && (Knob1_new <= (step_amount*(k+1)))) { Blue(); LED_num = k;}  //Go through each possible step, and compare it with pot value, and turn on appropriate LED
      }
        counter = 0;      //If there is a change, the counter is reset
    }

    else{ //If pots aren't moved, then do nothing, except increase the counter for the time off delay. 
       counter++; 
    }
 Knob1_old = Knob1_new;
}


void Knob2_Input(){
  Knob2_new = (0.9 * Knob2_new + 0.1 * analogRead(Knob2));    //This funny looking equation helps smooth out the Pot values so they are stable.
    if(Knob2_new != Knob2_old){
      for (int k = 1; k <= NUM_OF_LEDS; k++){
           if(Knob2_new <= step_amount) { Off();}  //Pot value for the very first step, if condition is met, the the whole set of lights are off
           else if((Knob2_new > (step_amount*k)) && (Knob2_new <= (step_amount*(k+1)))) { Green(); LED_num = k;}  //Go through each possible step, and compare it with pot value, and turn on appropriate LED
      }
        counter2 = 0;      //If there is a change, the counter is reset
    }

    else{ //If pots aren't moved, then do nothing, except increase the counter for the time off delay. 
       counter2++; 
    }
 Knob2_old = Knob2_new;
}

void Time_delay() {
  if((counter == display_time)||(counter2 == display_time)){
    for (int j = 0; j <= NUM_OF_LEDS; j++){
        Off();
        LED_num = j;
        SetPixels();
      }  
      counter = 0;
      counter2 = 0;
   }
}

void Blue() {
  color.R = color.G = 0, color.B = 250;
}

void Green() {
  color.R = color.B = 0, color.G = 250;
}

void Off(){
  color.R = color.G = color.B = 0;
}

void SetPixels(){
  SetLED(strip.Color(color.R * myIntensity, color.G * myIntensity, color.B * myIntensity), 0, LED_num); 
}

void SetLED(uint32_t c, uint8_t wait, int x) {
  int y = x;
  for (uint16_t i = 0; i <= x; i++) {
    strip.setPixelColor(pattern[i], c);
    strip.setPixelColor(pattern[y], strip.Color(0,0,0));   
    strip.show();
  }
}

