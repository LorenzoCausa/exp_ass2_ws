#include "rosplan_interface_ass2/check_hp.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <motion_plan/PlanningAction.h>
#include <exproblab_ass2/go_to_pointAction.h>
#include <exproblab_ass2/Move_arm.h>
#include <exproblab_ass2/Cons_IDs.h>

// GLOBAL VARIABLES
ros::ServiceClient cons_IDs_client;
int old_IDs[6]={0,0,0,0,0,0};
exproblab_ass2::Cons_IDs Cons_IDs_srv;

// FUNCTIONS
bool new_cons_HP(){

  bool at_least_one_new=false;

  for(int i;i<6;i++){

    if(Cons_IDs_srv.response.IDs[i]!=old_IDs[i]){

        at_least_one_new=true;
        old_IDs[i]=Cons_IDs_srv.response.IDs[i];
        }
    
    }
return at_least_one_new;
}

void test() {

  
    // here the implementation of the action
    std::cout << "check hp, if no consistents replan " << std::endl;
    
    if(!cons_IDs_client.call(Cons_IDs_srv)){
	std::cout<<"error calling the service \n";
     }
    std::cout << "service called " << std::endl;
    
    if(!new_cons_HP()){
        std::cout << "no new consistent hp -> replan " << std::endl;
        }
    else{
        std::cout << " new consistent hp -> go test to test hp " << std::endl;
        }
    ROS_INFO("Action performed: completed!");

  }



int main(int argc, char **argv) {
ros::init(argc, argv, "my_rosplan_action_check_hp");
ros::NodeHandle nh("~");
cons_IDs_client = nh.serviceClient<exproblab_ass2::Cons_IDs>("/consistent_IDs");
test();

return 0;
}
