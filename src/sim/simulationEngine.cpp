#include <sim/simulationEngine.hpp>
#include <sim/commands.hpp>
#include <math/mathUtils.hpp>

#include <common.hpp>
#include <string.h>

bool check_bdry_reached(float _x[3],float xyz_max[3],float xyz_min[3])
{
        bool bdry_reached = false;
        /// check if the ball has reached the boundary...
        for (int d = 0; d < 3; d++)
        {
                if (_x[d] >= xyz_max[d] || _x[d] <= xyz_min[d])
                {
                        bdry_reached = true;
                        break;
                }
        }
        return bdry_reached;
}

bool check_target_reached(float _x[3],float _x_new[3], float _target[3])
{
        float sprod = 0; // scalar prod of target-x and target-xnew
        for (int d = 0; d < 3; d++)
                sprod += (_target[d] - _x[d]) * (_target[d] - _x_new[d]);
        return sprod < 0;
}


void Engine::move()
{
        if(!current_state->start_simulation)
                return;

        trajectory[pt_ctr_][0] = current_state->x[0];
        trajectory[pt_ctr_][1] = current_state->x[1];
        trajectory[pt_ctr_][2] = current_state->x[2];

        pt_ctr_ = (pt_ctr_ + 1 )% MAX_POINTS;

        if (current_state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_LINEAR)
        {
                if (current_state->target[3] != 0)
                        go_to_linear_motion();
                else
                        execute_linear_motion();
        }
        // move x first then y then z ...
        if (current_state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_SEQUENTIAL)
        {
                if (current_state->target[3] != 0)
                        go_to_sequential_motion();
                else
                        execute_sequential_motion();
        }
        if (current_state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_CIRCULAR)
        {
                if (current_state->target[3] != 0)
                        go_to_circular_motion();
                else
                        execute_circular_motion();
        }
        if (current_state->CURRENT_TRAJ_TYPE == TRAJ_TYPE_HELICAL)
        {
                if (current_state->target[3] != 0)
                        go_to_helical_motion();
                else
                        execute_helical_motion();
        }



}

void Engine::stop()
{
        for (int d = 0; d < 3; d++)
        {
                current_state->current_velocity[d] = 0;
                current_state->current_acceleration[d] = 0;
                current_state->direction[d] = 0;
        }
}

void Engine::go_to_linear_motion()
{


        float x_new[3];
        for (int d = 0; d < 3; d++)
                x_new[d] = current_state->x[d] + current_state->VELOCITY[current_state->CURRENT_VEL_SELECTOR] * dt * current_state->direction[d]
                           + 0.5 * current_state->ACCELERATION[current_state->CURRENT_ACC_SELECTOR] * dt * dt
                           * current_state->direction[d];
        // if targeted moton is activated
        // check whether we are aoubt to jump over the target!!!
        // if we are about to overshoot (i.e. jumped over) the target, stop where we are!
        // else proceed the motion as usual.

        bool target_reached = check_target_reached(current_state->x, x_new, current_state->target);
        if (target_reached)   // if we still have some time to go proceed as usual
        {
                stop();
        }
        else     //else set the current coordinate to be x[d];
        {
                execute_linear_motion();
        }

}




void Engine::execute_linear_motion()
{
        float x_new[3];
        // calculate the new position
        for (int d = 0; d < 3; d++)
                x_new[d] = current_state->x[d] + current_state->VELOCITY[current_state->CURRENT_VEL_SELECTOR] * dt *current_state-> direction[d]
                           + 0.5 * current_state->ACCELERATION[current_state->CURRENT_ACC_SELECTOR] * dt * dt
                           * current_state->direction[d];
        // check if you have reached the boundary
        if(check_bdry_reached(x_new,current_state->xyz_max,current_state->xyz_min))
        {
                stop();
                return;
        }

        // if we are not executing targeted linear move proceed with the usual motion !!!
        for (int d = 0; d < 3; d++)
        {
                current_state->x[d] = x_new[d];
                //change the current velocity and current acceleration to reflect the current state of moiton
                current_state->current_velocity[d] = current_state->direction[d] * current_state->VELOCITY[current_state->CURRENT_VEL_SELECTOR];
                current_state->current_acceleration[d] = current_state->direction[d]
                                * current_state->ACCELERATION[current_state->CURRENT_VEL_SELECTOR];
        }
        // increase the velocity a bit.
        for (int d = 0; d < 3; d++)
        {
                current_state->VELOCITY[current_state->CURRENT_VEL_SELECTOR] += current_state->ACCELERATION[current_state->CURRENT_ACC_SELECTOR]
                                * dt;
        }

}
void Engine::go_to_sequential_motion()
{
        /**
         * ToDo: implement me
         */

}


void Engine::execute_sequential_motion()
{

        /**
         * ToDo: implement me
         */

}

void Engine::go_to_circular_motion()
{

        //predict the next step
        float x_new[3];
        for (int d = 0; d < 3; d++)
        {
                x_new[d] = current_state->c_0[d]
                           + current_state->radius * (current_state->t_vect[d] * cos(current_state->theta) + current_state->b_vect[d] *
                                                      sin(current_state->theta));
        }

        bool target_reached = check_target_reached(current_state->x, x_new, current_state->target);
        if (target_reached)
        {
                stop();
        }
        else
        {
                // proceed with sequential motion as usual
                execute_circular_motion();
        }

}

void Engine::execute_circular_motion()
{
        float x_new[3];

        //execute motion
        for (int d = 0; d < 3; d++)
        {
                x_new[d] =current_state-> c_0[d]
                          + current_state->radius * (current_state->t_vect[d] * cos(current_state->theta) + current_state->b_vect[d] * sin(current_state->theta));
        }


        // check if you have reached the boundary
        if(check_bdry_reached(x_new,current_state->xyz_max,current_state->xyz_min))
        {
                stop();
                return;
        }

        // calculate the tangential vector to the circular orbit, i.e. "current direction"...
        for (int d = 0; d < 3; d++)
        {
                current_state->x[d] = x_new[d];
                current_state->direction[d] = (-current_state->t_vect[d] * sin(current_state->theta) + current_state->b_vect[d] * cos(current_state->theta));
        }
        normalize_vector(current_state->direction);
        // calculate the tangential acceleration and tangential velocity...
        float tangential_vel =current_state-> angular_velocity *current_state-> radius;
        float tangential_acc = current_state->angular_acceleration * current_state->radius;
        //set the current velocity to be a vector pointing in the direction of motion
        for (int d = 0; d < 3; d++)
        {
                {
                        current_state->current_velocity[d] = tangential_vel * current_state->direction[d];
                        current_state->current_acceleration[d] = tangential_acc * current_state->direction[d];
                }
        }

        // update the angle and increase the angular velocity.
        current_state->theta = current_state->theta + dt * current_state->angular_velocity
                               + 0.5 * dt * dt *current_state-> angular_acceleration;
        current_state->angular_velocity += dt * current_state->angular_acceleration;

}

void Engine::go_to_helical_motion()
{


        //predict the next step
        current_state->v_helix[0] = current_state->radius * cos(current_state->theta);
        current_state->v_helix[1] = current_state->radius * sin(current_state->theta);
        current_state->v_helix[2] += current_state->axial_vel * dt;

        float x_new[3];
        //transform from the local coordinate system to the global coordinate system :)
        x_new[0] = current_state->c_0[0] + current_state->t_vect[0] * current_state->v_helix[0] + current_state->b_vect[0] * current_state->v_helix[1]
                   + current_state->n_vect[0] * current_state->v_helix[2];
        x_new[1] =current_state-> c_0[1] + current_state->t_vect[1] * current_state->v_helix[0] +current_state-> b_vect[1] * current_state->v_helix[1]
                  + current_state->n_vect[1] * current_state->v_helix[2];
        x_new[2] = current_state->c_0[2] + current_state->t_vect[2] * current_state->v_helix[0] + current_state->b_vect[2] * current_state->v_helix[1]
                   + current_state->n_vect[2] * current_state->v_helix[2];
        
	bool target_reached = check_target_reached(current_state->x, x_new, current_state->target);
        if (target_reached)
        {
                stop();
        }
        else
        {
                // proceed with sequential motion as usual
                execute_circular_motion();
        }
}



void Engine::execute_helical_motion()
{
        current_state->v_helix[0] = current_state->radius * cos(current_state->theta);
        current_state->v_helix[1] = current_state->radius * sin(current_state->theta);
        current_state->v_helix[2] += current_state->axial_vel * dt;

        float x_new[3];
        //transform from the local coordinate system to the global coordinate system :)
        x_new[0] = current_state->c_0[0] + current_state->t_vect[0] * current_state->v_helix[0] +current_state-> b_vect[0] *current_state-> v_helix[1]
                   + current_state->n_vect[0] *current_state-> v_helix[2];
        x_new[1] = current_state->c_0[1] + current_state->t_vect[1] * current_state->v_helix[0] + current_state->b_vect[1] *current_state-> v_helix[1]
                   + current_state->n_vect[1] * current_state->v_helix[2];
        x_new[2] = current_state->c_0[2] + current_state->t_vect[2] * current_state->v_helix[0] + current_state->b_vect[2] *current_state-> v_helix[1]
                   + current_state->n_vect[2] * current_state->v_helix[2];

        if(check_bdry_reached(x_new,current_state->xyz_max,current_state->xyz_min))
        {
                stop();
                return;
        }
        //else make the move!!!
        for(int d = 0 ; d< 3; d++)
                current_state->x[d] = x_new[d];
        current_state->theta = current_state->theta + dt * current_state->angular_velocity
                               + 0.5 * dt * dt * current_state->angular_acceleration;
        current_state->angular_velocity += dt * current_state->angular_acceleration;
}




