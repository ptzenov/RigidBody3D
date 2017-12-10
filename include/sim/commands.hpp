#ifndef _COMMANDS_HPP_
#define _COMMANDS_HPP_

#include <sim/stateMachine.hpp>
#include <string>
#include <iostream>

class AbstractCommand {
public:

	std::string command_name;
	std::string command_description;
	virtual void executeCommand(StateMachine* state,
			const char* command_values[3]) = 0;
	virtual ~AbstractCommand(){;}
};

class Set_Move_type_cmd: public AbstractCommand {
public:
	Set_Move_type_cmd()
	{
		this->command_name = "set_move_type";
		this->command_description =
				"Select one of 4 possible motion trajectories: linear, sequential, circular and helical.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Move_cmd: public AbstractCommand {
public:

	Move_cmd() {
		command_name = "move";
		command_description = "Start/Resume the simulation";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Pause_cmd: public AbstractCommand {
public:

	Pause_cmd() {
		command_name = "pause";
		command_description = "Pause the simulation";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Resume_cmd: public AbstractCommand {
public:

	Resume_cmd() {
		command_name = "resume";
		command_description = "Similar to move - resume simulation.";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_linear_move_direction_cmd: public AbstractCommand {
public:

	Set_linear_move_direction_cmd() {
		command_name = "set_linear_move_direction";
		command_description =
				"Specify (as a 3-vector) the direction vector for the following motion along a linear trajectory.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Start_continuous_linear_move_x_cmd: public AbstractCommand {
public:

	Start_continuous_linear_move_x_cmd() {
		command_name = "start_continuous_linear_move_x";
		command_description =
				"Set the direction vector to point along the x-axis to 1.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Stop_continuous_linear_move_x_cmd: public AbstractCommand {
public:

	Stop_continuous_linear_move_x_cmd() {
		command_name = "stop_continuous_linear_move_x";
		command_description = "Set the direction vector along the x-axis to 0.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Start_continuous_linear_move_y_cmd: public AbstractCommand {
public:

	Start_continuous_linear_move_y_cmd() {
		command_name = "start_continuous_linear_move_y";
		command_description = "Set the direction vector along the y-axis to 1.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Stop_continuous_linear_move_y_cmd: public AbstractCommand {
public:

	Stop_continuous_linear_move_y_cmd() {
		command_name = "stop_continuous_linear_move_y";
		command_description = "Set the direction vector along the y-axis to 0.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Start_continuous_linear_move_z_cmd: public AbstractCommand {
public:

	Start_continuous_linear_move_z_cmd() {
		command_name = "start_continuous_linear_move_z";
		command_description = "Set the direction vector along the z-axis to 1.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Stop_continuous_linear_move_z_cmd: public AbstractCommand {
public:

	Stop_continuous_linear_move_z_cmd() {
		command_name = "stop_continuous_linear_move_z";
		command_description = "Set the direction vector along the z-axis to 0.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_position_x_cmd: public AbstractCommand {
public:

	Set_position_x_cmd() {
		command_name = "set_position_x_cmd";
		command_description = "Set the x-coordiante of the current position.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_position_y_cmd: public AbstractCommand {
public:

	Set_position_y_cmd() {
		command_name = "set_position_y_cmd";
		command_description = "Set the y-coordiante of the current position.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_position_z_cmd: public AbstractCommand {
public:

	Set_position_z_cmd() {
		command_name = "set_position_z_cmd";
		command_description = "Set the z-coordiante of the current position.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_velocity_1_cmd: public AbstractCommand {
public:

	Set_velocity_1_cmd() {
		command_name = "set_velocity_1";
		command_description =
				"Set the first object velocity to a desired value.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_velocity_2_cmd: public AbstractCommand {
public:

	Set_velocity_2_cmd() {
		command_name = "set_velocity_2";
		command_description =
				"Set the second object velocity to a desired value.";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_velocity_selector_to_1_cmd: public AbstractCommand {
public:

	Set_velocity_selector_to_1_cmd() {
		command_name = "set_velocity_selector_to_1";
		command_description =
				"Select the current velocity to be equal to the first object velocity";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_velocity_selector_to_2_cmd: public AbstractCommand {
public:

	Set_velocity_selector_to_2_cmd() {
		command_name = "set_velocity_selector_to_2";
		command_description =
				"Select the current velocity to be equal to the second object velocity";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_acceleration_1_cmd: public AbstractCommand {
public:

	Set_acceleration_1_cmd() {
		command_name = "set_acceleration_1";
		command_description =
				"Set the first object acceleration to a desired value.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_acceleration_2_cmd: public AbstractCommand {
public:

	Set_acceleration_2_cmd() {
		command_name = "set_acceleration_2";
		command_description =
				"Set the second object acceleration to a desired value.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_acceleration_selector_to_1_cmd: public AbstractCommand {
public:

	Set_acceleration_selector_to_1_cmd() {
		command_name = "set_vacceleration_selector_to_1";
		command_description =
				"Select the current acceleration to be equal to the first object acceleration";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_acceleration_selector_to_2_cmd: public AbstractCommand {
public:

	Set_acceleration_selector_to_2_cmd() {
		command_name = "set_vacceleration_selector_to_2";
		command_description =
				"Select the current acceleration to be equal to the second object acceleration";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_rotation_axis_cmd: public AbstractCommand {
public:

	Set_rotation_axis_cmd() {
		command_name = "set_rotation_axis";
		command_description =
				"(for rotational motion - circular/helical). Set the rotation axis direction as a 3 vector (a,b,c) default is (0 0 1)";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_center_of_rotation_cmd: public AbstractCommand {

public:

	Set_center_of_rotation_cmd() {
		command_name = "set_center_of_rotation";
		command_description =
				"(for rotational motion - circular/helical). Set the 3D coordinates of the current center of rotation (a,b,c) default is (0 0 0)";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_angular_velocity_cmd: public AbstractCommand {
public:

	Set_angular_velocity_cmd() {
		command_name = "set_angular_velocity";
		command_description =
				"(for rotational motion - circular/helical). Set the angular velocity.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_angular_acceleration_cmd: public AbstractCommand {
public:

	Set_angular_acceleration_cmd() {
		command_name = "set_angular_acceleration";
		command_description =
				"(for rotational motion - circular/helical). Set the angular acceleration.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_axial_velocity_cmd: public AbstractCommand {
public:

	Set_axial_velocity_cmd() {
		command_name = "set_axial_velocity";
		command_description =
				"(for motion along a helical trajectory). Set the object velocity along the helix symmetry axis.";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Go_to_cmd: public AbstractCommand {
public:

	Go_to_cmd() {
		command_name = "go_to";
		command_description =
				"(for all types of motion). Set the target coordinates of the objects motion. According to the currently selected trajectory type,"
						" the program will automatically calculate the relevant parameters as to successfully move the object from current position to the specified "
						"target position ";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_axis_max_cmd: public AbstractCommand {
public:

	Set_axis_max_cmd() {
		command_name = "set_axis_max";
		command_description =
				"set the maximum extend of the x,y and z coordinate axis. Default is (5,5,5).";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_axis_min_cmd: public AbstractCommand {
public:

	Set_axis_min_cmd() {
		command_name = "set_axis_min";
		command_description =
				"set the minimum extend of the x,y and z coordinate axis. Default is (-5,-5,-5).";
	}
	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_rotation_plane_cmd: public AbstractCommand {
public:

	Set_rotation_plane_cmd() {
		command_name = "set_rotation_plane";
		command_description =
				"(for rotational motion). Choose one of 3 possible planes of rotation: XY/XZ or YZ. ";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Set_arch_angle_cmd: public AbstractCommand {
public:

	Set_arch_angle_cmd() {
		command_name = "set_arch_angle";
		command_description =
				"(for rotational motion).For go_to along a circular trajectory. Set the angle of the trajectory arch between current point and target point.";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);

};

class Yaw_cmd: public AbstractCommand {
public:

	Yaw_cmd() {
		command_name = "yaw";
		command_description = "rotate object around its Y-axis";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);
};

class Pitch_cmd: public AbstractCommand {
public:

	Pitch_cmd() {
		command_name = "pitch";
		command_description = "rotate object around its X-axis";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);
};

class Roll_cmd: public AbstractCommand {
public:

	Roll_cmd() {
		command_name = "roll";
		command_description = "rotate object around its Z-axis";
	}

	void executeCommand(StateMachine* state, const char* command_values[3]);
};



#endif
