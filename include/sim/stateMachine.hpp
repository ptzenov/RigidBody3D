#ifndef _STATEMACHINE_HPP_
#define _STATEMACHINE_HPP_


class StateMachine {
	private: 
		StateMachine();
	public:
	static StateMachine* get_instance(){
		static StateMachine* instance = new StateMachine();
		return instance;
	}
	unsigned int CURRENT_TRAJ_TYPE;
	unsigned int CURRENT_ROTATION_PLANE; // set default plane of rotation to be xy!
	unsigned int CURRENT_ACC_SELECTOR;
	unsigned int CURRENT_VEL_SELECTOR;

	float ACCELERATION[2];
	float VELOCITY[2];

	int dimension_toggle;
	//bool start_simulation = false;
	//
	//vector specifying the current direction of motion
	float direction[3];
	//vector specifying the current velocity
	float current_velocity[3];
	//vector specifying the current direction of acceleration
	float current_acceleration[3];
	//vectors specifying the min and max dimensions of the x
	float xyz_min[3];
	float xyz_max[3];
	//vector specifying the current position
	float x[3];
	// this is the motion target vector!!! Notice that it is a 4-vector, initialized with 0 at the end
	// this means that targeted motion is DEACTIVATED!!! Set to a value different than 0 and this 
	// will activate the checksif target is reached.
	float target[4];
	// special params for spherical and helical motion
	// n_vect: vector perpendicular to the plane of rotation
	float n_vect[3];
	// t_vect -> first basis vector for the plane of rotation
	float t_vect[3];
	//b_vect --> second basis vector for the plane of rotation: b = n x t (so that t,b,n form a right handed coordinate system)
	float b_vect[3];
	// central point of rotation
	float c_0[3];
	// rotation angle, angular velocity and acceleration...
	float theta;
	float angular_velocity;
	float angular_acceleration;
	//this is the axial velocity for the helical motion...
	float axial_vel;
	float arch_angle; // this is the variable specifying the arch angle for execution of the go_to command along circular trajectory.
	// default is 180 degrees. Possible values are arch_angle (15; 180] degrees ( set 15 as the minimum since when arch angle is 0 then the
	// Radius of the trajectory becomes infinity...

	// helical motion vector in the t,b,n basis... start with R 0 0 !
	float v_helix[3];
	float radius;
	bool start_simulation;

	bool yaw,pitch,roll;

};

#endif
