#include "mbed.h"
#include "ros.h"
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt8.h>

ros::NodeHandle nh;

std_msgs::UInt8MultiArray U_msg;
ros::Publisher luggageLockStatus("luggageLockStatus", &U_msg);

Timeout unlock_timer;
Ticker msg_timer;
DigitalOut   relay_L(D6);
DigitalOut   relay_R(D5);
DigitalIn    limit_switch_L(A3);
DigitalIn    limit_switch_R(A4);
uint8_t data[2];
//int open_one=0;
//bool open_new=false;
//bool open_Left=false;
//bool open_Right=false;

void unlock_timeout()
{
    relay_L=0;
    relay_R=0;
    //bool open_Left=false;
    //bool open_Right=false;
    //open_new=false;
}

void msg_read_pub()
{
    nh.spinOnce();
    luggageLockStatus.publish( &U_msg );
}

void unlock(const std_msgs::UInt8 &unlock_msg)
{
    //----------------------------------------
    //單邊解鎖
    /*
    if(unlock_msg.data==0)
    {
    relay_L=1;
    }
    if(unlock_msg.data==1)
    {
    relay_R=1;
    }
    */
    //----------------------------------------
    relay_L=1;
    relay_R=1;
    unlock_timer.attach(&unlock_timeout, 10);
    //open_new=true;
}

ros::Subscriber<std_msgs::UInt8> sub("luggageUnlock", &unlock);

int main()
{
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(luggageLockStatus);
    U_msg.data_length=2;
    U_msg.data = data;

    msg_timer.attach(&msg_read_pub, 1);
    while(1)
    {
      U_msg.data[0]=!limit_switch_R;
      U_msg.data[1]=!limit_switch_L;
    //-----------------------------------------------------------------------------------
    //兩邊開鎖，直到下次再壓limit switch || 開啟10秒後 ，就鎖上
      /*
        if (open_new==false)
        {
        U_msg.data[0]=!limit_switch_R;
        U_msg.data[1]=!limit_switch_L;
        if (limit_switch_L==0)
        {#include "mbed.h"
#include "ros.h"
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt8.h>

ros::NodeHandle nh;

std_msgs::UInt8MultiArray U_msg;
ros::Publisher luggageLockStatus("luggageLockStatus", &U_msg);

Timeout unlock_timer;
Ticker msg_timer;
DigitalOut   relay_L(D6);
DigitalOut   relay_R(D5);
DigitalIn    limit_switch_L(A3);
DigitalIn    limit_switch_R(A4);
uint8_t data[2];
//int open_one=0;
//bool open_new=false;
//bool open_Left=false;
//bool open_Right=false;

void unlock_timeout()
{
    relay_L=0;
    relay_R=0;
    //bool open_Left=false;
    //bool open_Right=false;
    //open_new=false;
}

void msg_read_pub()
{
    nh.spinOnce();
    luggageLockStatus.publish( &U_msg );
}

void unlock(const std_msgs::UInt8 &unlock_msg)
{
    //----------------------------------------
    //單邊解鎖
    /*
    if(unlock_msg.data==0)
    {
    relay_L=1;
    }
    if(unlock_msg.data==1)
    {
    relay_R=1;
    }
    */
    //----------------------------------------
    relay_L=1;
    relay_R=1;
    unlock_timer.attach(&unlock_timeout, 10);
    //open_new=true;
}

ros::Subscriber<std_msgs::UInt8> sub("luggageUnlock", &unlock);

int main()
{
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(luggageLockStatus);
    U_msg.data_length=2;
    U_msg.data = data;

    msg_timer.attach(&msg_read_pub, 1);
    while(1)
    {
      U_msg.data[0]=!limit_switch_R;
      U_msg.data[1]=!limit_switch_L;
    //-----------------------------------------------------------------------------------
    //兩邊開鎖，直到下次再壓limit switch || 開啟10秒後 ，就鎖上
      /*
        if (open_new==false)
        {
        U_msg.data[0]=!limit_switch_R;
        U_msg.data[1]=!limit_switch_L;
        if (limit_switch_L==0)
        {
         relay_L=0;
        }
    
        if (limit_switch_R==0)
        {
         relay_R=0;
        }
        }
        while(open_new==true)
      {
        U_msg.data[0]=!limit_switch_R;
        U_msg.data[1]=!limit_switch_L;
        
        if (limit_switch_L==1)
        {    
            open_Left=true;
        }
        if (limit_switch_R==1)
        {    
            open_Right=true;
        }
        
        if (limit_switch_L==0 && open_Left==true)
        //if (limit_switch_L==0)
        {
            relay_L=0;
            open_Left=false;
        }
        if (limit_switch_R==0 && open_Right==true)
        {
            relay_R=0;
            open_Right=false;
        }
        
      }*/
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //兩邊開鎖，一邊拿開另一邊就鎖上
      /*
      while(limit_switch_L==1 || limit_switch_R==1 || open_one==1)
      {    
        if (limit_switch_L==0)
        {
         U_msg.data[0]=limit_switch_L;
         relay_L=0;
         open_one++;
        }
    
        if (limit_switch_R==0)
        {
          U_msg.data[1]=limit_switch_R;
         relay_R=0;
         open_one++;
        }
      }
      //open_one=0; 
      */
    //------------------------------------------------------------------------
      
    //U_msg.layout.dim_length=1;
    //U_msg.data_length=2;
    /*
    U_msg.layout.dim = (std_msgs::MultiArrayDimension *)
    malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
    U_msg.layout.dim[0].label="luggageLockStatus";
    U_msg.layout.dim[0].size = 5;
    U_msg.layout.dim[0].stride = 1*5;
    U_msg.layout.data_offset=0;
    */
    }
}
         relay_L=0;
        }
    
        if (limit_switch_R==0)
        {
         relay_R=0;
        }
        }
        while(open_new==true)
      {
        U_msg.data[0]=!limit_switch_R;
        U_msg.data[1]=!limit_switch_L;
        
        if (limit_switch_L==1)
        {    
            open_Left=true;
        }
        if (limit_switch_R==1)
        {    
            open_Right=true;
        }
        
        if (limit_switch_L==0 && open_Left==true)
        //if (limit_switch_L==0)
        {
            relay_L=0;
            open_Left=false;
        }
        if (limit_switch_R==0 && open_Right==true)
        {
            relay_R=0;
            open_Right=false;
        }
        
      }*/
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //兩邊開鎖，一邊拿開另一邊就鎖上
      /*
      while(limit_switch_L==1 || limit_switch_R==1 || open_one==1)
      {    
        if (limit_switch_L==0)
        {
         U_msg.data[0]=limit_switch_L;
         relay_L=0;
         open_one++;
        }
    
        if (limit_switch_R==0)
        {
          U_msg.data[1]=limit_switch_R;
         relay_R=0;
         open_one++;
        }
      }
      //open_one=0; 
      */
    //------------------------------------------------------------------------
      
    //U_msg.layout.dim_length=1;
    //U_msg.data_length=2;
    /*
    U_msg.layout.dim = (std_msgs::MultiArrayDimension *)
    malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
    U_msg.layout.dim[0].label="luggageLockStatus";
    U_msg.layout.dim[0].size = 5;
    U_msg.layout.dim[0].stride = 1*5;
    U_msg.layout.data_offset=0;
    */
    }
}
