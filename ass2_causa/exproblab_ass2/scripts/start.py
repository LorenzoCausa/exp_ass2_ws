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
from std_srvs.srv import *
import time
import rosplan_dispatch_msgs.srv 
import rosplan_knowledge_msgs.srv
import diagnostic_msgs.msg

# GLOBAL VARIABLES
update_knowledge_client=None
    
#FUNCTIONS
def update_knowledge_predicate(is_positive,predicate_name,key,value):
    global update_knowledge_client
    update_req=rosplan_knowledge_msgs.srv.KnowledgeUpdateServiceRequest()
    update_req.knowledge.is_negative=not(is_positive)
    update_req.update_type=0
    update_req.knowledge.knowledge_type=1
    update_req.knowledge.attribute_name=predicate_name
    key_value=diagnostic_msgs.msg.KeyValue()
    key_value.key=key
    key_value.value=value
    update_req.knowledge.values.append(key_value)
    result=update_knowledge_client(update_req)
    print('predicate knowledge updated: ',predicate_name,key,value,is_positive)

def update_knowledge_goal(predicate_name,key,value,is_positive):
    global update_knowledge_client
    update_req=rosplan_knowledge_msgs.srv.KnowledgeUpdateServiceRequest()
    update_req.knowledge.is_negative=not(is_positive)
    update_req.update_type=1
    update_req.knowledge.knowledge_type=1
    update_req.knowledge.attribute_name=predicate_name
    key_value=diagnostic_msgs.msg.KeyValue()
    key_value.key=key
    key_value.value=value
    update_req.knowledge.values.append(key_value)
    result=update_knowledge_client(update_req)
    print('goal knowledge updated: ',predicate_name,key,value,is_positive)

def update_knowledge_instance(name,instanceType):
    global update_knowledge_client
    update_req=rosplan_knowledge_msgs.srv.KnowledgeUpdateServiceRequest()
    update_req.update_type=0
    update_req.knowledge.knowledge_type=0
    update_req.knowledge.instance_name=name
    update_req.knowledge.instance_type=instanceType
    result=update_knowledge_client(update_req)
    print('instance knowledge updated: ',instanceType,name)


def main():
    """main of the start node"""
    global update_knowledge_client
    rospy.init_node('start',anonymous=True)
    # Wait for all services
    rospy.wait_for_service('rosplan_problem_interface/problem_generation_server')
    rospy.wait_for_service('rosplan_planner_interface/planning_server')
    rospy.wait_for_service('rosplan_parsing_interface/parse_plan')
    rospy.wait_for_service('rosplan_plan_dispatcher/dispatch_plan')
    rospy.wait_for_service('rosplan_knowledge_base/update')
    #rospy.wait_for_service('rosplan_knowledge_base/state/propositions')# not used for now, needed for avoid to try to take the hint from your start position
    rospy.wait_for_service('rosplan_knowledge_base/clear')
    print('All services ready')
    
    # Generates all clients
    prob_gen_client=rospy.ServiceProxy('rosplan_problem_interface/problem_generation_server',Empty)  
    plan_client=rospy.ServiceProxy('rosplan_planner_interface/planning_server',Empty) 
    parse_client=rospy.ServiceProxy('rosplan_parsing_interface/parse_plan',Empty)
    dipatch_client=rospy.ServiceProxy('rosplan_plan_dispatcher/dispatch_plan',rosplan_dispatch_msgs.srv.DispatchService) 
    update_knowledge_client=rospy.ServiceProxy('rosplan_knowledge_base/update',rosplan_knowledge_msgs.srv.KnowledgeUpdateService) 
    #prop_client=rospy.ServiceProxy('rosplan_knowledge_base/state/propositions',rosplan_knowledge_msgs.srv.GetAttributeService) #not used for now, needed for avoid to try to take the hint from your start position
    clear_knowledge=rospy.ServiceProxy('rosplan_knowledge_base/clear',Empty) 
    
    
    success=False
    while success==False:
        clear_knowledge()
        update_knowledge_predicate(True,'not_initialized','','')
        update_knowledge_instance('wp1','waypoint')
        update_knowledge_instance('wp2','waypoint')
        update_knowledge_instance('wp3','waypoint')
        update_knowledge_instance('wp4','waypoint')       
        #update_knowledge_predicate(True,'robot_at','waypoint','wp1')
        update_knowledge_goal('hp_tested','','',True)
        # Call services to start the system
        prob_gen_client()
        print('Problem generated')
        #time.sleep(1)
        plan_client()
        print('Plan generated')
        #time.sleep(1)
        parse_client()
        print('Plan parsed')
        #time.sleep(1)
        print('Dispatching plan')
        dispatchRes=dipatch_client()
        success=dispatchRes.goal_achieved
        print('Plan dispatched, success: ',success)
        time.sleep(10)

    print('Goal achieved!')
    
if __name__ == '__main__':
    main()
