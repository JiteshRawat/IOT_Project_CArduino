#include <SoftwareSerial.h>
SoftwareSerial sim808(12,13);
void clearData();
double Distance();
void setGPS();
char phone[]="+919880364223";
String data[5]= {""};
double gps[2];
double la1= 0.00;
double lo1= 0.00;

String read(const int timeout ,bool debug)
{
  String response = "";
  long int time = millis();
  int i = 0;

  while ( (time+timeout ) > millis() )
  {
   // Serial.println("before available");
    while (sim808.available())
    { 
     char c = sim808.read();
     response +=c;
     //Serial.println("in available"+c);
    }
  }
  if (debug) 
  {
    Serial.print(response);
  }
  
  return response;
}

void getGPS(int timeout,bool debug)
{ 
  clearData();
  sim808.println("AT+CGNSPWR=1");
  sim808.flush();
  read(100,true);
  sim808.println("AT+CGNSSEQ=RMC");
  read(100,true);
  sim808.println("AT+CGNSINF");
  sim808.flush();
  long int time = millis();
  int i = 0;

  while ( (time+timeout ) > millis() )
  {
    while (sim808.available())
    {
     char c = sim808.read();
     if(c != ',')
        data[i] +=c;
     else
        i++;
     if (i == 5)
      break;
    }
    if (i == 5)
      break;
  }
  
    for(int j=1;j<i;j++)
    {
      Serial.println(data[j]);
    }
    

   setGPS();
   return;
}


void setGPS()
{
  gps[0]= data[3].toDouble();
  gps[1]= data[4].toDouble();
  return;
}

String sendmessage(String msg)
{
  sim808.println("AT+CSMP=17,167,0,0");
  sim808.println("AT+CMGF=1");
  sim808.print("AT+CMGS=\"");
  sim808.print(phone);
  sim808.println("\"");
  delay(300);
  sim808.print(msg);
  delay(200);
  sim808.println((char)26);
  delay(200);
  sim808.flush();
  read(100,true);
}

String readmessage()
{
  sim808.println("AT+CMGF=1");
  read(100,true);
  sim808.println("AT+CMGR=1");
  read(1000,true);
  sim808.print("AT+CMGL=\"");
  sim808.print("ALL");
  sim808.println("\"");
  read(1000,true);
  sim808.flush();
}

void clearData()
{
  for(int i= 0; i < 5; i++)
    data[i]= "";
}

#define DTOR 0.0174532925199432957f
#define RTOD 57.295779513082320876f
double locs[4];
double d= 0.0;
double angle= 0.0;
double reald= 0.0;
double count=1.0;
int temp= 0;

double Distance()
{
  
  const double R = 6371000; // km  
  double l1= locs[0]*DTOR;
  double l2= locs[0]*DTOR;
  double dla= (locs[2]-locs[0])*DTOR;
  double dlo= (locs[3]-locs[1])*DTOR;

  double x= sin(dla/2) * sin(dla/2) + cos(l1) * cos(l2) * sin(dlo/2) * sin(dlo/2);
  double y= 2* atan2(sqrt(x),sqrt(1-x));
  d= R*y;
  
/////////////////////////////////////////     ANGLE     /////////////////////////////////////////////////////////////////////////////////////////

  double a = sin(locs[3]-locs[1]) * cos(locs[2]);//y is a,x is b
  double b = cos(locs[0])*sin(locs[2]) - sin(locs[0])*cos(locs[2])*cos(locs[3]-locs[1]);
  angle= (atan2(a, b)) * RTOD;
  return(d); 
}
