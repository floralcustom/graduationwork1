#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);    //RX, TX
#define Heart 2
#define LED 4
#define LED2 5
boolean beat = false; 

boolean led_state = LOW;
unsigned char counter;
unsigned long temp[6];   // = 5  
unsigned long sub;
bool data_effect=true;
unsigned int heart_rate;


const int max_heartpluse_duty = 2000;    // = 2sec
            

// int speakerpin = 6;


void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(Heart, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.println("Check your Pulse Sensor");
  delay(5000);
  arrayInit();
  Serial.println("Heart rate test begin.");
  attachInterrupt(0, interrupt, RISING);
}


void loop() {
/*
if(Serial.available()>0){
  char re = Serial.read();

  switch(re){
    case 'E' :
    start();
  }*/
}
  
  
}

/*function : heart rate calculate*/
void sum()
{
 if(data_effect)
    {
      heart_rate=300000/(temp[5]-temp[0]);   //TTIME   1200000 /20
      Serial.print("Heart_rate_is:\t");
      Serial.println(heart_rate);
      
      BTSerial.print("f");
      BTSerial.print(heart_rate);
    }
   data_effect=1;
}


/*function interrupt service */
void interrupt()
{
    temp[counter]=millis();
    //Serial.println(counter,DEC);
    //Serial.println(temp[counter]);
    switch(counter)
  {
    case 0:
      sub=temp[counter]-temp[5];
      Serial.println(sub);   //sub !!!
     // BTSerial.println(sub);
      break;
    default:
      sub=temp[counter]-temp[counter-1];
     Serial.println(sub);
    // BTSerial.println(sub);
      break;
  }
    if(sub>max_heartpluse_duty) //set 2 seconds
  {
    data_effect=0;//sign bit
    counter=0;
          
    Serial.println("Arrest\n");

    BTSerial.print("g");
    BTSerial.print("Arrest");
    arrayInit();
  }

  
    if (counter==5&&data_effect)
    {
    counter=0;
    sum();
    }
    else if(counter!=5&&data_effect)
    counter++;
    else 
    {
    counter=0;
    data_effect=1;
    }
    
}
/*Function: Initialization for the array(temp)*/
void arrayInit()
{
  for(unsigned char i=0;i < 5;i ++)
  {
    temp[i]=0;
  }
  temp[5]=millis();
}


/*
float floatMap(float x, float inMin, float inMax, float onMin, float onMax)
{
    return (x-inMin)-(onMax-onMin)/(inMax-inMin)+onMin;
}


void start(){
  while(1){
    Serial.print('s');
    Serial.print(floatMap(analogRead(Heart), 0, 1023, 0, 5 ),2);
    delay(20);

    if(Serial.available()>0){
      if(Serial.read()=='Q') return;
    }
  }
}
*/


