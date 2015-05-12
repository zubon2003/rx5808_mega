//LCD UTFT Library
#include <UTFT.h>
#include "EEPROM.h"
//LED Library
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

//UTFT Fonts
extern uint8_t Inconsola[];
extern uint8_t BigFont[];
extern uint8_t SmallFont[];

UTFT myGLCD(HX8357C,38,39,40,41);


String VERSION = "Ver. 0.81";

//PIN Assign
#define spiDataPin     66 //A12 RX5808のCH1に1kΩの抵抗つけて接続
#define spiClockPin    68 //A14 RX5808のCH3に1kΩの抵抗つけて接続
#define module1slaveSelectPin 57// A3 //RX5808のCH2に1kΩの抵抗つけて接続
#define module2slaveSelectPin 67 // A13
#define module1rssiPin        58 //A4 
#define module2rssiPin        69 //A15
#define lcdSerialPin           6 
#define leftButtonPin   8
#define upButtonPin     9
#define downButtonPin   10
#define rightButtonPin  11
#define cancelButtonPin 12
#define enterButtonPin  5

uint8_t MODULE_NUM = 2;

uint8_t slaveSelectPin[2]= {module1slaveSelectPin,module2slaveSelectPin};
uint8_t rssiPin[2]={module1rssiPin,module2rssiPin};

uint16_t RAW_RSSI[32];

boolean FORCE_REDRAW = false; 

uint8_t ACTUAL_MENU = 0;

uint8_t SELECTED_X = 0;
uint8_t SELECTED_Y = 0;

uint16_t channelFreqTable[32] = {
  5865,5845,5825,5805,5785,5765,5745,5725,
  5733,5752,5771,5790,5809,5828,5847,5866,
  5705,5685,5665,5645,5885,5905,5925,5945,
  5740,5760,5780,5800,5820,5840,5860,5880
};

uint16_t sortedChannelFreqTable[32];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32,lcdSerialPin, NEO_GRB + NEO_KHZ800);

 //EEPROMより設定
#define maxRssiDefault  261
#define minRssiDefault  110
#define initFreqDefault  5705
#define rssiThresholdDefault 10

uint16_t MAX_RSSI = maxRssiDefault;
uint16_t MIN_RSSI = minRssiDefault;
uint16_t ACTUAL_FREQ = initFreqDefault;
uint8_t RSSI_THRESHOLD = rssiThresholdDefault;



void setup() 
{
     
    myGLCD.InitLCD();
    
    Serial.begin(9600);
    
    //EEPROMより設定値読み込み
    if (readEeprom() == 0) writeDefaultEeprom();
    
    
    //BUTTONS
    pinMode (leftButtonPin,INPUT_PULLUP);
    pinMode (upButtonPin,INPUT_PULLUP);
    pinMode (downButtonPin,INPUT_PULLUP);
    pinMode (rightButtonPin,INPUT_PULLUP);
    pinMode (cancelButtonPin,INPUT_PULLUP);
    pinMode (enterButtonPin,INPUT_PULLUP);

    // SPI pins for RX control
    pinMode (spiDataPin, OUTPUT);
    pinMode (spiClockPin, OUTPUT);
    for (uint8_t i = 0; i < MODULE_NUM; i++) pinMode(slaveSelectPin[i],OUTPUT);
    
    sortChannel(); //Sort By Freqency Order
    
    
    initMenuDisplay();

    for (uint8_t i=1; i<= MODULE_NUM; i++) setChannelModule(i,ACTUAL_FREQ);
    
    pixels.begin(); //LCD INIT
    for(int i=0;i<32;i++) pixels.setPixelColor(i, pixels.Color(150,0,0));
    pixels.show();
    delay(1000);
    
    for(int i=0;i<32;i++) pixels.setPixelColor(i, pixels.Color(0,150,0));
    
    pixels.show();
    delay(1000);    
    
    for(int i=0;i<32;i++) pixels.setPixelColor(i, pixels.Color(0,0,150));
    pixels.show();
    delay(1000);
    
    for(int i=0;i<32;i++) pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    delay(1000);
 
}

void loop()
{
//    for(int i=0;i<32;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(100); // Delay for a period of time (in milliseconds).
//
//  }
   if (ACTUAL_MENU == 0) SELECTED_Y = 1;
   while(ACTUAL_MENU == 0)
   {
      if (upButtonPushed())
         {
          eraseMenuFrame(SELECTED_Y);
          SELECTED_Y--;
          if (SELECTED_Y == 0) SELECTED_Y = 4;
         }
      if (downButtonPushed())
         {
          eraseMenuFrame(SELECTED_Y);
          SELECTED_Y++;
          if (SELECTED_Y == 5) SELECTED_Y = 1;
         }
      if (enterButtonPushed()) ACTUAL_MENU = SELECTED_Y;
      drawMenuFrame(SELECTED_Y);
   }
   
  switch(ACTUAL_MENU)
   {
     case 1:
     bandmonitor();
     ACTUAL_MENU = 0;
     delay(100);
     break;
     case 2:
     autotune();
     ACTUAL_MENU = 0;
     delay(100);
     break;
     case 3:
     rssiview();
     ACTUAL_MENU = 0;
     delay(100);
     break;
     case 4:
     rssisetup();
     ACTUAL_MENU = 0;
     delay(100);
   }
   if (FORCE_REDRAW == true )
    {
      FORCE_REDRAW = false;  
      initMenuDisplay();
    }
}

