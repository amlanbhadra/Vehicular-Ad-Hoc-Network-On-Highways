#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const int zpin = A2;                  // z-axis (only on 3-axis models)

const byte rxAddr[6] = "00001";

void setup()
{
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  
   Serial.begin(9600);
}

void loop()
{
  char text[] = "!MH 31 0003@";
  radio.write(&text, sizeof(text));
 
 int z = analogRead(zpin);  //read from zpin
 
float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                      //ADXL335 power supply by Vs 3.3V
float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
                       //330 * 1024/3.3/1000  

int z1 = (((float)z - 340)/68*9.8);
if(z1 > 2)
{
   char text[] = "#0$";
  radio.write(&text, sizeof(text));
}
else 
{
  char text[] = "#1$";
   radio.write(&text, sizeof(text));
  
}

delay(1000);
  
 
}
