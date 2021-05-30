#include "GSMProject.h"
#include"Infra_Ultra_Car.h"
#include "VoiceRecognitionV3.h"
#include"Path.h"

struct path *r;

////////////////////////////////////////      GPS     //////////////////////////////////////////////////////////////////////////////////////////


int  GSM_Fun()
{
  // sim808.begin(9600);
   forward();
   while(true)
   {
     String ring= read(1000,true);
       if(ring=="RING")
           break;
        
      count++;
   }
   turnaround();
   while(true)
   { 
    
     getstr = Serial.read();
     if (irrecv.decode(&results))
     {
      val=results.value;
      irrecv.resume();
     }
     if( getstr== 's'|| val==16712445 || count<=0)
     {
      break;
     }
     count--;
  }
  stop();
  
  return("3");
}

//////////////////////////////////// Come Back Car   ////////////////////////////////////////////////////////////////////////////
int comeback()
{ 
  while(top!=NULL)
  {  r= top;        
    Serial.println(top->val); 
     
     if(top->val=='f')
      {
        forward();
        while(top->count>1.0)   
         {
          top->count--; 
          delay(1000);
         }    
      }
     else if(top->val=='b')
        {
          back();
          while(top->count>0.0)   
         {
          top->count--; 
          delay(1000);
         }
        }    
     else if(top->val=='l')
         { right(); delay(1000);}
     else if (top->val=='r')
          { left(); delay(1000);}

      top=top->next;
      free(r);
   }
   stop();
  return("4");
  
}
///////////////////////////////////////////   IRREMOTE    ///////////////////////////////////////////////////////////////////////////////////

int Remote_Fun()
{
  // Serial.println("remote mode on"); 
  if (irrecv.decode(&results))
   {  
      preMillis=millis();
      val=results.value;
      Serial.print(val);
      irrecv.resume();
      
       switch(val){
        case 16736925 : forward(); record('f',count);  break;
        case 16754775 : back();    record('b',count); break;  
        case 16720605 : left();   record('l',count); break;                          
        case 16761405 : right();  record('r',count);  break;
        case 16712445 : turnaround(); delay(1000);return comeback();  break;
        default: break;
      }
   }

    top->count++;
    delay(1000);
    Serial.println(top->count);
    return("1");
}
////////////////////////////////////////     VOICE       ///////////////////////////////////////////////////////////////////////////////////

VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.
uint8_t records[7]; // save record
uint8_t buf[64];
#define onRecord    (0)
#define offRecord   (1)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}


String printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

int Voice_Fun()
{
   myVR.begin(9600);
   Serial.begin(115200);
   Serial.println("I am in voice mode.");
   int ret;
   ret = myVR.recognize(buf, 50);
   if(ret>0){
    switch(buf[1]){
      case onRecord: forward(); break;
        /* move forward */
      case offRecord: stop(); break;
        /* stop the car*/
          
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
  return("2");
}


///////////////////////////////////   BLUETOOTH   ////////////////////////////////////////////////////////////////////////////////////////////

int Bluetooth_Fun()
{ 
    Serial.println("bluetooth mode on");
    getstr = Serial.read();
    switch(getstr){
    case 'f': forward();Serial.println("forward"); record('f',count); break;
    case 'b': back();   record('b',count);  break;
    case 'l': left();   record('l',count);  break;
    case 'r': right();  record('r',count);  break;
    case 's': stop();   break;
    case 'c': turnaround(); delay(1000); comeback(); break;
    default:  break;
  }
  top->count++;
   delay(1000);
  return("4");
}
