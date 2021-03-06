# Experimental Robotics Laboratory: Second assignment
## Introduction
This is a ROS package that simulates a simple Cluedo-like investigation. It uses rosplan to manage pddl logic as reasoner and moveit for moving the arm and reach the hints.

## Software architecture
The assignment is divided in three packages: 
1) **exproblab_ass2:** It contains the launchers, pddl, urdf and the nodes that implement the services necessary for the correct functioning of the code.
2) **moveit_ass2_pkg:** It contains the code generated by moveit.
3) **rosplan_interface_ass2:** It contains the implementations of the actions in the domain of the pddl.

### Component diagram
In the diagram below you can see the nodes necessary for the correct functioning of the code. Since there are many nodes the complete component diagram would be unreadable. For this reason the proposed component diagram shows only the main parts and the most general connections.

![Alt text](images/componentUML.png?raw=true)

* **start:** This node starts the investigation and replan in a loop until the solution is found. The solution is signaled by receiving the message with the ID of the correct hypothesis (via subscrition to the topic /final solution).
* **ROSPLAN:** This component represents all parts that we saw of rosplan: Knowledge Base, Problem Interface, Planner Interface, Parsing Interface, Plan Dispatch.
* **simulation** The node given by the prof. It provides a publisher for the hints and a service for check the correct hipothesis's ID.
* **simulator** This component represents all nodes and interfaces of the simulation like gazebo and rviz.

**ACTIONs**

This are the nodes implementing the actions of the pddl:
* **initialize**: Brings the arm in the start pose and move my robot in a starting waypoint.
* **goto_waypoint**: Move my robot in waypoints.
* **take_hint**: Move the arm to take the hint and return to the start pose.
* **check_hp**: Check if there are new consistent hypoteses.
* **test_hp**: Test consistent hypotheses and if the correct one is found send the final solution message to stop the investigation. 

**SERVICEs**

This are nodes that I wrote to implement services that I need.
* **listener:** It listen the hints and provide a services to check consistent hypotheses.
* **move_arm:** It provides a service to use moveit and move the arm.
* **replan:** It provides a service to cancel the current plan and force a replan.
* **go_to_point:** It provides a service to move to a point on the map with a certain orientation.

## State Diagram
The code does not have an explicit state machine (it uses rosplanner to manage the logic), however its behavior can be represented with the simple state diagram below.
* **Plan:** In this phase a new plan will be generated, this plan goal is to test hypotheses. To do this, all waypoints must be visited and it must be checked that there are new coherent hypotheses.
* **Dispatch Plan:** In this phase the previously generated plan is actuated. When the current plan became unable to find the solution the replan is triggered. 

![Alt text](images/stateDiagram.png?raw=true)

## Temporal Diagram
Although the code uses a planner (whose domain and problem are defined via pddl) the plan found can be described by a time diagram since its structure is always the same.

1) **Initialization:** the arm is placed in the starting position and the robot is moved to a waypoint.
2) **take the hint:** the arm moves to place the cluedo link in the hint receiving sphere, after that it returns to the starting position.
3) **move to a waypoint:** the robot moves to a waypoint whose hint has not yet been taken.
4) **check hypotheses:** check if there are any new consistent hypotheses. If there are, then go to the test. If there are no new consistent hypotheses, the plan is canceled and a new one is replanned (restarts from (1))
5) **test hypotheses:** test if my consistent hypotheses are the solution. If none of the currently consistent hypotheses are correct then the replan is done (restarts from (1)). If the solution is among my consistent hypotheses, the simulation ends as the crime is solved.

![Alt text](images/TemporalDiagram.png?raw=true)

## List of srv implemented
* **Cons_IDs**: It can be used in two ways: to get all the IDs of my consistent hypotheses, or to get only the IDs of my new consistent hypotheses (once an ID is returned from this service it is considered old).
* **Move_arm**: This service allows the robot arm to be moved in any configuration. It takes as input 5 floats each representing the angle of one of the 5 joints.
* **Oracle**: Service given by the professor. Return the ID of the correct solution
* **Replan**: It cancel the current dispatch and force a replan.

## Installation and running procedure
### Requirements
To use this package some external packages are needed:
* Moveit
* occupancy_grid_utils
* ROSPlan
* rosplan_demos

**Note:** If you use the docker that was provided to us these packages should be already installed.

### Installation
The installation is straightforward, just clone this repository to your ros workspace and do the catkin_make:

```
git clone https://github.com/LorenzoCausa/exp_ass2_ws
```

**Note:** This repository also contains the required external packages, if you use the docker that was provided to us you will already have them in your workspace, so you will have to delete the duplicate packages and keep only the folder with the actual assignment, which is `ass2_causa`.

## Running procedure
To use this code you need to run in this order in separate terminals the following:
1) This will open gazebo and rviz with the the robot and the hints in the map.
```
roslaunch exproblab_ass2 my_robot_in_the_map.launch 
```
2) This will start rosplan with all its parts. From this terminal you can see the action that the robot is performing.
```
roslaunch exproblab_ass2 rosplan.launch
```
3) This will start the services that I implemented. From this terminal you can see the hints, and when checked you can also see the current hypotheses.
```
roslaunch exproblab_ass2 my_services.launch
```
4) This will start the simulation. This terminal shows the replannings and when is found prints the ID of the solution.
```
rosrun exproblab_ass2 start.py
```
**Note:** If you are using the docker it is highly advisable to do `apt-get update` and `apt-get upgrade`. Without it, strange behaviors occurred during the tests.

## Behavior
The behavior of the robot in the enviroment is straightforward:
1) Take hint in all waypoints.
2) Check if there are new consistent hypotheses, if no restart from 1.
3) Test my hypotheses, if none is the correct one restart from 1.

## Video demo
If you run properly the code you should see something like this

![Alt Text](images/myGif.gif?raw=true) 

You can take a look at the complete video demo of the project from here:

[Click here](https://drive.google.com/file/d/1NaVbCxEIZJVQB7wqzuCuNIktaiBzbQI3/view?usp=sharing)

**Note:** 
* The video shows only a portion of the entire 'investigation' as it usually lasts quite a long time.
* Both GIF and video have been accelerated to make them shorter and with less downtime.

## Environment and working hypothesis 
The simulation environment was entirely provided by the professor, no changes were made to any of the parts that were given to us.
The code is designed to be robust and reusable, all implemented services can be used for similar a problem with few modifations. 
The system also wants to be versatile, it uses the one provided by the teacher as oracle but it would also work with a different logic, the only necessary adjustments would concern the communication interfaces with it.

## System features
* Robot with five controlable joints via moveit
* Replanning when the plan is no longer able to find a solution
* Test of the hypotheses only when a new consistent one is found
* Modularity
* Flexibility

## System limitations and improvements
### Limitations
1) Very long investigation
2) It is necessary to finish taking hints in all waypoints before checking if any new consistent hypotheses have been found
3) Takes the hints with open-loop control
4) When it reinitializes, it could theoretically go to the last waypoint from which it took the last suggestion, however this actually never happens because rosplan always visits the waypoints always in the same order (wp1, wp2, wp3, wp4).

### Possible solutions and improvements
1) To solve (1) the only solutions are to speed up the robot (increasing the risk of overturn the robot) or to modify the oracle and decrease the number of hints needed (for example by removing the repetition of hints already found).
2) To solve (2) it would have been sufficient to write the PDDL in such a way as to check the new consistent hypotheses after each suggestion taken, it was decided not to use this solution since there would have been plans with very few actions removing any freedom from rosplan planning (and effectively making it a state machine).
3) The robot arm only makes a predefined ad hoc movement to take the hints, if the robot for any reason is positioned incorrectly the arm would miss the hint (in my tests this never happened but it would be possible in a less ideal simulation). The solution can be to use moveit to move *cluedo_link* exactly into the "hint sphere" with a closed loop method.
4) Before deleting the entire plan and forcing the replan, the last waypoint visited by the robot should be memorized and then added to the PDDL problem before replanning.

## Documentation
All the doxygen documentation is in the *documentation* folder.

## Author and contacts
The system was developed entirely by me, below my credentials and contacts:

**Lorenzo Causa, 4519089**

**mail**: lorenzo.causa1998@gmail.com

**phone number**: 3247427182  

## Third assignment
You can open the repo of the third assignment by clicking 
[here](https://github.com/LorenzoCausa/ass3_causa)

