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
hypotheses=[]
old_hp=[0,0,0,0,0,0]

class Hypothesis:
    """ This class contains the hypothesis of the game """
    
    def __init__(self):
        """ Initializer of the class."""
        self.murderer = []
        self.murder_weapon = []
        self.murder_place = []
        self.ID=-1
        
def callback(hint):
    #rospy.set_param('ID'+str(hint.ID)+'/'+ hint.key,hint.value)
    flag_duplicate=False
    i=0

    if(hint.key=='who'):
        while ((i<len(hypotheses[hint.ID].murderer))and (flag_duplicate==False)):
            if(hint.value==hypotheses[hint.ID].murderer[i]):
                hypotheses[hint.ID].murderer.remove(hint.value)
                flag_duplicate=True
            i=i+1
        hypotheses[hint.ID].murderer.append(hint.value)

    flag_duplicate=False
    i=0    
    if(hint.key=='where'):
        while ((i<len(hypotheses[hint.ID].murder_place))and (flag_duplicate==False)):
            if(hint.value==hypotheses[hint.ID].murder_place[i]):
                hypotheses[hint.ID].murder_place.remove(hint.value)
                flag_duplicate=True
            i=i+1
        hypotheses[hint.ID].murder_place.append(hint.value)

    flag_duplicate=False
    i=0     
    if(hint.key=='what'):
        while ((i<len(hypotheses[hint.ID].murder_weapon))and (flag_duplicate==False)):
            if(hint.value==hypotheses[hint.ID].murder_weapon[i]):
                hypotheses[hint.ID].murder_weapon.remove(hint.value)
                flag_duplicate=True
            i=i+1
        hypotheses[hint.ID].murder_weapon.append(hint.value)
        
    print('New hint added!')
    
def cons_IDs_callback(req):
    global old_hp
    IDs= Cons_IDsResponse([0,0,0,0,0,0])
    #IDs.IDs[0]=-1
    #IDs.IDs[1]=-1
    for i in range(6):
        print('ID',i,'who: ',hypotheses[i].murderer,'where: ', hypotheses[i].murder_place,'what: ',hypotheses[i].murder_weapon)
        if(len(hypotheses[i].murderer)==1 and len(hypotheses[i].murder_place)==1 and len(hypotheses[i].murder_weapon)==1):
            #if(old_hp[i]==0): #serviva per tornare 1 solo quando era la prima volta che trovi l'ipotesi
                IDs.IDs[i]=1
                old_hp[i]=1
            
    print('IDs returned')
    return IDs
   
def main():
    """main of the listener node"""
    rospy.init_node('listener',anonymous=True)
    rospy.Subscriber("oracle_hint", ErlOracle, callback)
    consistent_ID_service = rospy.Service('consistent_IDs', Cons_IDs, cons_IDs_callback)
    #Generate Hypotheses
    for i in range(6):
        HP = Hypothesis()
        HP.ID=i
        hypotheses.append(HP)
    
    rospy.spin()
    
if __name__ == '__main__':
    main()
