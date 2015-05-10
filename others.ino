void freqselect()
{
      uint8_t button = 99;
      uint8_t channel;
      uint8_t x;
      uint8_t y;

      initFreqSelectDisplay();
      channel = getChannel(ACTUAL_FREQ);
      y = channel / 8;
      x = channel % 8;
      displayFreqSelectFreq(x,y,1);

  while (1)
  {
      if (upButtonPushed()) 
      {
        displayFreqSelectFreq(x,y,0);
        if (channel <=7) channel = channel + 24;
        else channel = channel - 8;
        y = channel / 8;
        x = channel % 8;
        displayFreqSelectFreq(x,y,1);
      }
      if (downButtonPushed()) 
      {
        displayFreqSelectFreq(x,y,0);
        if (channel >=24) channel = channel - 24;
        else channel = channel + 8;
        y = channel / 8;
        x = channel % 8;
        displayFreqSelectFreq(x,y,1);
      }
      if (leftButtonPushed()) 
      {
        displayFreqSelectFreq(x,y,0);
        if (channel % 8 == 0) channel = channel + 7;
        else channel = channel -1;
        y = channel / 8;
        x = channel % 8;
        displayFreqSelectFreq(x,y,1);
      }
      if (rightButtonPushed()) 
      {
        displayFreqSelectFreq(x,y,0);
        if (channel % 8 == 7) channel = channel - 7;
        else channel = channel +1;
        y = channel / 8;
        x = channel % 8;
        displayFreqSelectFreq(x,y,1);
      }
      if (cancelButtonPushed()) 
      {
        FORCE_REDRAW = true;
        return;
      }
      if (enterButtonPushed()) 
      {
        ACTUAL_FREQ = channelFreqTable[channel];
       FORCE_REDRAW = true;
        return;
      }
  }
}


void rssisetup()
{
        uint8_t i = 0;
        uint8_t y = 1;
        uint16_t rssimax = (EEPROM.read(0) << 8) + EEPROM.read(1);
        uint16_t rssimin = (EEPROM.read(2) << 8) + EEPROM.read(3);
        uint16_t initfreq = (EEPROM.read(4) << 8) + EEPROM.read(5);
        uint8_t rssithreshold = EEPROM.read(6);
        uint8_t channel;
        uint16_t tempfreq;

	clearRawRssi();


        FORCE_REDRAW = false;
        
	initRssiSetupDisplay();
        myGLCD.setColor(255, 255, 255);
        myGLCD.setBackColor(0, 0, 0);
        myGLCD.setFont(BigFont);
        myGLCD.printNumI(rssimax,16*22,16*8);
        if (rssimin > 99) myGLCD.printNumI(rssimin,16*22,16*10);
        else {
              myGLCD.print(" ",16*22,16*10);
              myGLCD.printNumI(rssimin,16*23,16*10);
              }
        myGLCD.printNumI(rssithreshold,16*23,16*12);
        myGLCD.printNumI(initfreq,16*21,16*14);
        drawSetupFrame(y);
        myGLCD.setColor(255, 0, 0);
        myGLCD.drawLine(0, 100 - rssithreshold, 479, 100 - rssithreshold);
        myGLCD.setColor(255, 255, 255);
        tempfreq = ACTUAL_FREQ;
        ACTUAL_FREQ = initfreq; 
        channel = getSortedChannel(ACTUAL_FREQ);
        ACTUAL_FREQ = tempfreq;
	setChannelModule(1,sortedChannelFreqTable[channel]);
        
    while (1)
    {
          if (enterButtonPushed()) 
          {
            if (rssimax != (EEPROM.read(0) << 8) + EEPROM.read(1)  ||
                rssimin != (EEPROM.read(2) << 8) + EEPROM.read(3)  ||
                initfreq != (EEPROM.read(4) << 8) + EEPROM.read(5) ||
                rssithreshold != EEPROM.read(6))
                 {
                    writeEeprom(rssimax,rssimin,initfreq,rssithreshold);
                    myGLCD.setColor(0, 0, 0);
                    myGLCD.setBackColor(255, 255, 255);
                    myGLCD.print("                ",16*1,16*16);
                    myGLCD.print("   S A V E D    ",16*1,16*17);
                    myGLCD.print("                ",16*1,16*18);
                    delay(1000);
                    myGLCD.setColor(255, 255, 255);                    
                    myGLCD.setBackColor(0, 0, 0);
                    myGLCD.print("                ",16*1,16*16);
                    myGLCD.print("                ",16*1,16*17);
                    myGLCD.print("                ",16*1,16*18);                    
                 }
            else
                {
                    myGLCD.setColor(0, 0, 0);
                    myGLCD.setBackColor(255, 255, 255);
                    myGLCD.print("                ",16*1,16*16);
                    myGLCD.print("  NOT CHANGED   ",16*1,16*17);
                    myGLCD.print("                ",16*1,16*18);
                    delay(1000);
                    myGLCD.setColor(255, 255, 255);                    
                    myGLCD.setBackColor(0, 0, 0);
                    myGLCD.print("                ",16*1,16*16);
                    myGLCD.print("                ",16*1,16*17);
                    myGLCD.print("                ",16*1,16*18);   
                }
          }
          if (cancelButtonPushed()) 
          {
            FORCE_REDRAW = true;
            ACTUAL_MENU = 0;
            return;
          }
          if (upButtonPushed()) 
          {
            eraseSetupFrame(y);
            y--;
            if (y == 0) y = 4;
            drawSetupFrame(y);
          }
          if (downButtonPushed()) 
          {
            eraseSetupFrame(y);
            y++;
            if (y == 5) y = 1;
            drawSetupFrame(y);
          }
          if (leftButtonPushed()) 
          {
          switch(y)
           {
             case 1:
               if (rssimax == 200) rssimax = 300;
               else rssimax--;
               myGLCD.printNumI(rssimax,16*22,16*8);
               delay(50);
               break;
             case 2:
               if (rssimin == 50) rssimin = 150;
               else rssimin--;
               
               if (rssimin > 99) myGLCD.printNumI(rssimin,16*22,16*10);
               else {
                      myGLCD.print(" ",16*22,16*10);
                      myGLCD.printNumI(rssimin,16*23,16*10);
                    }
               delay(50);
               break;
             case 3:
               myGLCD.setColor(0, 0, 0);
               myGLCD.drawLine(0, 100 - rssithreshold, 479, 100 - rssithreshold);
               if (rssithreshold == 1) rssithreshold = 99;
               else rssithreshold--;
               myGLCD.setColor(255, 0, 0);
               myGLCD.drawLine(0, 100 - rssithreshold, 479, 100 - rssithreshold);
               myGLCD.setColor(255, 255, 255);
               if (rssithreshold > 9) myGLCD.printNumI(rssithreshold,16*23,16*12);
               else {
                      myGLCD.print(" ",16*23,16*12);
                      myGLCD.printNumI(rssithreshold,16*24,16*12);
                    }
               delay(50);
             break;
             case 4:
               if (channel == 0) channel = 31;
               else channel--;
               initfreq = sortedChannelFreqTable[channel];
               myGLCD.printNumI(initfreq,16*21,16*14);
               delay(50);
            }
          }
          if (rightButtonPushed()) 
          {
           switch(y)
           {
             case 1:
               if (rssimax == 300) rssimax = 200;
               else rssimax++;
               myGLCD.printNumI(rssimax,16*22,16*8);
               delay(50);
               break;
             case 2:
               if (rssimin == 150) rssimin = 50;
               else rssimin++;
               
               if (rssimin > 99) myGLCD.printNumI(rssimin,16*22,16*10);
               else {
                     myGLCD.print(" ",16*22,16*10);
                     myGLCD.printNumI(rssimin,16*23,16*10);
                    }
               delay(50);
               break;
             case 3:
               myGLCD.setColor(0, 0, 0);
               myGLCD.drawLine(0, 100 - rssithreshold, 479, 100 - rssithreshold);
               if (rssithreshold == 99) rssithreshold = 1;
               else rssithreshold++;
               myGLCD.setColor(255, 0, 0);
               myGLCD.drawLine(0, 100 - rssithreshold, 479, 100 - rssithreshold);
               myGLCD.setColor(255, 255, 255);
               if (rssithreshold > 9) myGLCD.printNumI(rssithreshold,16*23,16*12);
               else {
                      myGLCD.print(" ",16*23,16*12);
                      myGLCD.printNumI(rssithreshold,16*24,16*12);
                    }
               delay(50);
             break;
             case 4:
               if (channel == 31) channel = 0;
               else channel++;
               initfreq = sortedChannelFreqTable[channel];
               myGLCD.printNumI(initfreq,16*21,16*14);
               delay(50);
            }
          }

               setChannelModule(2,sortedChannelFreqTable[i]);
               delay(30);
               RAW_RSSI[i] = readRSSI(2);
               RAW_RSSI[i] = constrain(RAW_RSSI[i],rssimin,rssimax);
               RAW_RSSI[i] = map(RAW_RSSI[i],rssimin,rssimax,0,100);
               monitorUpdateGraph(i,RAW_RSSI[i]);
               if (i == 31) i = 0;
               else i++;
            
    }
}

void rssiview()
{
  uint16_t j = 0;
  uint16_t rssi[401];
  uint16_t freq = ACTUAL_FREQ;
  uint8_t state = 0;
  uint8_t freq_change = 0;
  initRssiView();
  while(1)
  {
    if (enterButtonPushed())
    {
      for(uint16_t i = 5600 ;i <= 6000 ;i++)
      {
        if (cancelButtonPushed()) 
        {
          FORCE_REDRAW = true;
          ACTUAL_MENU = 0;
          return;
        }
        setChannelModule(2,i);
        delay(30);
        j=readRSSI(2);
        j = constrain(j,MIN_RSSI,MAX_RSSI);
        j= map(j,MIN_RSSI,MAX_RSSI,0,100);
        
        myGLCD.drawLine(i-5600+40,100,i-5600+40,100-j);
        rssi[i-5600] = j;
      }
      state = 1;
  }
  if (cancelButtonPushed()) 
  {
      FORCE_REDRAW = true;
      ACTUAL_MENU = 0;
      return;
  }
  if (upButtonPushed() && state == 1) 
  {
        myGLCD.drawLine(freq-5600+40,100,freq-5600+40,100-rssi[freq-5600]);
        if (freq > 5990) freq = 5600;
        else freq = freq + 10;
        freq_change = 1;
  }
  if (downButtonPushed() && state == 1) 
  {
        myGLCD.drawLine(freq-5600+40,100,freq-5600+40,100-rssi[freq-5600]);
        if (freq < 5610) freq = 6000;
        else freq = freq - 10;
        freq_change = 1;
  }
  if (leftButtonPushed() && state == 1) 
  {
        myGLCD.drawLine(freq-5600+40,100,freq-5600+40,100-rssi[freq-5600]);
        if (freq == 5600) freq = 6000;
        else freq = freq - 1;
        freq_change = 1;
  }
  if (rightButtonPushed() && state == 1) 
  {
        myGLCD.drawLine(freq-5600+40,100,freq-5600+40,100-rssi[freq-5600]);
        if (freq == 6000) freq = 5600;
        else freq = freq + 1;
        freq_change = 1;
  }
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(freq-5600+40,100,freq-5600+40,100-rssi[freq-5600]);
  myGLCD.setColor(255, 255, 255);
  if (freq_change == 1)
  {
    myGLCD.printNumI(freq, 16*8, 16*10+8);
    myGLCD.print("   ", 16*25, 16*10+8);
    if (rssi[freq-5600] == 100) myGLCD.printNumI(rssi[freq-5600], 16*25, 16*10+8);
    else if (rssi[freq-5600] > 9) myGLCD.printNumI(rssi[freq-5600], 16*26, 16*10+8);
    else myGLCD.printNumI(rssi[freq-5600], 16*27, 16*10+8);
    freq_change = 0;
  }
  }
}
void bandmonitor()
{
        uint8_t i = 0;
        uint8_t channel;
        uint8_t lostcount = 0;
	clearRawRssi();


        FORCE_REDRAW = false;
	initBandMonitorDisplay();
        channel = getSortedChannel(ACTUAL_FREQ);
	setChannelModule(1,sortedChannelFreqTable[channel]);
        myGLCD.setFont(BigFont);
        myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
        displayChannelMonitorFreq(channel,1);
    while (1)
    {
          if (enterButtonPushed()) 
          {
            freqselect();
            channel = getSortedChannel(ACTUAL_FREQ);
            setChannelModule(1,ACTUAL_FREQ);
            initBandMonitorDisplay();
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
            FORCE_REDRAW = false;
          }
          if (cancelButtonPushed()) 
          {
            FORCE_REDRAW = true;
            ACTUAL_MENU = 0;
            return;
          }
          if (upButtonPushed()) 
          {
            displayChannelMonitorFreq(channel,0);
            if (channel == 31) channel = 0;
            else channel ++;
            ACTUAL_FREQ = sortedChannelFreqTable[channel];
            setChannelModule(1,ACTUAL_FREQ);
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
          }
          if (downButtonPushed()) 
          {
            displayChannelMonitorFreq(channel,0);
            if (channel == 0) channel = 31;
            else channel --;
            ACTUAL_FREQ = sortedChannelFreqTable[channel];
            setChannelModule(1,ACTUAL_FREQ);
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
          }


               setChannelModule(2,sortedChannelFreqTable[i]);
               delay(30);
               RAW_RSSI[i] = readRSSI(2);
               RAW_RSSI[i] = constrain(RAW_RSSI[i],MIN_RSSI,MAX_RSSI);
               RAW_RSSI[i] = map(RAW_RSSI[i],MIN_RSSI,MAX_RSSI,0,100);
               monitorUpdateGraph(i,RAW_RSSI[i]);
               if (i == 31) i = 0;
               else i++;            
    }
}

void autotune()
{
        uint8_t i = 0;
        uint8_t channel;
        uint8_t lostcount = 0;
        uint8_t led[32];
	clearRawRssi();


        FORCE_REDRAW = false;
	initBandMonitorDisplay();
        channel = getSortedChannel(ACTUAL_FREQ);
	setChannelModule(1,sortedChannelFreqTable[channel]);
        myGLCD.setFont(BigFont);
        myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
        displayChannelMonitorFreq(channel,1);
    while (1)
    {
          if (enterButtonPushed()) 
          {
            freqselect();
            channel = getSortedChannel(ACTUAL_FREQ);
            setChannelModule(1,ACTUAL_FREQ);
            initBandMonitorDisplay();
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
            FORCE_REDRAW = false;
          }
          if (cancelButtonPushed()) 
          {
            FORCE_REDRAW = true;
            ACTUAL_MENU = 0;
            return;
          }
          if (upButtonPushed()) 
          {
            displayChannelMonitorFreq(channel,0);
            if (channel == 31) channel = 0;
            else channel ++;
            ACTUAL_FREQ = sortedChannelFreqTable[channel];
            setChannelModule(1,ACTUAL_FREQ);
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
          }
          if (downButtonPushed()) 
          {
            displayChannelMonitorFreq(channel,0);
            if (channel == 0) channel = 31;
            else channel --;
            ACTUAL_FREQ = sortedChannelFreqTable[channel];
            setChannelModule(1,ACTUAL_FREQ);
            myGLCD.setFont(BigFont);
            myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
            displayChannelMonitorFreq(channel,1);
          }

               
               setChannelModule(2,sortedChannelFreqTable[i]);
               delay(30);
               RAW_RSSI[i] = readRSSI(2);
               RAW_RSSI[i] = constrain(RAW_RSSI[i],MIN_RSSI,MAX_RSSI);
               RAW_RSSI[i] = map(RAW_RSSI[i],MIN_RSSI,MAX_RSSI,0,100);
               monitorUpdateGraph(i,RAW_RSSI[i]);
               if (i == 31) i = 0;
               else i++;
          
          
          //現在モニタ中のRSSIが5%以下だったら、32ch中MAXのチャンネルにモニタチャンネルを変更する。
         if (RAW_RSSI[channel] < RSSI_THRESHOLD) lostcount++;
         else lostcount = 0;
         if (lostcount > 20)
         {
           displayChannelMonitorFreq(channel,0);
           channel = getMaxRssi();
           ACTUAL_FREQ = sortedChannelFreqTable[channel];
           setChannelModule(1,ACTUAL_FREQ);
           myGLCD.setFont(BigFont);
           myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
           displayChannelMonitorFreq(channel,1);
         }
         
//         //現在のモニタしてるチャンネルと前後のチャンネルを比較して、RSSIが前後のチャンネルの方が良好なら、チャンネルずらす。
//         
//         //現在のチャンネルより一つ前のチャンネルの方がRSSIがよければ、前のチャンネルに移る
//         //現在のチャンネルが5645 5665 5685 5705 5725 5905 5925 5945MHzならこの動作の対象外
//
//         if (channel > 5 && channel < 30)
//           {
//             if (RAW_RSSI[channel] < RAW_RSSI[channel-1])
//               {
//                 displayChannelMonitorFreq(channel,0);
//                 channel = channel - 1;
//                 ACTUAL_FREQ = sortedChannelFreqTable[channel];
//                 setChannelModule(1,ACTUAL_FREQ);
//                 myGLCD.setFont(BigFont);
//                 myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
//                 displayChannelMonitorFreq(channel,1);
//               }
//           }
//         
//         //現在のチャンネルより一つ後のチャンネルの方がRSSIがよければ、後のチャンネルに移る
//         //5645 5665 5685 5705 5885 5905 5925 5945MHzならこの動作の対象外
//
//         if (channel > 4 && channel < 29)
//           {
//             if (RAW_RSSI[channel] < RAW_RSSI[channel+1])
//               {
//                 displayChannelMonitorFreq(channel,0);
//                 channel = channel + 1;
//                 ACTUAL_FREQ = sortedChannelFreqTable[channel];
//                 setChannelModule(1,ACTUAL_FREQ);
//                 myGLCD.setFont(BigFont);
//                 myGLCD.printNumI(sortedChannelFreqTable[channel], 16*21+8, 16*11);
//                 displayChannelMonitorFreq(channel,1);
//               }
//           }
           
         //スキャンしたRSSIからLEDを光らせる
        for(int i=0;i<32;i++) led[getChannel(sortedChannelFreqTable[i])] = RAW_RSSI[i];
        for(int i=0;i<32;i++) pixels.setPixelColor(i, pixels.Color(led[i],0,0));
        pixels.show();
  
 }
}
uint8_t getMaxRssi()
{
  uint8_t maxrssi = 0;
  uint8_t maxrssichannel = 0;
    for (uint8_t i = 0;i<32;i++)
    {
      if (RAW_RSSI[i] > maxrssi)
        {
          maxrssi = RAW_RSSI[i];
          maxrssichannel = i;
        }
    }
  return(maxrssichannel);
}
void monitorUpdateGraph(uint8_t rssi,uint16_t rssibar)
{ 
   rssibar=100 - rssibar;
   myGLCD.setColor(0, 0, 0);
   myGLCD.fillRect(rssi*15+3,0,rssi*15+3+4,100);
   myGLCD.setColor(255, 255, 255);
   myGLCD.fillRect(rssi*15+3,rssibar,rssi*15+3+4,100);
   myGLCD.setColor(255, 255, 255);
   myGLCD.setBackColor(0,0, 0);
}
//




void clearRawRssi()
{
		for(uint8_t i=0;i<=31;i++) RAW_RSSI[i] = 0;
}


void sortChannel()
{
  uint16_t temp;
  for (uint8_t i = 0;i<32 ;i++) sortedChannelFreqTable[i] = channelFreqTable[i];
  
  for (uint8_t i = 0;i<31 ;i++)
  {
    for (uint8_t j = 0;j<31-i ;j++)
      {
        if (sortedChannelFreqTable[j] > sortedChannelFreqTable[j+1])
           {
            temp =  sortedChannelFreqTable[j+1];
            sortedChannelFreqTable[j+1] = sortedChannelFreqTable[j];
            sortedChannelFreqTable[j] = temp;
           }
      }
  }
}
uint8_t getSortedChannel(uint16_t freq)
{
    for (uint8_t i = 0;i<32;i++)
    {
      if (sortedChannelFreqTable[i] == freq)
        {
          return(i);
          break;
        }
    }
}
uint8_t getChannel(uint16_t freq)
{
    for (uint8_t i = 0;i<32;i++)
    {
      if (channelFreqTable[i] == freq)
        {
          return(i);
          break;
        }
    }
}
void writeDefaultEeprom()
{
  writeEeprom(maxRssiDefault,minRssiDefault,initFreqDefault,rssiThresholdDefault);
}
void writeEeprom(uint16_t maxRssi,uint16_t minRssi,uint16_t initFreq,uint8_t rssiThreshold)
{  
  uint8_t checksum = 0;
  EEPROM.write(0,highByte(maxRssi));
  EEPROM.write(1,lowByte(maxRssi));
  EEPROM.write(2,highByte(minRssi));
  EEPROM.write(3,lowByte(minRssi));
  EEPROM.write(4,highByte(initFreq));
  EEPROM.write(5,lowByte(initFreq));
  EEPROM.write(6,rssiThreshold);
  for (uint8_t i=0; i<= 6; i++) checksum = checksum + EEPROM.read(i); //XOR CHECKSUM
  EEPROM.write(7,checksum);
}
uint8_t readEeprom()
{
  uint8_t temp[7];
  uint8_t checksum = 0;
  for (uint8_t i=0; i<= 6; i++) 
    {
      temp[i] = EEPROM.read(i);
      checksum = checksum + EEPROM.read(i);
    }
  if (checksum == EEPROM.read(7))
  {
    MAX_RSSI = (temp[0] << 8)+ temp[1];
    MIN_RSSI = (temp[2] << 8) + temp[3];
    ACTUAL_FREQ = (temp[4] << 8) + temp[5];
    RSSI_THRESHOLD = temp[6];
  }
  else return(0);
}
