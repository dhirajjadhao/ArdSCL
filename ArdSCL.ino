/*

        ARDUINO SERIAL CONTROL LIBRARY OR ArdSCL  VERSION 1.0
                   Copyright 2014 Dhiraj Jadhao

  This Library works with All arduino compatible boards.
  Maximum 100 boards can be controlled at a time using this library.
  
  Logic:
  
  * Using this library you can control Arduino completely.
  * Once you upload this code to arduino, you just have to send ArdSCL Protocol
    to get desired output.
  
  * ArdSCL Protocol can be used in following way to control Arduino

    ArdSCL protocol is a String of 12 characters as follows.
  
    xx  +  xxx +  x  +  x  +  x  +  xxxx
   |--|   |---|  |-|   |-|   |-|   |----|

   xx : [1st two chracter are :Device ID]

   xxx : [3rd 4th and 5th are for :Pin Number either from 000 to 999 OR from A00 to A99]

   x : [6th is for :Pin Mode either I:input  OR  O:output]
   
   x : [7th is for :Pin Type  D:digital, A:analog, S:Servo Function]
   
   x : [8th is for : Pin Option  R:read,  W:write]
   
   xxxx: [9th 10th 11th and 12th are for: Pin Value:  for digitalWrite: 0001 or 0000.  for analogWrite: 0000 to 0255.  for ServoFunction:  0000 to 0180]


  If you want to Read any of the analog or digital Pin then leave last 4 chracters in the Protocol as 0000, as it doesn't matter and Analog value of the Pin will be Serially Printed.


   Example:  If you want to turm on the LED on 13th pin of Arduino then protocol will be
      
             Protocol:  00013ODW0001
             
             In above protocol:
             
             00 - Device ID
             013 - Pin Number
             O - Pin Mode Output
             D - Pin Type Digital
             W -  Pin Option Write
             0001 - Pin Value 0001 = 1 = HIGH
             
             
             In this way you can control arduino as you wish according your Protocol.



 **Arduino Serial Control Library (ArdSCL) by Dhiraj Jadhao is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.
 ** More details about this library can be found at:
 ** http://ardscl.blogspot.com 

 ** Email: dhirajjadhao@gmail.com

*/

#include <Servo.h> 

int Device_Id = 00;       //  Chnage to specify your Device ID ranging from 00 to 99
int Pin_No;               //  Stores Pin Number starting either from 000 to 999 OR from A00 to A999
char Pin_Mode = ' ';      //  Stores Pin Mode I:Input, O:Output// I or O
char Pin_Type = ' ';      //  Stores Pin Type  D:Digital, A:Analog ,S:Servo Function  // D A S00013ODW0001
char Pin_Option = ' ';    //  Stores Pin Option  R:Read, W:Write
int Pin_Value;            //  Stores Pin Value 0001 or 0000 for digital, 0000 to 1023 for Analog, 0000 to 0180 for Servo Function

int total_pins = 100;     // Total number of Pins available on board. Default Value is 100 which can be changed to desied number

int Pin_No1, Pin_No2, Id;

/////////////////


char val[2];

/////////////////


char Input_Buffer[11];
Servo servo[30];

void setup()
{
Serial.begin(9600);

for(int i=0;i<total_pins;i++)
{
pinMode(i,OUTPUT);
}

for(int i=0;i<total_pins;i++)
{
digitalWrite(i,LOW);
}

}


void loop()
{

  while(Serial.available() == 12)
{
for(int i = 0;i< 12;i++)
{
Input_Buffer[i] = Serial.read();
}

//Serial.println(Input_Buffer);
Id = (Input_Buffer[0] - '0')*10 + (Input_Buffer[1] - '0'); //  Stores the Incoming Device Id Characters

if(Id  == Device_Id)
{
  
if(Input_Buffer[2] == 'A')
{
 val[0] = Input_Buffer[3]; 
 val[1] = Input_Buffer[4];  

Pin_No = (Input_Buffer[3] - '0')*10 + (Input_Buffer[4] - '0'); // Set Pin Number
//Serial.println(Pin_No);
}

else
{
Pin_No = (Input_Buffer[2] - '0')*100 + (Input_Buffer[3] - '0')*10 + (Input_Buffer[4] - '0'); // Set Pin Number
}



  Pin_Mode = Input_Buffer[5]; // Set PinMode(I/O/S)
 
  Pin_Type = Input_Buffer[6]; // Set Pin Type (Digital / Analog / Servo)
  
  Pin_Option = Input_Buffer[7]; // Set Pin Option as (R:Read or W:Write)

  Pin_Value = (Input_Buffer[8] - '0')*1000 + (Input_Buffer[9] - '0')*100 + (Input_Buffer[10] - '0')*10 + (Input_Buffer[11] - '0'); // Input Value to be written to specified Pin

 //Serial.println(Pin_No);
 
 //////////Setting PinMode///////////////
 
 if(Pin_Mode == 'I')
 {
 pinMode(Pin_No, INPUT);
 }
 
 else if(Pin_Mode == 'O')
 {
 pinMode(Pin_No, OUTPUT);
 
 }
 
  else if(Pin_Mode == 'S')
 {
  servo[Pin_No].attach(Pin_No);
 }
 ////////////////////////////////////////////
 
 //////////////Pin Type Digital ////////////
 if(Pin_Type == 'D' && Pin_Option == 'W')
 {
 digitalWrite(Pin_No,Pin_Value);
 }
 else if(Pin_Type == 'D' && Pin_Option == 'R')
 {
 int digistate = digitalRead(Pin_No);
 Serial.println(digistate);
 }
 //////////////////////////////////////////////
 
 
  //////////////Pin Type Analog ////////////
 if(Pin_Type == 'A' && Pin_Option == 'W')
 {
 analogWrite(Pin_No,Pin_Value);
 }
 else if(Pin_Type == 'A' && Pin_Option == 'R')
 {
 int anastate = analogRead(Pin_No);
 Serial.println(anastate); 
 }
 //////////////////////////////////////////////
 
 
  //////////////Pin Type Servo ////////////
 if(Pin_Type == 'S' && Pin_Option == 'W')
 {
   servo[Pin_No].write(Pin_Value);
 }

 ////////////////////////////////////////////// 
 
 
 
 
 
 
 }

Serial.flush();
delay(20);
}



}




  


