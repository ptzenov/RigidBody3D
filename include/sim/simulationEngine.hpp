#ifndef _SIMULATION_ENGINE_HPP_
#define _SIMULATION_ENGINE_HPP_

#define MAX_POINTS 100


#include <sim/stateMachine.hpp>
#include <memory>


std::string normalizeStr(std::string str);
bool check_bdry_reached(float _x[3],float xyz_max[3],float xyz_min[3]);
bool check_target_reached(float _x[3],float _x_new[3], float _target[3]);

class Engine
{
private:
        float dt;
        float trajectory[MAX_POINTS][3];
        int pt_ctr_;
        StateMachine* current_state;

        void execute_linear_motion();
        void go_to_linear_motion();
        void execute_sequential_motion();
        void go_to_sequential_motion();
        void execute_circular_motion();
        void go_to_circular_motion();
        void execute_helical_motion();
        void go_to_helical_motion();
        void stop();
public:
        Engine()
        {
                dt = 0.0f;
                current_state = StateMachine::get_instance();
        }
        inline void set_dt(float in_dt)
        {
                dt = in_dt;
        }

	inline bool get_yaw(){return current_state->yaw;}	
	inline bool get_pitch(){return current_state->pitch;}	
	inline bool get_roll(){return current_state->roll;}

	inline float get_X(){return current_state->x[0];}
	inline float get_Y(){ return current_state->x[1];}
	inline float get_Z(){return current_state->x[2];}

        void move();
};
#endif






