 /* LCD RS pin to digital pin 10
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);
RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

void setup()
{
  radio.begin();

   lcd.begin(16,2);
  lcd.setCursor(5, 0);
  lcd.print("VANET");
}

void loop()
{
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  const char text[] = "!MH 31 0002@";
  radio.write(&text, sizeof(text));
  
  
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
    if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    
      if(text[0]=='#')
      {
        if(text[1]=='1')
        {
          if(text[2]=='$')
          {
           lcd.clear();
          lcd.print("Accident Nearby");
          lcd.setCursor(2, 1);
        lcd.print("MH 31 0003");
          delay(1000);
          }  
        }
      }    
    
    if(text[0]=='!')
    { 
      text[0]=' ';
      text[11]=' ';
      
       lcd.clear();
       lcd.setCursor(3, 0);
       lcd.print("Nearby Car");
       lcd.setCursor(2, 1);
        lcd.print(text);
        delay(100);
    }
    
  }
    delay(100);
}
