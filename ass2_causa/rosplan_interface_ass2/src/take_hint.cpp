/**
* \file take_hint.cpp
* \brief move my the arm of my robot
* \author Lorenzo Causa
* \version 1.0
*
*  Clients : <BR>
*    /move_arm_service
*
* Description :
*
* This node uses moveit move the arm of the robot to reach the hint
*
*/

#include "rosplan_interface_ass2/take_hint.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>

// GLOBAL VARIABLES
ros::ServiceClient client_move_arm;

namespace KCL_rosplan {
	MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
		// here the initialization
		
	}
	bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
		// here the implementation of the action
		std::cout << "take hint of: " << msg->parameters[0].value << std::endl;
		usleep(3000000); //wait 3 second to wait the arm to stop oscillate
		exproblab_ass2:: Move_arm joint_goal;
		joint_goal.request.joint0 = -3.14/2;
		joint_goal.request.joint1 = 0;
		joint_goal.request.joint2 = -3.14/2;
		joint_goal.request.joint3 = 0;
		joint_goal.request.joint4 = 0;
		client_move_arm.call(joint_goal);
		joint_goal.request.joint2 = 0;
		client_move_arm.call(joint_goal);

		ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
		return true;
	}
}

/// This node move the arm of the robot to reach the hint
int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_take_hint", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");
client_move_arm = nh.serviceClient<exproblab_ass2::Move_arm>("/move_arm_service");
KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
