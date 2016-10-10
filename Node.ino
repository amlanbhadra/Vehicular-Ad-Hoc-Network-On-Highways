#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
char text1[32] = {0};
char text2[32] = {0};
const byte rxAddr[6] = "00001";

int carno;

int Tstatus;

int car1;
int car2;
int car3;
int count1;
void setup()
{
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
}

void loop()
{
 
  char text[32] = {0}; 
  
  if (radio.available())
  {
   radio.read(&text, sizeof(text));
   for(int i=0; i<=sizeof(text);i++)
   {
     if(text[0]=='!')
        text1[i]=text[i];
    else break;
   }
  }
  
  if(text[0]=='#')
 { 
   if(text[1]=='1')
   {
     if(text[2]=='$')
     {
       Serial.print("Accident Detected-MH 31 0003" ); 
     }
   }
 }

 
 if(text[0]=='!')
 { 
   if(text2[10]!=text1[10])
   {
      Serial.print("Square = " );                          
  Serial.print(" Shankar Nagar");   
    Serial.print(" | " );  
    
      Serial.print("Cars = " );  
 
 if(text[0]=='!')      
  Serial.print(text);  
  
     Serial.println(' ' ); 
     count1++;

}
}


 if(text[0]=='!')
{
  if(text[10]=='1')
    car1=1;
    if(text[10]=='2')
    car2=1;
    if(text[10]=='3')
    car3=1;  
  }    
 
 if(count1==3)
  {
    carno=car1+car2+car3;
    car1=0;
    car2=0;
    car3=0;
    count1=0;
    
      Serial.print("No of Cars = " );                          
  Serial.print(carno);   
    Serial.print(" | " );  
    
      Serial.print("Status= " );  
  if(carno==3)      
  Serial.print("over traffic "); 
else   
Serial.println("Normal traffic "); 
   
    
}
 

 for(int i=0; i<=sizeof(text1);i++)
   {
    text2[i]=text1[i];
   }

   

}
