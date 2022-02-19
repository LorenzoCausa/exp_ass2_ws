#include "rosplan_interface_ass2/test_hp.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>
#include <exproblab_ass2/Cons_IDs.h>
#include <exproblab_ass2/Replan_srv.h>

// GLOBAL VARIABLES


// FUNCTIONS


namespace KCL_rosplan {
  MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
    // here the initialization

  }
  bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
    // here the implementation of the action
    std::cout << "HP tested \n ";

    return true;
  }
}


int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_test_hp", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");

KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
