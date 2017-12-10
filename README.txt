*************** motion3D v 1.1 **************************
*	 Created by: petzko									*
* 	 Created on: May 31st 2014							*
*********************************************************
 
 
 Motion3D is a real-time simulator of virtual motion of a single object ( in current
 implementation a black ball), which supports:
 
 1) high resolution timer for accurate timing synchronization 
 2) real-time openGL 3.1. animation of the simulation
 3) motion setup and control via simple text commands console/sockets/other input
 methods
 4)
 ****************************************************************************************************
 COMPILATION 
 
 to compile you will need the following libraries
 
 PAPI - a profiler library that provides an accurate high resolution timer for timing 
 sinchronizations ( i have provided a compiled static libpapi.a in the lib folder of the project 
 as well as the header file papi.h, but you could recompile your own version of PAPI
 see http://icl.cs.utk.edu/papi/) 
 OpenGL version 3.1 or higher
 glut (or freeglut) openGL utility toolkit library 
 glew - the opengl extension wrangler 
 glu - openGL Utility Library 
 openMP - the usual library form shared memory architecture multithreading 
 
 you can either export the project in Eclipse from the archive or compile using the makefile
 provided in the debug folder. 
 
 ****************************************************************************************************
 LIFECYCLE of the program! 
 Motion3D logically contains three modules - a "simulation engine", which implements all 
 commands and is responsible for orchestrating the motion process, and a "visualizatio module"
 which reads in the simulation data and renders it on screen using openGL and a "user 
 interraction module", which is responsible for handing any kind of program input in real time. 
   
 Currently, this program structure is divided amongst two independednt threads - the "SIMULAITON THREAD", which 
 handles the simulation engine and the visualization module, and the "USER IO THREAD" which is a dedicated thread
 only for processing user input data. 
    
 User Interaction:
 the user can influence the simulation or the visualization in two ways: controlling the motion via input commands and
 changing the view of the motion via specialized shrotcut & command keys.
 i) controlling the motion via input commands.  
 - Currently motion3D implements the following set of commands & corresponding values specified by strings: 
 NOTE1: when inputing the commands the ""'s are not neccessary! Also motion3D can take both capital, small or mixed letters 
 for the commands and their values!!
 NOTE2: some of the commands below accept numerical values as the command values. for example "set_linear_move_direction" setting the values happens
 with either comma separated or whitespace separated string: i.e the following form of instructions is possible
 set_linear_move_direction 1 0 0 
 or 
 set_linear_move_direction (1,0,0) 
 or 
 set_linear_move_direction 1,0,0 
 or 
 set_linear_move_direction (1 0 0)  
 etc... 
 ****************************************************************************************************
 COMMAND DESCRIPTION 
 COMMAND -- VALUES	-- MEANING
 
"set_move_type" -- LINEAR/CIRCULAR/HELICAL/SEQUENTIAL -- choose between one of 4 different trajectory types ( names are self descriptive) 
 
"move" -- no value -- initiate the movement
 
"pause" -- no value -- pause the current simulation 

"resume" -- no value -- resume the simulation 

"set_linear_move_direction" -- a 3vector specifying the direction of linear motion -- set the direction of linear motion
  
"start_continuous_linear_move_x -- no value -- initiate continuous linear move in x direction 
 
"stop_continuous_linear_move_x" -- no value -- stop the movement in x direction 

"start_continuous_linear_move_y -- same as above 

"stop_continuous_linear_move_y" --- bla bla 

"start_continuous_linear_move_z --- bla bla

"stop_continuous_linear_move_z" --- bla bla

"set_position_x" -- a single value -- specify a new x coordinate of the object
 
"set_position_y" -- a single value -- specify a new y coordinate of the object

"set_position_z" -- a single value -- specify a new z coordinate of the object

"set_velocity_1" -- a 3vector -- specify first velocity mode // internally the program allows dynamic switching between two different velocity modes

"set_velocity_2" -- a 3vector -- specify second velocity mode

"set_velocity_selector_to_1" -- no value -- set the to be used velocity mode to mode 1

"set_velocity_selector_to_2" -- no value -- set the to be used velocity mode to mode 2

"set_acceleration_1" -- a 3vector -- specify first acceleration mode // internally the program allows dynamic switching between 
two different acceleration modes

"set_acceleration_2"-- a 3vector -- specify second acceleration mode //

"set_acceleration_selector_to_1 -- no value -- set the to be used acceleration mode to mode 1

"set_acceleration_selector_to_2" -- no value -- set the to be used acceleration mode to mode 2

/// parameters for circular and helical motion only

"set_rotation_axis" -- a 3 vector -- specify a vector pointing along the axis around which the rotaiton should take place

"set_center_of_rotation" -- a 3 vector -- specify a coordinate point , i.e. center of rotation, around which the object is suppsed to rotate

"set_angular_velocity" -- a single value -- set the angular velocity

"set_angular_acceleration" -- a single value -- set the angular acceleration 

"set_axial_velocity" -- a single value --- set the axial velocity for helical motion, that is how fast is the object going out of the rotation plane. 
 
 "end" -- no value -- exit from the program... 
 
 NOTE3: Please remember that in order to start the simulation one has to give the program the command "move" !! 
 
 
 TO BE CONTINUED... IMPLEMENT MORE COMMAND
  
 ii) keyboard shortcuts for improving visualizaiton 
 	
 	arrow keys --> rotate the camera along the x and y coordinate axis
 	
 	
  	'+' --> zoom in 
  	'-' --> zoom out
  	'a' --> move to the left with respect to the object (object moves to the right) 
	'd' --> move to the right with respect to the object
	's' --> move downwards with respect to the object
 	'w' --> move upwards with respect to the object
	'z' --> toggle on/off the text display
 	'c' --> center the camera facing the global coordinate system origin
	'r' --> reset the timer

NOTE on CAMERA : Please note that the camera is initially position so that the
positive x-axis points towards East, the positive y-axis towards north and the positive
z-axis towards the user... 
***************************************************************************************************
EXAMPLES FOR MOTION INSTRUCTIONS

to setup linear motion in say (1,1,0) direction enter the following commands:

//set the direction of the movement... 

set_linear_move_direction 1 1 0 
// set the initial velocity to 1
set_velocity_1 1
// velocity and acceleration selectors are by default set to 1, but just in case
set_velocity_selector_to_1 
move 
//sit back and relax.. 

to set up a sequential motion (first x then y then z direction) 


to set up a circular motion around z axis with center the point (2,0,0)

set_move_type circular
set_rotation_axis 0 0 1 // z-axis 
set_center_of_rotation 2 0 0 
set_angular_velocity 1 
move
// sit back and relax... 
 ****************************************************************************************************
  
