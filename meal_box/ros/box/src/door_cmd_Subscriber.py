#!/usr/bin/env python
#import sys
import rospy
import requests
from std_msgs.msg import String

class tmp ():
	def __init__(self):
	    rospy.init_node('coverCmd', anonymous=True)
	    rospy.Subscriber("coverCmd", String, self.callback)
	    self.pub = rospy.Publisher('coverhttp',String,queue_size=10)
	def callback(self, data):

	    s = requests.Session()
	    #print data
	    r = s.get('http://192.168.50.177/'+ str(data))
	    #print r
	    c = str(data)
	    #print c
	    #print c.find('query')
	    #rospy.loginfo(data)
	    if c.find('query')>=0:     
			#while not rospy.is_shutdown():
		            #rospy.loginfo(data)
	       #rospy.loginfo(data)
	       self.pub.publish(data)         
		            #rate.sleep()
		
		
	def listener(self):
	    #pub = rospy.Publisher('coverStatus',String,queue_size=10)
	    rospy.spin()
#if __name__ == '__main__':
    
#rospy.spin()

#def talker():
#    #pub = rospy.Publisher('coverStatus',String,queue_size=10)
#    rospy.init.node('pub_coverCmd',anonymos=True)
if __name__ == '__main__':
    try:
       
       TMP = tmp()
       TMP.listener()
       #talker()
    except rospy.ROSInterruptException:
       pass
