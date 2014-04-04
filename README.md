ArdSCL : Arduino Serial Control Library
=======================================

ArdSCL, lets you control Arduino over Serial.

ArdSCL library works with all arduino compatible board. It uses ArdSCL protocol which is a string of 12 chracters.

## ArdSCL Protocol

Format of Protocol:   
                      XX        -- XXX        -- X        -- X       -- X          -- XXX

  Device ID -- Pin Number -- Pin Mode --Pin Type -- Pin Option -- Pin Value

#Device ID:

1st and 2nd characters XX:  Specify Device ID

So device id can be anything from 00 to 99 and can be changed in the ArdSCL sketch, so whatever device id you specify on your sketch while uploading that sketch to your arduino board, your board will get that Device ID and then it can be identified by the Device ID.

#Pin Number:

3rd, 4th and 5th characters XXX: Specify Pin Number.

Three character space is given for specifying pin number.

For Digital Pin: It can take values from 000 to 999 (Must be valid for your board.)
* It means if you want to specify Pin2 then it will be written as 002. If you want to use pin 13 then it will be written as 013.

For Analog Pin: It can take values form A00 to A99(Must be valid for your board.)
* It means if you want to read Analog Pin2 then it must be specified as A02 or if you want to read Analog Pin13 then must be specified as A13.


#Pin Mode:

6th character X: Specify Pin Mode.

If you want to set pinMode as Input then it should be specified as "I".
And if you want to set pinMode as Output then it should be specified as "O".


#Pin Type:


7th character X: Specify Pin Type.

If you want to set pin type as Digital then it should be specified as "D".
If you want to set pin type as Analog then it should be specified as "A".
If you want to set pin type as Servo pin then it should be specified as "S".


#Pin Option:

8th character X: Specify Pin Option.

If you want to Read Pin then it must be specified as "R".
If you want to Write Pin then it must be specified as "W".


#Pin Value:

9th, 10th, 11th, 12th characters XXXX: Specify Pin value.


For digitalWrite it must be specified as: 0001 or 0000  (HIGH or LOW).

For analogWrite it must be specified as: 0000 or 0255.

For Servo Function it must be specified as: 0000 or 0180.


If you want to Read any of the Analog or Digital Pin then leave last 4 chracters in the Protocol as 0000, as it doesn't matter and Analog or Digital value of the Pin will be Serially Printed.

Example:

If you want to turm on the LED on 13th pin of Arduino then protocol will be
    
                  Protocol:  00013ODW0001 -- Turns ON pin 13
                                  00013ODW0000 -- Turns OFF pin 13
            
             In above protocol:
            
             00 - Device ID
             013 - Pin Number
             O - Pin Mode Output
             D - Pin Type Digital
             W -  Pin Option Write
             0001 - Pin Value 0001 = 1 = HIGH
            

Library comes with standard sketch, once you upload the code to the board you will get its full control over Serial.

