#include "rosplan_interface_ass2/test_hp.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>
#include <exproblab_ass2/Cons_IDs.h>
#include <exproblab_ass2/Replan_srv.h>
#include <exproblab_ass2/ErlOracle.h>
#include <exproblab_ass2/Oracle.h>
#include "std_msgs/Int32.h"

// GLOBAL VARIABLES
ros::ServiceClient cons_IDs_client;
ros::ServiceClient test_hp_client;
ros::Publisher sol_publisher;
exproblab_ass2::Cons_IDs Cons_IDs_srv;
exproblab_ass2::Oracle oracle_solution;


// FUNCTIONS


namespace KCL_rosplan {
  MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
    // here the initialization

  }
  bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
    // here the implementation of the action
    int found_solution = -1; //-1 means that no solution has been found
    cons_IDs_client.call(Cons_IDs_srv);
    test_hp_client.call(oracle_solution);

    for(int i=0;i<6;i++){
      if((Cons_IDs_srv.response.IDs[i]==1)&&(i==oracle_solution.response.ID)){
        found_solution=i;
      }
    }
    std::cout << "HP tested \n ";
    if(found_solution==-1){
      std::cout << "no solution found \n ";
    }

    else{
      std_msgs::Int32 msg;
      msg.data = found_solution;
      sol_publisher.publish(msg);
      std::cout << "the solution is ID: " << found_solution << "\n";   
    }
    return true;
  }
}


int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_test_hp", ros::init_options::AnonymousName);
ros::NodeHandle nh("~");
cons_IDs_client = nh.serviceClient<exproblab_ass2::Cons_IDs>("/consistent_IDs");
test_hp_client = nh.serviceClient<exproblab_ass2::Oracle>("/oracle_solution");
sol_publisher = nh.advertise<std_msgs::Int32>("/final_solution", 1000);
KCL_rosplan::MyActionInterface my_aci(nh);
my_aci.runActionInterface();
return 0;
}
