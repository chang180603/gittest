void door_open(int i)
{
   
   motor_clockwise(i);
   if (Block_Buffer==true)
     {
     delay(300);
     Block_Buffer=false;
     Serial.println("op");
     }
     light_blocking(i);
     int ggg=0;
   if (Light_Block==true && light_blocking_door_num==i && ggg==1)
   {
     motor_stop(i);
     Block_Buffer=true;
     Open_Num[i]=0;
     Opening[i]=1;
     door_stop_time[i] = millis() ;                                //門剛開到90度的時間
   }
    // Serial.println(i);
}

void door_close(int i)
{

   motor_anticlockwise(i);
   if (Block_Buffer==true)
     {
     delay(300);
     Block_Buffer=false;
     Serial.println("cl");
     }
     light_blocking(i);
   if (Light_Block==true && light_blocking_door_num==i)
   {
    motor_stop(i);
    Block_Buffer=true;
    Close_Num[i]=0; 
    Opening[i]=0;
   }
   //  Serial.println(i);
}

void all_door_stop()
{
  motor_stop(0);
  motor_stop(1);
  motor_stop(2);
  motor_stop(3);
  motor_stop(4);
}
