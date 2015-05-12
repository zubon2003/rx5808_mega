void initRssiSetupDisplay()
{
  myGLCD.clrScr();
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.setFont(BigFont);
    myGLCD.print("     100% RAW RSSI", 16*2, 16*8);
    myGLCD.print("       0% RAW RSSI", 16*2, 16*10);
    myGLCD.print("AUTOTUNE THRESHOLD", 16*2, 16*12);
    myGLCD.print("INITILAL FREQUENCY      MHz", 16*2, 16*14);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("    ", 16*19, 16*16);
    myGLCD.print("BACK", 16*19, 16*17);
    myGLCD.print("    ", 16*19, 16*18);
    myGLCD.print("    ", 16*25, 16*16);
    myGLCD.print("SAVE", 16*25, 16*17);
    myGLCD.print("    ", 16*25, 16*18);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
}
void drawSetupFrame(uint8_t y)
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0,0);
  myGLCD.drawRect(8,16*8+32*(y-1)-8,472,16*8+32*(y-1)+16);
}
void eraseSetupFrame(uint8_t y)
{
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);
  myGLCD.drawRect(8,16*8+32*(y-1)-8,472,16*8+32*(y-1)+16);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0,0);
}

void initRssiView()
{
  myGLCD.clrScr();
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);

  for (uint16_t i = 5600;i<=6000;i = i + 20)
  {
    displayRssiViewFreq(i);
  }
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.setFont(BigFont);
    myGLCD.print("      MHz  RSSI =    %", 16*7, 16*10+8);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("   ", 16* 8, 16*12);
    myGLCD.print(" + ", 16* 8, 16*13);
    myGLCD.print("   ", 16* 8, 16*14);
    myGLCD.print("   ", 16* 8, 16*16);
    myGLCD.print(" - ", 16* 8, 16*17);
    myGLCD.print("   ", 16* 8, 16*18);
    myGLCD.print("   ", 16* 4, 16*14);
    myGLCD.print(" < ", 16* 4, 16*15);
    myGLCD.print("   ", 16* 4, 16*16);
    myGLCD.print("   ", 16*12, 16*14);
    myGLCD.print(" > ", 16*12, 16*15);
    myGLCD.print("   ", 16*12, 16*16);
    myGLCD.print("    ", 16*19, 16*14);
    myGLCD.print("MENU", 16*19, 16*15);
    myGLCD.print("    ", 16*19, 16*16);
    myGLCD.print("    ", 16*25, 16*14);
    myGLCD.print("SCAN", 16*25, 16*15);
    myGLCD.print("    ", 16*25, 16*16);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
}
void displayRssiViewFreq(uint16_t freq)
{
  String str1;
  String str2;


  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0, 0);

  myGLCD.setFont(SmallFont); 
  str1 = String(freq,DEC);
  str2=str1.substring(0,1);
  myGLCD.print(str2, freq-5600+40-6, 110);
  str2=str1.substring(1,2);
  myGLCD.print(str2, freq-5600+40-6, 110+12);
  str2=str1.substring(2,3);
  myGLCD.print(str2, freq-5600+40-6, 110+24);
  str2=str1.substring(3,4);
  myGLCD.print(str2, freq-5600+40-6, 110+36); 
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0, 0);
  myGLCD.setFont(BigFont);
}
void initBandMonitorDisplay()
{
  myGLCD.clrScr();
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);

  for (uint8_t i = 0;i<32;i++)
  {
    displayChannelMonitorFreq(i,0);
  }
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.setFont(BigFont);
    myGLCD.print("MONITOR =     MHz", 16*12, 16*11);
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("   ", 16* 8, 16*12);
    myGLCD.print(" + ", 16* 8, 16*13);
    myGLCD.print("   ", 16* 8, 16*14);
    myGLCD.print("   ", 16* 8, 16*16);
    myGLCD.print(" - ", 16* 8, 16*17);
    myGLCD.print("   ", 16* 8, 16*18);
    myGLCD.print("   ", 16* 4, 16*14);
    myGLCD.print(" < ", 16* 4, 16*15);
    myGLCD.print("   ", 16* 4, 16*16);
    myGLCD.print("   ", 16*12, 16*14);
    myGLCD.print(" > ", 16*12, 16*15);
    myGLCD.print("   ", 16*12, 16*16);
    myGLCD.print("    ", 16*19, 16*14);
    myGLCD.print("MENU", 16*19, 16*15);
    myGLCD.print("    ", 16*19, 16*16);
    myGLCD.print("    ", 16*25, 16*14);
    myGLCD.print("FREQ", 16*25, 16*15);
    myGLCD.print("    ", 16*25, 16*16);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
}
void displayChannelMonitorFreq(uint8_t freq,uint8_t color)
{
  String str1;
  String str2;
  if (color == 0)
  {

    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0,0, 0);
  }
  else
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.setBackColor(0,0,0);
  }
  myGLCD.setFont(SmallFont); 
  str1 = String(sortedChannelFreqTable[freq],DEC);
  str2=str1.substring(0,1);
  myGLCD.print(str2, freq*15+3, 100+8);
  str2=str1.substring(1,2);
  myGLCD.print(str2, freq*15+3, 116+8);
  str2=str1.substring(2,3);
  myGLCD.print(str2, freq*15+3, 132+8);
  str2=str1.substring(3,4);
  myGLCD.print(str2, freq*15+3, 148+8);  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0, 0);
  myGLCD.setFont(BigFont);
}
void initMenuDisplay()
{
  myGLCD.setFont(Inconsola);
  myGLCD.clrScr();
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);
  myGLCD.print("   BAND SCANNER   ",CENTER,16*3+1);
  myGLCD.print("     AUTOTUNE     ",CENTER,16*7+1);
  myGLCD.print("    RSSI  VIEW    ",CENTER,16*11+1);
  myGLCD.print("       SETUP      ",CENTER,16*15+1);
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(255,255,255);
  myGLCD.setBackColor(0 , 0, 0);
  myGLCD.print(VERSION,0,308);
}
uint8_t upButtonPushed()
{
  if ( digitalRead(upButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(upButtonPin) == LOW) return(1);
  }
  return(0);
}
uint8_t downButtonPushed()
{
  if ( digitalRead(downButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(downButtonPin) == LOW) return(1);
  }
  return(0);
}
uint8_t leftButtonPushed()
{
  if ( digitalRead(leftButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(leftButtonPin) == LOW) return(1);
  }
  return(0);
}
uint8_t rightButtonPushed()
{
  if ( digitalRead(rightButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(rightButtonPin) == LOW) return(1);
  }
  return(0);
}
uint8_t cancelButtonPushed()
{
  if ( digitalRead(cancelButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(cancelButtonPin) == LOW) return(1);
  }
  return(0);
}
uint8_t enterButtonPushed()
{
  if ( digitalRead(enterButtonPin) == LOW )
  {
    delay(100);
    if (digitalRead(enterButtonPin) == LOW) return(1);
  }
  return(0);
}
void drawMenuFrame(uint8_t y)
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0,0);
  myGLCD.drawRect(8,35+64*(y-1),470,55+64*(y-1)+39);
}
void eraseMenuFrame(uint8_t y)
{
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255,255, 255);
  myGLCD.drawRect(8,35+64*(y-1),470,55+64*(y-1)+39);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0,0,0);
}


void initFreqSelectDisplay()
{
  myGLCD.clrScr();
  for (uint8_t x = 0; x<=7;x++)
  {
    for (uint8_t y = 0; y<=3;y++)
    {
      displayFreqSelectFreq(x,y,0);
    }
  }
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("   ", 16* 8, 16*12);
    myGLCD.print(" + ", 16* 8, 16*13);
    myGLCD.print("   ", 16* 8, 16*14);
    myGLCD.print("   ", 16* 8, 16*16);
    myGLCD.print(" - ", 16* 8, 16*17);
    myGLCD.print("   ", 16* 8, 16*18);
    myGLCD.print("   ", 16* 4, 16*14);
    myGLCD.print(" < ", 16* 4, 16*15);
    myGLCD.print("   ", 16* 4, 16*16);
    myGLCD.print("   ", 16*12, 16*14);
    myGLCD.print(" > ", 16*12, 16*15);
    myGLCD.print("   ", 16*12, 16*16);
    myGLCD.print("    ", 16*19, 16*14);
    myGLCD.print("BACK", 16*19, 16*15);
    myGLCD.print("    ", 16*19, 16*16);
    myGLCD.print("    ", 16*25, 16*14);
    myGLCD.print(" OK ", 16*25, 16*15);
    myGLCD.print("    ", 16*25, 16*16);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
}
void displayFreqSelectFreq (uint8_t x,uint8_t y,uint8_t color)
{
  String str1;
  String str2=" ";
  String str3=" ";
  uint8_t channel;
  channel = x + y * 8;
  if (color == 0)
  {
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255,255,255);
  }
  else
  {
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255,0,0);
  }
  myGLCD.setFont(BigFont);
  str1 = String(channelFreqTable[channel],DEC);
  str2=str1.substring(0,2);
  myGLCD.print(str2, 8+60*x, 8+48*y);
  str2=str1.substring(2,4);
  myGLCD.print(str2, 8+60*x, 24+48*y);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
}


void initDiversityDisplay()
{
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setFont(BigFont);
  myGLCD.print("FREQ = ", 0, 0);
  myGLCD.printNumI(ACTUAL_FREQ, 112, 0);
  myGLCD.print("Mhz", 192, 0);
  myGLCD.print("MODULE 1", 0, 24);
  myGLCD.print("MODULE 2", 0, 48);
  myGLCD.print("MODULE 3", 0, 72);
    for (uint8_t i = 0;i<32;i++)
    {
      displayChannelMonitorFreq(i,0);
    }
  
    myGLCD.setColor(0, 0, 0);
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.print("   ", 16* 8, 16*12);
    myGLCD.print(" + ", 16* 8, 16*13);
    myGLCD.print("   ", 16* 8, 16*14);
    myGLCD.print("   ", 16* 8, 16*16);
    myGLCD.print(" - ", 16* 8, 16*17);
    myGLCD.print("   ", 16* 8, 16*18);
    myGLCD.print("   ", 16* 4, 16*14);
    myGLCD.print(" < ", 16* 4, 16*15);
    myGLCD.print("   ", 16* 4, 16*16);
    myGLCD.print("   ", 16*12, 16*14);
    myGLCD.print(" > ", 16*12, 16*15);
    myGLCD.print("   ", 16*12, 16*16);
    myGLCD.print("    ", 16*19, 16*14);
    myGLCD.print("MENU", 16*19, 16*15);
    myGLCD.print("    ", 16*19, 16*16);
    myGLCD.print("    ", 16*25, 16*14);
    myGLCD.print("FREQ", 16*25, 16*15);
    myGLCD.print("    ", 16*25, 16*16);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
  
}
