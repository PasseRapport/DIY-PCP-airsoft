#include <Servo.h>


#define valvePin 9
#define servoPin 6
#define triggerPin 12
#define safetyPin 7
#define fireSelectPin 8


#define boltOpen 135      //Theses are the angle values for the  servo
#define chamberLoaded 105 //
#define fire 85

Servo Servo;

void setup()
{
  
  pinMode(fireSelectPin,INPUT);
  pinMode(valvePin, OUTPUT);
  Servo.attach(servoPin);
  pinMode(triggerPin, INPUT);
 
}

void loop()
{

  while(digitalRead(safetyPin))
  {
    delay(100);
  }

  int fireMode = digitalRead(fireSelectPin);
  

  if(fireMode)               //FULL AUTO
  {
  
    if(digitalRead(triggerPin))
    {
      delay(150);
      Servo.write(fire);
      delay(100);
      digitalWrite(valvePin, HIGH);
      delay(20);                      //Valve open duration
      digitalWrite(valvePin, LOW);

      delay(150);                     //give time to the bullet to leave the cannon

      if(digitalRead(triggerPin))
      {
        Servo.write(boltOpen);        //faster cycle skipping the "chamerLoaded" state      
        delay(100);  
      }
      else
      {
        Servo.write(boltOpen);
        delay(150);
        Servo.write(chamberLoaded);
      }
    }
                             
  }
  else                         //SINGLE FIRE
  {
    if(digitalRead(triggerPin))
    {
      Servo.write(fire);
      delay(100);                       //adding a delay cause the servo is too slow
      digitalWrite(valvePin, HIGH);
      delay(20);                        //Valve open duration
      digitalWrite(valvePin, LOW);
      delay(100);
      Servo.write(90);
      delay(300);                        //give time to the bullet to leave the cannon

      Servo.write(140);
      delay(250);
      Servo.write(chamberLoaded);
      delay(300);
      while(digitalRead(triggerPin))
      {
        
      }
    }
  }
}