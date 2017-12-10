#include <common.hpp>
#include <sim/controller.hpp>
#include <sim/commands.hpp>
#include <sim/stateMachine.hpp>
#include <string.h>
#include <mutex>

Abstract_Control::Abstract_Control(): commands(0)
{
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_Move_type_cmd));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_Move_type_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Move_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Pause_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Resume_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_linear_move_direction_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Start_continuous_linear_move_x_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Stop_continuous_linear_move_x_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Start_continuous_linear_move_y_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Stop_continuous_linear_move_y_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Start_continuous_linear_move_z_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Stop_continuous_linear_move_z_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_position_x_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_position_y_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_position_z_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_velocity_1_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_velocity_2_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_velocity_selector_to_1_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_velocity_selector_to_2_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_acceleration_1_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_acceleration_2_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_acceleration_selector_to_1_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_acceleration_selector_to_2_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_rotation_axis_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_center_of_rotation_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_angular_velocity_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_angular_acceleration_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_axial_velocity_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Go_to_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_axis_max_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_axis_min_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_rotation_plane_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Set_arch_angle_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Yaw_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Pitch_cmd()));
        commands.push_back(std::unique_ptr<AbstractCommand>(new Roll_cmd()));
}


void Abstract_Control::parse_next_command(std::string ss)
{
        const int MAX_CHARS_PER_LINE = 512;
        const char* DELIMITER = ")( ,";


        std::cout << "\nPARSER: " << ss << "\n";
        char buffer[MAX_CHARS_PER_LINE];

        // copy the command string to a char buffer
        strcpy(buffer, ss.c_str());
        //tokenize the string removing ( , ) and empty spaces
        char* token = strtok(buffer, DELIMITER);
        std::string command = "";
        const char* values[3];
        if (token)
        {
                // first token should be the command name
                command = token;
                //should obtain the value...
                token = strtok(NULL, DELIMITER);
                if (!token)
                        values[0] = "_";
                else
                        values[0] = token;

                token = strtok(NULL, DELIMITER);
                if (!token)
                        values[1] = "_";
                else
                        values[1] = token;

                token = strtok(NULL, DELIMITER);
                if (!token)
                        values[2] = "_";
                else
                        values[2] = token;

                std::cout << "parsed command is : " << command << "\n --> values : ["
                          << values[0] << "," << values[1] << "," << values[2] << "]\n";
        }
        else
        {
                std::cout << "PARSER: invalid input command \n";
        }

        // find the current command
        bool command_identified = false;

        for (size_t i = 0; i < commands.size(); ++i)
        {
                if (!strcmp(command.c_str(), commands[i]->command_name.c_str()))
                {
                        std::cout << "\n Command index :" << i << " input command name: "
                                  << command << " original command name: "
                                  << commands[i]->command_name << "\n";
			std::mutex mtx; 
			mtx.lock();
                        {
                                commands[i]->executeCommand(StateMachine::get_instance(), values);
                        }
			mtx.unlock();
                        command_identified = true;
                        break;
                }
        }
        if (!command_identified)
                std::cout << "\n Hmm could not recognize the command you just sent me." 
				" Please try again \n";
}

std::string normalizeStr(std::string str)
{

        std::string result(str);
        std::locale loc;
        for (std::string::size_type i = 0; i < str.length(); ++i)
                result[i] = std::tolower(str[i], loc);

        return result;

}

void Abstract_Control::list_commands()
{
        std::cout << "\n############################ Welcome to motion3D" 
		" v 1.0 ############################ \n";
        std::cout << "Currently supported commands are:\n";
        std::string comm;
        for (int i = 0; i < NR_CMDS; i++)
        {
                comm = commands[i]->command_name;
                std::cout<<"cmd[" << i <<"] : "<< commands[i]->command_name<<
		       	" :: " << commands[i]->command_description<<"\n";
        }
        std::cout << " " << NR_CMDS << ": " << "end (to exit the program)\n";
        std::cout << "Please note that in order to start the simulation,"
			"you need to enter the command [MOVE]\n";
}

void Console_IO_Control::loop()
{
        std::cout << "\nEntering Console IO control loop mode \n";
        std::cout << "...\n";
        while (true)
        {
                std::cout << "Waiting for your next instruction...\n";
                std::string str;
                getline(std::cin, str);
                /// normalize the command to lower case..
                str = normalizeStr(str);
                if (!str.compare("help"))
                {
                        list_commands();
                        continue;
                }

                if (!str.compare("end"))
                {
                        std::cout << "That will be all for now! bye bye \n";
                        exit(EXIT_SUCCESS);
                }
                parse_next_command(str);
        }
}

void Socket_IO_Control::loop()
{
        std::cout << "\nEntering Socket IO control loop mode \n";
        std::cout << "...\n";
        while (true)
        {
                std::string str;
                getline(std::cin, str);
                /// normalize the command to lower case..
                str = normalizeStr(str);
                if (!str.compare("help"))
                {
                        list_commands();
                        continue;
                }

                if (!str.compare("end"))
                {
                        std::cout << "That will be all for now! bye bye \n";
                        exit(EXIT_SUCCESS);
                }

                parse_next_command(str);
        }
}






