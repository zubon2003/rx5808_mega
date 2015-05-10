//周波数からPLLに書き込む値を計算するサブルーチン
//計算方法はデータシート参照のこと
uint32_t calcChannelRegister(uint32_t channelFreq)
{
    uint32_t freq;
    uint32_t flo;
    uint32_t n;
    uint32_t a;
    uint32_t freq_registor;
    freq = constrain(channelFreq,5000,6000);//5000-6000MHZの間で設定する。
    flo = freq -479;
    n = flo / 64;
    a = (flo - (n * 64)) / 2;
    freq_registor = (n << 7) + a;
    return(freq_registor);
}

//現在のRSSIを取得するサブルーチン
//5V arduinoでは、0-5vの間を 0-1023の値に変換
//RTC6715のRSSIは 0.5v-1.1vの間で出力
//なので、生のrssi値は102-225位になる（大体）
uint16_t readRSSI(uint8_t module) 
{
    uint16_t rssi = 0;
    for (uint8_t i = 0; i < 10; i++) 
    {
        rssi += analogRead(rssiPin[module - 1]);
    }
    rssi=rssi/10; // 10回測定する平均値
    return(rssi);
}

//周波数を引数にしてPLLに周波数を設定するサブルーチン
void setChannelModule(uint8_t moduleID,uint16_t channelFreq)
{
  uint8_t address = 1;
  uint32_t channelData;
  channelData = calcChannelRegister(channelFreq);
  moduleWriteRegister(moduleID,address,channelData);
}
void moduleWriteRegister(uint8_t moduleID,uint8_t address,uint32_t registerData)
{
  int i;
  serialEnable(moduleID);

  // Register 0x1
    for (i = 4; i > 0; i--)
  {
    serialSendBit(address & 0x1);
    // Shift bits along to check the next one
    address >>= 1;
  }
  
  // Write mode
  serialSendBit(1);

  // D0-D19
  for (i = 20; i > 0; i--)
  {
    serialSendBit(registerData & 0x1);
    // Shift bits along to check the next one
    registerData >>= 1;
  }

  // Finished clocking data in
  serialDisable(moduleID);
  delayMicroseconds(1);
  digitalWrite(spiDataPin, LOW);
}


void serialSendBit(uint8_t bit)
{
  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);
  if (bit == 0) digitalWrite(spiDataPin, LOW);
  else digitalWrite(spiDataPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(spiClockPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(spiClockPin, LOW);
  delayMicroseconds(1);
}

void serialEnable(uint8_t moduleID)
{
  delayMicroseconds(1);
  digitalWrite(slaveSelectPin[moduleID - 1], LOW);
  delayMicroseconds(1);
}

void serialDisable(uint8_t moduleID)
{
  delayMicroseconds(1);
  digitalWrite(slaveSelectPin[moduleID - 1], HIGH);
  delayMicroseconds(1);
}
