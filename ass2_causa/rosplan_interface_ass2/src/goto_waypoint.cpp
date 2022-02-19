#include "rosplan_interface_ass2/goto_waypoint.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>

// GLOBAL VARIABLES


namespace KCL_rosplan {
  MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
    // here the initialization

  }
  bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
    // here the implementation of the action
    std::cout << "Going from: " << msg->parameters[0].value << " to: "<< msg->parameters[1].value << std::endl;
    actionlib::SimpleActionClient<exproblab_ass2::go_to_pointAction> ac("/go_to_point", true);
    
    exproblab_ass2:: go_to_pointGoal goal;
    ac.waitForServer();
    if(msg->parameters[1].value == "wp1"){
      goal.x = 2.2;
      goal.y = 0.0;
      goal.theta = 0;
    }
    else if (msg->parameters[1].value == "wp2"){
      goal.x = 0;
      goal.y = 2.2;
      goal.theta = 3.14/2;
    }
    else if (msg->parameters[1].value == "wp3"){
      goal.x = -2.2;
      goal.y = 0;
      goal.theta = 3.14;
    }
    else if (msg->parameters[1].value == "wp4"){
      goal.x = 0;
      goal.y = -2.2;
      goal.theta = 3.14*3/2;
    }
    
    //std::cout << "Debug" <<std::endl;
    ac.sendGoal(goal);
    ac.waitForResult();
    ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
    return true;
  }
}


int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_goto_waypoint", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");
KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
