#include <sim/commands.hpp>
#include <common.hpp>
#include <math/mathUtils.hpp>

void Set_rotation_axis_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        for (int d = 0; d < 3; d++)
        {
                if (!compStr("_",command_values[d]))
                        state->n_vect[d] = atof(command_values[d]);
        }
        reinit_vector_triplet(state->n_vect, state->t_vect, state->b_vect, state->x,
                              state->c_0,state->radius);
        //as the helical/circular motion will have to restart, set theta = 0 and v_helix = 0;
        state->theta = 0;
        state->v_helix[2] = 0;

}

void Set_center_of_rotation_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        for (int d = 0; d < 3; d++)
        {
                if (!compStr("_",command_values[d]))
                        state->c_0[d] = atof(command_values[d]);
        }
        //reinitialize the local coordinate system of the rotation
        reinit_vector_triplet(state->n_vect, state->t_vect, state->b_vect, state->x,
                              state->c_0,state->radius);
        //as the helical/circular motion will have to restart, set theta = 0 and v_helix = 0;
        state->theta = 0;
        state->v_helix[2] = 0;
}

void Set_angular_velocity_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{
        if (!compStr("_",command_values[0]))
                state->angular_velocity = (float) atof(command_values[0]);

}

void Set_angular_acceleration_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        if ( !compStr(command_values[0],"_"))
                state->angular_acceleration = (float) atof(command_values[0]);
}

void Set_axial_velocity_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        if (!compStr(command_values[0],"_"))
                state->axial_vel = (float) atof(command_values[0]);
}

void Set_rotation_plane_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{

        if (compStr(command_values[0], "xy") || compStr(command_values[0], "yx"))
                state->CURRENT_ROTATION_PLANE = ROT_PLANE_XY;
        if (compStr(command_values[0], "xz") || compStr(command_values[0], "zx"))
                state->CURRENT_ROTATION_PLANE = ROT_PLANE_XZ;
        if (compStr(command_values[0], "yz") || compStr(command_values[0], "zy"))
                state->CURRENT_ROTATION_PLANE = ROT_PLANE_YZ;

}

void Set_arch_angle_cmd::executeCommand(StateMachine* state,
                                        const char* command_values[3])
{

        if (!compStr(command_values[0], "_"))
        {
                float tmp = atof(command_values[0]);
                // if the given value is outside of the allowed boundary,
                // set the arch angle to default 180 degrees
                if (tmp < 15 || tmp > 180)
                {
                        std::cout
                                        << "\nWarning: The specified arch angle value is outside of the allowed domain [15;180] degrees. "
                                        "Reseting arch_angle to default value - 180 degrees!!!\n";
                        tmp = 180;
                }
                state->arch_angle = M_PI * tmp / (180.0f); // convert the angle to radians...
        }
}

void Yaw_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	state->yaw = ! state->yaw; 
}
	
void Pitch_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	state->pitch = ! state->pitch; 
}


void Roll_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
	state->roll = ! state->roll; 
}


