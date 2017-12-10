#include <sim/commands.hpp>
#include <common.hpp>
#include <math/linsolver.hpp>
#include <math/mathUtils.hpp>

void Set_Move_type_cmd::executeCommand(StateMachine* state,
                                       const char* command_values[3])
{
        state->target[3] = 0;
        if (compStr(command_values[0], "linear"))
                state->CURRENT_TRAJ_TYPE = TRAJ_TYPE_LINEAR;
        if (compStr(command_values[0], "circular"))
        {
                state->CURRENT_TRAJ_TYPE = TRAJ_TYPE_CIRCULAR;
                state->theta = 0;

        }
        if (compStr(command_values[0], "helical"))
        {
                state->CURRENT_TRAJ_TYPE = TRAJ_TYPE_HELICAL;
                state->theta = 0;
                state->v_helix[2] = 0;
        }

        if (compStr(command_values[0], "sequential"))
        {
                state->CURRENT_TRAJ_TYPE = TRAJ_TYPE_SEQUENTIAL;
                state->dimension_toggle = 0;
        }
}

void Move_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	DBG_MSG("Starting simulation",__FILE__,__LINE__);
	state->start_simulation = true;
}

void Pause_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	DBG_MSG("Pausing simulation",__FILE__,__LINE__);
	state->start_simulation = false;
}

void Resume_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	DBG_MSG("Resuming simulation",__FILE__,__LINE__);
        state->start_simulation = true;
}

void Set_position_x_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{
        if (!compStr(command_values[0], "_"))
                state->x[0] = atof(command_values[0]);
}

void Set_position_y_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{
        if (!compStr(command_values[0], "_"))
                state->x[1] = atof(command_values[0]);
}

void Set_position_z_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{
        if (!compStr(command_values[0], "_"))
                state->x[2] = atof(command_values[0]);
}

void Set_velocity_1_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{

        if (!compStr(command_values[0], "_"))
                state->VELOCITY[0] = atof(command_values[0]);
}

void Set_velocity_2_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{

        if (!compStr(command_values[0], "_"))
                state->VELOCITY[1] = atof(command_values[0]);
}

void Set_velocity_selector_to_1_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        state->CURRENT_VEL_SELECTOR = 0;

}

void Set_velocity_selector_to_2_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{
        state->CURRENT_VEL_SELECTOR = 1;

}

void Set_acceleration_1_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{
        if (!compStr(command_values[0], "_"))
                state->ACCELERATION[0] = atof(command_values[0]);

}

void Set_acceleration_2_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        if (!compStr(command_values[0], "_"))
                state->ACCELERATION[1] = atof(command_values[0]);

}

void Set_acceleration_selector_to_1_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        state->CURRENT_ACC_SELECTOR = 0;

}

void Set_acceleration_selector_to_2_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{
        state->CURRENT_ACC_SELECTOR = 1;
}

void Set_axis_max_cmd::executeCommand(StateMachine* state,
                                      const char* command_values[3])
{

        for (int d = 0; d < 3; d++)
        {
                if (!compStr(command_values[d], "_"))
                        state->xyz_max[d] = atof(command_values[d]);
        }

}

void Set_axis_min_cmd::executeCommand(StateMachine* state,
                                      const char* command_values[3])
{
        for (int d = 0; d < 3; d++)
        {
                if (!compStr(command_values[d], "_"))
                        state->xyz_min[d] = atof(command_values[d]);
        }
}

void Go_to_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{

        //"go_to",
        for (int d = 0; d < 3; d++)
        {
                if (!compStr(command_values[d], "_"))
                        state->target[d] = atof(command_values[d]);
        }

        if (state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_LINEAR)
                for (int d = 0; d < 3; d++)
                        state->direction[d] = state->target[d] - state->x[d];

        if (state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_CIRCULAR)
        {

                //setup the rotation axis to be perpendicular to the currently selected rotation plane!
                /*Mind that the motion might not always be in that plane!!! This WILL NOT be the case
                 * when the line connecting the current posiotion and the target position is not perpendicular
                 * to any of the coordinate axis, x,y,z.
                 *
                 * */
                state->n_vect[0] = 0;
                state->n_vect[1] = 0;
                state->n_vect[2] = 0;
                state->n_vect[state->CURRENT_ROTATION_PLANE] = 1;

                /**
                 *  now to find the center of rotation c_0 as well as the coordinate basis triplet (t,b,n) we need to solve a linear
                 * 	system of equations Ax = b
                 *  Below I setup the matrix A and the r.h.s b and solve it using my own gaussian ellimination procedure (with pivoting)
                 *	Basically the system we have to solve is the following
                 *
                 *	arbitrary circular motion in 3D space can be represented as follows
                 *
                 *	x(theta) = c_0 + A*v(theta) -> where A is a coordinate transformation matrix from the normal carthesian coordinate basis, (1,0,0)
                 *	(0,1,0) (0,0,1) to the basis determined by the triplet (t,b,n), and v is the trajectory of circular motion in the xy plane
                 *	v(theta) = (Rcos(theta), Rsin(theta), 0)
                 *  given that we know the normal vector n, and the condition that n x t = b find c_0 and t such that the following
                 *  conditions are statisfied
                 *  x(0) = initial_position = c_0 + A*v(0)
                 *  x(arch_angle) = target_position = c_0 + A*v(arch_angle); -> these two conditions give us 6 equations and luckily we have
                 *  exactly 6 unknonws (3 for c_0 and 3 for t) ---> setup the system and solve it!!!
                 */

                //first calculate the radius of the circular motion with the formula... R = distance(target,x)/2*sin(arch_angle/2);
                float distance = 0;
                for (int d = 0; d < 3; d++)
                        distance += (state->target[d] - state->x[d]) * (state->target[d] - state->x[d]);
                distance = sqrt(distance);

                state->radius = distance / (2 * sin(state->arch_angle / 2));
                // done! now setup the system ( note that we are not solving a 6x6 linear system, but rather 3x3 -->
                // if one does the math he/she will see that this suffices.
                //allocate space for the matrix A
                float A[9];
                // first row of A
                A[0] = state->radius * cos(state->arch_angle) - state->radius;
                A[1] = -state->radius * state->n_vect[2] * sin(state->arch_angle);
                A[2] = state->radius * state->n_vect[1] * sin(state->arch_angle);
                // second row of A
                A[3] = state->radius * state->n_vect[2] * sin(state->arch_angle);
                A[4] = state->radius * cos(state->arch_angle) - state->radius;
                A[5] = -state->radius * state->n_vect[0] * sin(state->arch_angle);
                //third row of A
                A[6] = -state->radius * state->n_vect[1] * sin(state->arch_angle);
                A[7] = state->radius *	state->n_vect[0] * sin(state->arch_angle);
                A[8] = state->radius * cos(state->arch_angle) - state->radius;

                //setup the right hand side...
                float b[3];
                for (int d = 0; d < 3; d++)
                {
                        b[d] = state->target[d] - state->x[d];
                }

                gaussianElimination(A, b, state->t_vect, 3);
                // now calculate the center c_0;
                for (int d = 0; d < 3; d++)
                        state->c_0[d] = state->x[d] - state->radius * state->t_vect[d];

                //				normalize_vector(t_vect);
                vector_product(state->n_vect, state->t_vect, state->b_vect);
                //				normalize_vector(b_vect); //not needed !!!b should already have norm 1!

                //reinitialize the local coordinate system of the rotation
                //reinit_vector_triplet();
                //as the helical/circular motion will have to restart, set theta = 0 and v_helix = 0;
                state->theta = 0;

        }
        if (state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_HELICAL)
        {

                /// Build and solve the equations that satisfy the following conditions
                /*  the coordinates at time t of a point moving along a helix in 3D space:
                 *  x(t) = c_0 + A*v(t)
                 * ,where
                 * c_0 is hte center of rotation.
                 *
                 * 		t1 b1 n1
                 * A =  t2 b2 n2
                 *      t3 b3 b3
                 * is the transformation matrix from the local w.r.t the helical motion basis (t,b,n)
                 * and v(t) = (Rcos(b*t) , Rsin(b*t), a*t)
                 * with "b" = angular velocity and "a" is the axial velocity
                 *
                 * Idea: Basically find c_0 and the vector t = (t1,t2,t3) , which satisfy the equations
                 * x(0) = current position x(theta_end) = final position.
                 *
                 * Here I will treat the problem a little differently than the circular motion, even thought the logics is the same!
                 * i) the user specifies the angular velocity "b", the axial velocity "a", the radius of the helix R and the angle of rotation
                 * theta_end. theta_end can be any arbitrary value more than 10 degrees, with the number of full rotations described by the
                 * helix given by floor(theta_end / 360 degrees). e.g.  theta_end = 720 --> 2 full rotations
                 * Note that we are treating non-accelerating motion! for accelerating helical motion things become way more complicated.
                 * */

                state->n_vect[0] = 0;
                state->n_vect[1] = 0;
                state->n_vect[2] = 0;
                state->n_vect[state->CURRENT_ROTATION_PLANE] = 1;

                float theta_end = 1024; // total angle described by the motion HARDCODED: TODO SET THETA_END VIA USER COMMAND
                state->radius = 2; //HARDCODED: TODO SET RADIUS VIA USER COMMAND
                // done! now setup the system ( note that we are not solving a 6x6 linear system, but rather 3x3 -->
                // if one does the math he/she will see that this suffices.
                //allocate space for the matrix A
                float A[9];
                state->arch_angle = M_PI * theta_end / 180;
                float tend = state->arch_angle / state->angular_velocity;

                // first row of A
                A[0] = state->radius * cos(state->arch_angle) - state->radius;
                A[1] = -state->radius *state->n_vect[2] * sin(state->arch_angle);
                A[2] = state->radius * state->n_vect[1] * sin(state->arch_angle);
                // second row of A
                A[3] = state->radius * state->n_vect[2] * sin(state->arch_angle);
                A[4] = state->radius * cos(state->arch_angle) - state->radius;
                A[5] = -state->radius * state->n_vect[0] * sin(state->arch_angle);
                //third row of A
                A[6] = -state->radius * state->n_vect[1] * sin(state->arch_angle);
                A[7] = state->radius * state->n_vect[0] * sin(state->arch_angle);
                A[8] = state->radius * cos(state->arch_angle) - state->radius;

                //setup the right hand side...
                float b[3];
                for (int d = 0; d < 3; d++)
                {
                        b[d] = state->target[d] - state->x[d] - state->axial_vel * tend * state->n_vect[d];
                }

                gaussianElimination(A, b, state->t_vect, 3);

                // now calculate the center c_0;
                for (int d = 0; d < 3; d++)
                        state->c_0[d] = state->x[d] - state->radius * state->t_vect[d];

                vector_product(state->n_vect, state->t_vect, state->b_vect);
                state->theta = 0;
                state->v_helix[2] = 0;
        }

        //activate targeted motion!

        state->target[3] = 1;
}


