/**
* \file check_hp.cpp
* \brief check my hypotheses
* \author Lorenzo Causa
* \version 1.0
*
* Clients : <BR>
*   /consistent_IDs
*
*   /replan_service
*
* Description :
*
* This node check my hypotheses to see if I have new consistent, if no it triggers the replanning
*
*/

#include "rosplan_interface_ass2/check_hp.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>
#include <exproblab_ass2/Cons_IDs.h>
#include <exproblab_ass2/Replan_srv.h>

// GLOBAL VARIABLES
ros::ServiceClient cons_IDs_client;
ros::ServiceClient replan_client;
exproblab_ass2::Cons_IDs Cons_IDs_srv;

// FUNCTIONS
bool new_cons_HP(){

  bool at_least_one_new=false;

  for(int i;i<6;i++){

    if(Cons_IDs_srv.response.IDs[i]!=0){

        at_least_one_new=true;
        }
    
    }
return at_least_one_new;
}

namespace KCL_rosplan {
  MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
    // here the initialization

  }
  bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
    // here the implementation of the action
    std::cout << "check hp, if no consistents replan \n ";
    exproblab_ass2::Replan_srv replan_srv;
    Cons_IDs_srv.request.newIDs=true;
    cons_IDs_client.call(Cons_IDs_srv);
   
    bool at_least_one_new=new_cons_HP();
    
    if(!at_least_one_new){
        std::cout << "no new consistent hp -> replan \n" ;
        replan_client.call(replan_srv);
        }
    else{
        std::cout << "new consistent hp -> go test to test hp \n" ;
        }
    ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
    return true;
  }
}

///check my hypotheses to see if I have new consistent
int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_check_hp", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");
cons_IDs_client = nh.serviceClient<exproblab_ass2::Cons_IDs>("/consistent_IDs");
replan_client = nh.serviceClient<exproblab_ass2::Replan_srv>("/replan_service");
KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
