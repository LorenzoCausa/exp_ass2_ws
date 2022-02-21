# Experimental Robotics Laboratory: Second assignment
## Introduction
This is a ROS package that simulates a simple Cluedo-like investigation. It uses rosplan to manage pddl logic as reasoner and moveit for moving the arm and reach the hints.

## Software architecture
### Component diagram
In the diagram below you can see the nodes necessary for the correct functioning of the code. Since there are many nodes the complete component diagram would be unreadable. For this reason the proposed component diagram shows only the main parts and the most general connections.

![Alt text](images/componentUML.png?raw=true)

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
