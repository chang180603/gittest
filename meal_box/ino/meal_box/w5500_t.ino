void eth() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        //------------------------------------------

       if (c==93)               //   ]
       {                                   
           read_start=false;
           if(cmd == false)
           read_stop = true;
       }
       if(read_start==true && read_stop==false)
       {
           if(cmd == true)
               data_cmd += c;
           else
               data_id += c;
       }
      if(c == 91)
      {                                            //91為'['字元的ascii碼
             read_start = true;
             cmd = !cmd;
      }
      //-------------------------------------------
      if (c == '\n' && currentLineIsBlank)
      {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<div>");
          client.print("EMS");
          client.print(EMS);
          if (Error == false)
          {
              if(door_status == 1)
              {
                  client.print("[opened]");
              }
              else
              {
                  client.print("[closed]");
              }
              client.print("[");
              client.print(query_id);
              client.print("]");
          }

          else
          {
               client.print("[error]");
               client.print("[");
              client.print(query_id);
              client.print("]");
               if (Id_error==true)
               client.print("id not found");
               else 
               client.print("CMD is error");
          }
          client.print("</div>");
          client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') 
        {
          // you're starting a new line
              currentLineIsBlank = true;
        } 
        else if (c != '\r') 
        {
          // you've gotten a character on the current line
              currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    Serial.print("data_cmd : ");   
    Serial.println(data_cmd);
    Serial.print("data_id : ");      
    Serial.println(data_id);   
    read_start=false;
    read_stop=false;
    
    if (data_cmd =="open" )
    {
        Error = false;
        int int_data_id= data_id-'0';
        if (int_data_id<=4)
        {
            Id_error = false;
            Serial.print("door");
            Serial.print(int_data_id);
            Serial.println("   open");        
        }
        Open_Num[int_data_id]=1;
    }  
    else if (data_cmd =="close" )
    {
        Error = false;
        int int_data_id= data_id-'0';
        if (int_data_id<=4)
        {
            Id_error = false;
            Serial.print("door");
            Serial.print(int_data_id);
            Serial.println("   close");
        }
       Close_Num[int_data_id]=1;
    }
    else if (data_cmd == "query")
    { 
       Error = false;
       int int_data_id= data_id-'0';
       if (int_data_id<=4)
       {
            query_id = int_data_id;
            door_status = Opening[int_data_id];
            Id_error = false;
       }
       else
       {
             Id_error = true;  
       }
    }
    else if(data_cmd == "")
    {}
    else
    {
      Error =true;
    }
  }
  data_cmd="";
  data_id=0;
}
