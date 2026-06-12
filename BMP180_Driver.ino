int diagnosis = 1;
int raw_temp = 1;
int raw_pressure = 1;
int pressure_delay = 26;
int OSS = 2;
long B5;
uint16_t oss = 0x80;  
uint8_t msb = 0;
uint8_t lsb = 0;
uint8_t xlsb = 0;

// calibration coefficients
int16_t AC1 = 7763;
int16_t AC2 = -1153;      
int16_t AC3 = -14366;     
uint16_t AC4 = 34948;
uint16_t AC5 = 25196;
uint16_t AC6 = 18950;
int16_t BMP_B1 = 6515;
int16_t B2 = 44;
int16_t MB = -32768;       
int16_t MC = -11786;      
int16_t MD = 2701;

void setup()
{
  TWCR |= (1<<TWEN);
  TWBR = 0x08;
  TWSR &= 0xFC;     
  Serial.begin(9600);  
}

void START()
{
 TWCR |= (1<<TWINT);
 TWCR |= (1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t START_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(START_status == 0x08)
  {
   Serial.println("Communication started!");
  }
  else
  {
  Serial.println("START error!");
  }
  }
}
void Re_START()
{
 TWCR |= (1<<TWINT);
 TWCR |= (1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t START_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(START_status == 0x08)
  {
   Serial.println("Communication re-started!");
  }
  else
  {
   Serial.println("Re_START error!");
  }
 }
}
void SLA_W()
{
 TWDR = 0xEE;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t SLA_W_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(SLA_W_status == 0x18)
  {
   Serial.println("SLA_W begins!");
  }

  else
  {
   Serial.println("SLA_W error!");
   Serial.println(SLA_W_status,HEX);
  }
 }
}
void control_reg_write()
{
 TWDR = 0xF4;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t control_reg_status = TWSR&0xF8;

 if(diagnosis == 1)
 {
  if(control_reg_status == 0x28)
  {
   Serial.println("control reg address has been written!");
  }
  else
  {
   Serial.println("control reg address has not been written error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void temp_reading_write()
{
 TWDR = 0x2E;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t temp_read_start = TWSR&0xF8;

 if(diagnosis)
 {
  if(temp_read_start == 0x28)
  {
   Serial.println("Temp data address has been written!");
  }
  else
  {
   Serial.println("Temp data address has not been written error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void pressure_reading_write()
{
 TWDR = 0x34|oss;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t pressure_read_start = TWSR&0xF8;

 if(diagnosis)
 {
  if(pressure_read_start == 0x28)
  {
   Serial.println("Pressure data address has been written!");
  }
  else
  {
   Serial.println("Pressure data address has not been written error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void REPEATED_START()
{
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  while(!(TWCR & (1<<TWINT)));

  uint8_t status = TWSR & 0xF8;

  if(diagnosis)
  {
    Serial.print("Repeated START status = 0x");
    Serial.println(status, HEX);
  }
}
void SLA_W_repeated()
{
 TWDR = 0xEE;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t SLA_W_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(SLA_W_status == 0x18)
  {
   Serial.println("SLA_W_repeated begins!");
  }

  else
  {
   Serial.println("SLA_W_repeated error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void control_reg_write_repeated()
{
 TWDR = 0xF6;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t control_reg_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(control_reg_status == 0x28)
  {
   Serial.println("control reg repeated address has been written!");
  }
  else
  {
   Serial.println("control reg repeated address has not been written error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void SLA_R()
{
 TWDR = 0xEF;
 TWCR |= (1<<TWINT);
 TWCR &= ~(1<<TWSTA);
 while(!(TWCR&(1<<TWINT)));
 uint8_t SLA_R_status = TWSR&0xF8;

 if(diagnosis)
 {
  if(SLA_R_status == 0x40)
  {
   Serial.println("SLA_R begins!");
  }
  else
  {
   Serial.println("SLA_R error!");
   Serial.print("Status = 0x");
   Serial.println(TWSR & 0xF8, HEX);
  }
 }
}
void temp_SLA_data_read()
{
  TWCR |= (1<<TWINT);
  TWCR |= (1<<TWEA);

  while(!(TWCR & (1<<TWINT)));
  uint8_t msb_status = TWSR & 0xF8;

  if(msb_status == 0x50)
  {
    if(diagnosis)
     {
      Serial.println("MSB received!");
     }
  }
  else
  {
    if(diagnosis)
     {
      Serial.println("MSB receiving error!");
      Serial.print("Status = 0x");
      Serial.println(msb_status, HEX); 
     }
  }
  msb = TWDR;

  TWCR |= (1<<TWINT);
  TWCR &= ~(1<<TWEA);

  while(!(TWCR & (1<<TWINT)));
  uint8_t lsb_status = TWSR & 0xF8;

  if(lsb_status == 0x58)
  {
   if(diagnosis)
   {
    Serial.println("LSB received!");
   }
  }
  else
  { 
    if(diagnosis)
    {
     Serial.println("LSB receiving error!");
     Serial.print("Status = 0x");
     Serial.println(lsb_status, HEX);
    }
  }
  lsb = TWDR;

  uint16_t UT = ((uint16_t)msb << 8) | lsb;
  if(raw_temp)
  {
    Serial.print("Raw Temperature = ");
    Serial.println(UT);
  }
  long X1 = ((long)(UT - AC6) * AC5) / 32768;
  if(diagnosis)
   {
    Serial.println(X1);
   }
  long X2 = ((long)MC * 2048) / (X1 + MD);
   if(diagnosis)
    {
     Serial.println(X2);
    }
  B5 = X1+X2;
   if(diagnosis)
    {
     Serial.println(B5);
    }
  long temp = (B5+8)/16;
  Serial.print("Temperature: ");
  Serial.println(temp*0.1);  
}
void pressure_SLA_data_read()
{
 

  TWCR |= (1<<TWINT);
  TWCR |= (1<<TWEA);

  while(!(TWCR & (1<<TWINT)));

  uint8_t msb_status = TWSR & 0xF8;

  if(msb_status == 0x50)
  {
    if(diagnosis)
      Serial.println("MSB received!");
  }
  else
  {
    if(diagnosis)
    {
      Serial.println("MSB receiving error!");
      Serial.print("Status = 0x");
      Serial.println(msb_status, HEX);
    }
  }

  msb = TWDR;

  TWCR |= (1<<TWINT);
  TWCR |= (1<<TWEA);

  while(!(TWCR & (1<<TWINT)));

  uint8_t lsb_status = TWSR & 0xF8;

  if(lsb_status == 0x50)
  {
    if(diagnosis)
      Serial.println("LSB received!");
  }
  else
  {
    if(diagnosis)
    {
      Serial.println("LSB receiving error!");
      Serial.print("Status = 0x");
      Serial.println(lsb_status, HEX);
    }
  }

  lsb = TWDR;

  TWCR &= ~(1<<TWEA);
  TWCR |= (1<<TWINT);

  while(!(TWCR & (1<<TWINT)));

  uint8_t xlsb_status = TWSR & 0xF8;

  if(xlsb_status == 0x58)
  {
    if(diagnosis)
      Serial.println("XLSB received!");
  }
  else
  {
    if(diagnosis)
    {
      Serial.println("XLSB receiving error!");
      Serial.print("Status = 0x");
      Serial.println(xlsb_status, HEX);
    }
  }

  xlsb = TWDR;

  uint32_t UP =
  ((((uint32_t)msb << 16) |
    ((uint32_t)lsb << 8)  |
     (uint32_t)xlsb) >> (8 - OSS));

  if(diagnosis)
  {
    if(raw_pressure)
    {
      Serial.print("Raw Pressure (UP) = ");
      Serial.println(UP);
    }
    
  }

  long B6 = B5 - 4000;
  long X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
  long X2 = (AC2 * B6) >> 11;
  long X3 = X1 + X2;
  long B3 = ((((long)AC1 * 4 + X3) << OSS) + 2) >> 2;
  X1 = (AC3 * B6) >> 13;
  X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  uint32_t B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
  uint32_t B7 = ((uint32_t)UP - B3) * (50000 >> OSS);
  long pressure;
  if(B7 < 0x80000000)
  {
    pressure = (B7 << 1) / B4;
  }
  else
  {
    pressure = (B7 / B4) << 1;
  }
  X1 = (pressure >> 8) * (pressure >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * pressure) >> 16;
  pressure = pressure + ((X1 + X2 + 3791) >> 4);
  if(diagnosis)
  {
    Serial.print("Final Pressure (Pa) = ");
    Serial.println(pressure);
  }
  Serial.print("Pressure (hPa) = ");
  Serial.println(pressure / 100.0);
}
void STOP()
{
    TWCR |= (1<<TWSTO);
    while(TWCR & (1<<TWSTO));
    if(diagnosis == 1)
    { 
      Serial.println("Process stopped!");
    } 
}
void TWI()
{
  START();
  SLA_W();
  control_reg_write();
  temp_reading_write();
  STOP();

  delay(5);
  Re_START();
  SLA_W_repeated();
  control_reg_write_repeated();
  REPEATED_START();
  SLA_R();
  temp_SLA_data_read();
  STOP();  
 
 //pressure reading start
  START();
  SLA_W();
  control_reg_write();
  pressure_reading_write();
  STOP();

  delay(pressure_delay);
  Re_START();
  SLA_W_repeated();
  control_reg_write_repeated();
  REPEATED_START();
  SLA_R();
  pressure_SLA_data_read();
  STOP();
}
void loop()
{
  TWI();
}


