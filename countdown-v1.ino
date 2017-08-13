//
// julior@gmail.com
// 
//
//http://www.hobbytronics.co.uk/arduino-countdown-timer
//

#include <Adafruit_NeoPixel.h>
#define PIN            3
#define NUMPIXELS      40
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int val = 0;

int delayval = 100; // delay for half a second

                

int start_num = 3600;  // Number to countdown from

// 60 = 1 minute 
// 300 = 5 mintues
// 900 = 15 
// 1800 = 30
// 3600 = 1 hour

unsigned long time;

void setup() {
                                                          
  strip.begin(); // This initializes the NeoPixel library.
  //startShow(1);
//  startShow(2);
  startShow(3);
//  startShow(4);
//  startShow(5);
  
  Serial.begin(9600);
  Serial.println("light timer j2");


  ////
for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(0,0,80)); 
    strip.show(); 
    delay(delayval); 
    
  }

  ///
}


void loop() {
  
  // put your main code here, to run repeatedly:
  //long startTime = millis();
  
  if((millis()/1000) < start_num){
   // displayNumber(start_num -(millis()/1000));
   
  val = map(start_num -(millis()/1000), 0, start_num, 0, NUMPIXELS);
//  val = map((millis()/1000), 0, start_num, 0, NUMPIXELS);

  Serial.println(start_num -(millis()/1000));
  Serial.println(val);

  strip.setPixelColor(val, strip.Color(255,0,0));
  strip.show(); 

  
  }
  else {
    // reached zero, flash the display
    time=millis();
    while(millis() < time+200) {
      //displayNumber(0);  // display 0 for 0.2 second
      Serial.println("edddnnnn");
    startShow(5);
  
    }
    time=millis();    
    while(millis() < time+200) {
     //lightNumber(10);  // Turn display off for 0.2 second
    }
  }  
  // end countdown

   
 


  /// end void
}



///

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 70);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 70);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 70);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 70);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: 
    
    theaterChase(strip.Color(0,   0,   255), 50); // Red

    
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

