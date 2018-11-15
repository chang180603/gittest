//------w5500-------- 
#include <SPI.h>
#include <Ethernet2.h>
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 50, 177);
String data_cmd="";
char data_id;
boolean read_start=false;
boolean read_stop=false;
boolean cmd=false;
EthernetServer server(80);

//------------------------腳位定義
/*
int Motor_In1[] = {4,6,8,10,12};
int Motor_In2[] = {5,7,9,11,13};
*/

int Motor_In1[] = {2,4,6,8,12};
int Motor_In2[] = {3,5,7,9,13};

int Light_Blocking[] = {30,28,26,24,22};
int Emergency_Switch = 32;

//-------------------------
int Open_Num[5];
int Close_Num[5];
int Opening[5]={0,0,0,0,0};
int light_blocking_val;
int light_blocking_door_num;
int door_status;
int query_id;
unsigned long door_stop_time[5];
boolean Error = false;
boolean Id_error = false;
boolean Light_Block;
boolean EMS = false;                          //Emergency_Switch;
boolean Block_Buffer = true;
//------------------------------
#include <Timer.h>
Timer readcmd;
Timer readbottom;

//-----------------------------
#include <Bounce.h>
Bounce bouncer = Bounce( Emergency_Switch,30); 
//-----------------------------

void setup(){
     while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    
    
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    
    Serial.begin(9600);
    for(int i=0;i<=4;i++)
    {
      pinMode(Motor_In1[i],OUTPUT);
      pinMode(Motor_In2[i],OUTPUT);
      pinMode(Light_Blocking[i],INPUT_PULLUP);
    }
      pinMode(Emergency_Switch,INPUT);  
      readcmd.every(100,eth);
      readbottom.every(150,bottom_press);
}


void loop(){
  readcmd.update();
  readbottom.update();
  
 // Serial.print(digitalRead(!Emergency_Switch));
  Serial.print("EMS :");
  Serial.println(EMS);
  if (EMS == true)                                     //緊急開關被按壓
  {
    all_door_stop();
  }
  else
  {
    for(int i=0;i<=4;i++)
    {
      if (Opening[i]==0)
      {
        if  (Open_Num[i]==1)
        {
          //Serial.print(digitalRead(Light_Blocking[3]));
        door_open(i);
        }
      }
      else if (Opening[i]==1)
      {  
        //Serial.print(digitalRead(Light_Blocking[3]));
        /*
        Serial.print("millis : ");
        Serial.println(millis());
        Serial.print("door_stop_time");
        Serial.print(i);
        Serial.print(" : ");
        Serial.print(door_stop_time[i]);
        */
         if (Close_Num[i]==1)      //門到90度後  開啟超過x分鐘自動關閉   (millis ＝ 現在時間)
         {
           door_close(i);
         }
         else if (millis() - door_stop_time[i] > 6*1000*2)
         {
           door_close(i);
         }
      }            
    }
  }
}
