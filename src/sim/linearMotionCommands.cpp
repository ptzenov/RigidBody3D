#include <sim/commands.hpp>
#include <common.hpp>

void Set_linear_move_direction_cmd::executeCommand(StateMachine* state,
                const char* command_values[3])
{
        for (int d = 0; d < 3; d++)
        {
                if (!compStr("_",command_values[d]))
                        state->direction[d] = atof(command_values[d]);
        }

}

void Start_continuous_linear_move_x_cmd::executeCommand(StateMachine* state,
                const char * command_values[3])
{
        state->direction[0] = 1.0f;
        state->direction[1] = 0.0f;
        state->direction[2] = 0.0f;
        state->target[3] = 0;
}


void Stop_continuous_linear_move_x_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
        state->direction[0] = 0.0f;
}

void Start_continuous_linear_move_y_cmd::executeCommand(StateMachine* state,
                const char * command_values[3])
{
        state->direction[0] = 0.0f;
        state->direction[1] = 1.0f;
        state->direction[2] = 0.0f;
        state->target[3] = 0;
}


void Stop_continuous_linear_move_y_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
        state->direction[1] = 0.0f;
}

void Start_continuous_linear_move_z_cmd::executeCommand(StateMachine* state,
                const char * command_values[3])
{
        state->direction[0] = 0.0f;
        state->direction[1] = 0.0f;
        state->direction[2] = 1.0f;
        state->target[3] = 0;
}


void Stop_continuous_linear_move_z_cmd::executeCommand(StateMachine* state, const char* command_values[3])
{
        state->direction[2] = 0.0f;
}


