void light_blocking(int i)
{
  light_blocking_val = digitalRead(Light_Blocking[i]);
  if (light_blocking_val==1)
    Light_Block =true;
  else
    Light_Block=false;
    light_blocking_door_num=i;
}

void bottom_press()
{
  /*
      if (digitalRead(Emergency_Switch)==0)
      {
         EMS=!EMS; 
      }  
      */
      //bouncer.update ( );
      if ( bouncer.update() == true  && bouncer.read() == HIGH)
      {
       EMS=!EMS; 
      }
}

void motor_clockwise(int i)
{
  digitalWrite(Motor_In1[i],LOW);
  digitalWrite(Motor_In2[i],HIGH);
}

void motor_anticlockwise(int i)
{
  digitalWrite(Motor_In1[i],HIGH);
  digitalWrite(Motor_In2[i],LOW);
}

void motor_stop(int i)
{
  digitalWrite(Motor_In1[i],LOW);
  digitalWrite(Motor_In2[i],LOW);
  Serial.print("MOTORS");
}
