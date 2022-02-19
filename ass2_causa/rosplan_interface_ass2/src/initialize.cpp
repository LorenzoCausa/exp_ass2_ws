#include "rosplan_interface_ass2/initialize.h"
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
		std::cout << "Going to " << msg->parameters[0].value << std::endl;
		actionlib::SimpleActionClient<exproblab_ass2::go_to_pointAction> ac("/go_to_point", true);
		exproblab_ass2:: Move_arm joint_goal;
		joint_goal.request.joint0 = -3.14/2;
		joint_goal.request.joint1 = 0;
		joint_goal.request.joint2 = 0;
		joint_goal.request.joint3 = 0;
		joint_goal.request.joint4 = 0;
		client_move_arm.call(joint_goal);

		exproblab_ass2:: go_to_pointGoal goal;
		ac.waitForServer();
		if(msg->parameters[0].value == "wp1"){
			goal.x = 2.2;
			goal.y = 0.0;
			goal.theta = 0;
		}
		else if (msg->parameters[0].value == "wp2"){
			goal.x = 0;
			goal.y = 2.2;
			goal.theta = 3.14/2;
		}
		else if (msg->parameters[0].value == "wp3"){
			goal.x = -2.2;
			goal.y = 0;
			goal.theta = 3.14;
		}
		else if (msg->parameters[0].value == "wp4"){
			goal.x = 0;
			goal.y = -2.2;
			goal.theta = 3.14*3/2;
		}
		ac.sendGoal(goal);
		ac.waitForResult();
		ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
		return true;
	}
}


int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_initialize", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");
client_move_arm = nh.serviceClient<exproblab_ass2::Move_arm>("/move_arm_service");
KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
