#! /usr/bin/env python 

import rospy  
import requests
from std_msgs.msg import String
import urllib2
from bs4 import BeautifulSoup

def talker(): 
   rospy.init_node("EMS", anonymous=True)   
   rate = rospy.Rate(0.1) # 10hz 
   while not rospy.is_shutdown():
	   page = urllib2.urlopen("http://192.168.50.177/")
	   #print "Before soup"
	   soup = BeautifulSoup(page, 'html.parser')
	   div_str = str(soup.div.string)
	   #print '999999999999999',len(div_str)
	   #print div_str[0:4]
	   #print div_str[4:len(div_str)]
	   EMS = div_str[0:4]
	   #while EMS.find('EMS1')>=0:
	     
	   if EMS == 'EMS1':
	      rospy.loginfo('Peripherial_door is lock')       
	   rate.sleep() 
            
if __name__ == '__main__':
    try:
         talker()
    except rospy.ROSInterruptException:
         pass
