#include <sim/stateMachine.hpp>
#include <common.hpp>
#include <math.h>

StateMachine::StateMachine()
{
        CURRENT_TRAJ_TYPE = TRAJ_TYPE_LINEAR;
        CURRENT_ROTATION_PLANE = ROT_PLANE_XY; // set default plane of rotation to be xy!
        CURRENT_ACC_SELECTOR = 0;
        CURRENT_VEL_SELECTOR = 0;

        ACCELERATION[0] = 0;
        ACCELERATION[1] = 0;
        VELOCITY[0] = 0;
        VELOCITY[1] = 0;
        dimension_toggle = 0;

        //vector specifying the current direction of motion
        direction[0] = 1.0f;
        direction[1] = 1.0f;
        direction[2] = 0.0f;

        //vector specifying the current velocity
        current_velocity[0] = 0.0f;
        current_velocity[1] = 0;
        current_velocity[2] = 0;
        // acceleration
        current_acceleration[0] = 0;
        current_acceleration[1] = 0;
        current_acceleration[2] = 0;

        //vectors specifying the min and max dimensions of the x
        xyz_min[0] = -500;
        xyz_min[1] = -500;
        xyz_min[2] = -500;
        xyz_max[0] = 500;
        xyz_max[1] = 500;
        xyz_max[2] = 500;
        x[0] = 0;
        x[1] = 0;
        x[2] = 0;

        target[0] = 0;
        target[1] = 0;
        target[2] = 0;
        target[3] = 0;

        n_vect[0] = 0;
        n_vect[1] = 0;
        n_vect[2] = 1;

	t_vect[0] = 0;
        t_vect[1] = 0;
        t_vect[2] = 0;

	b_vect[0] = 0;
        b_vect[1] = 0;
        b_vect[2] = 0;

	c_0[0] = 0;
        c_0[1] = 0;
        c_0[2] = 0;

	theta = 0;
        angular_velocity = 0.0f;
        angular_acceleration = 0.0f;
        axial_vel = 0.0;
        arch_angle = M_PI;
        v_helix[0] = 0;
        v_helix[1] = 0;
        v_helix[2] = 0;
        radius = 10;
        start_simulation = false;
	
	yaw = false; 
	pitch = false;
       	roll = false;

}


