#include "All_Fun.h"
int getcom= 0;

void setup() 
{  
  
  Serial.begin(9600);
  //myVR.begin(9600);
  //Serial.begin(115200);

  
  myservo.attach(3);  // attach servo on pin 3 to servo object  
  pinMode(IN1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  stop();
  irrecv.enableIRIn(); 
  //sim808.begin(9600);

  //getGPS(1000,true);
  //sendmessage("sai ram");
  while(getcom<=0)
  {  
    getcom= Serial.read();
    //Serial.println(getcom);
  }
}

void loop() 
{  
   //sim808.println("AT+CSQ");
   //read(1000,true);

   //read(1000,true);
   //Serial.println(ring);
    
    switch(getcom){
    case '1': Remote_Fun(); Serial.println("Remote mode on."); break;
    case '2': Voice_Fun(); Serial.println("Voice mode on.");break;//voice
    case '3': GSM_Fun(); Serial.println("GSM mode on.");break;
    case '4': Bluetooth_Fun(); break;
    case '5': comeback(); break;
    default: break;
     }
    
}
