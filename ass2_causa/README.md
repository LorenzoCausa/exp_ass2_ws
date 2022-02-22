# Experimental Robotics Laboratory: Second assignment
## Introduction
This is a ROS package that simulates a simple Cluedo-like investigation. It uses rosplan to manage pddl logic as reasoner and moveit for moving the arm and reach the hints.

## Software architecture
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


![Alt text](images/TemporalDiagram.png?raw=true)

# TO DO LIST:
1) Aggiusta il plan, ogni volta rifa initialize e potrebbe tornare a prendere l'hint dall'ultimo waypoint 
2) Aggiungi test_hp 
3) Il robot si ferma senza motivo tra le action, aggiustalo (non ho idea del perche ma succede anche a fedezecchi)
4) Attento a non ritestare ipotesi già testate una volta

# COME LANCIARLO:
1) roslaunch exproblab_ass2 my_robot_in_the_map.launch 
2) roslaunch exproblab_ass2 rosplan.launch
3) roslaunch exproblab_ass2 my_services.launch
4) rosrun exproblab_ass2 start.py
