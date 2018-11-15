#!/usr/bin/env python
#import sys
import rospy
import requests
from std_msgs.msg import String

import urllib2
from bs4 import BeautifulSoup

def data_callback(data):
    c = str(data)
    #print '123'
    if c.find('query') >= 0:
       page = urllib2.urlopen("http://192.168.50.177/")
       #print "Before soup"
       soup = BeautifulSoup(page, 'html.parser')
       div_str = str(soup.div.string)
       #print '999999999999999',len(div_str)
       #print div_str[0:4]
       #print div_str[6:len(div_str)]
       EMS = div_str[0:4]
       door_status = div_str[4:len(div_str)]
       

       #print "After soup"
       #print("div = ",soup.div.string)
       #print "QQQQQQQQQQQQQQ:", soup.div.string
       #print type(soup.div.string)
       pub = rospy.Publisher('coverStatus',String,queue_size=10)
       rospy.loginfo(door_status)
       pub.publish(str(soup.div.string))

def listener():
    rospy.init_node('door_http', anonymous=True)
    rospy.Subscriber("coverhttp", String,data_callback)
    # print "TTTTTTTTTTTTTTTTTTTTTTTT"
    rospy.spin()
if __name__ == '__main__':
    listener()


#def talker():
    #pub = rospy.Publisher('coverStatus',String,queue_size=10)
    #rospy.init.node('pub_coverCmd',anonymos=True)
#if __name__ == '__main__':
   # try:
    #   talker()
   # except rospy.ROSInterruptException:
     #  pass
