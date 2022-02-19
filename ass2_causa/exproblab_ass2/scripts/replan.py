#!/usr/bin/env python

import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from math import pi
from std_msgs.msg import *
from moveit_commander.conversions import pose_to_list
from exproblab_ass2.srv import *
from exproblab_ass2.msg import *
from std_srvs.srv import *
import time
import rosplan_dispatch_msgs.srv 
import array
import numpy as np

# GLOBAL VARIABLES

def replan_callback(req):
    rospy.wait_for_service('/rosplan_plan_dispatcher/cancel_dispatch')
    #cancel current dispatch
    try:
        cancel_dispatch = rospy.ServiceProxy('/rosplan_plan_dispatcher/cancel_dispatch', Empty)
        ok=cancel_dispatch()
        if ok:
            print('dispatch cancelled')
    
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)
    
    return True
    


   
def main():
    """main of the replan node"""
    rospy.init_node('replan',anonymous=True)
    replan_service = rospy.Service('replan_service', Replan_srv, replan_callback)
    print("replanner online")
    rospy.spin()
    
if __name__ == '__main__':
    main()
