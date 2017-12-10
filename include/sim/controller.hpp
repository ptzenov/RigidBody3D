#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#define MAX_POINTS 100

#include <sim/commands.hpp>
#include <vector>
#include <string>
#include <memory>

class Abstract_Control
{
public:
        Abstract_Control();
	virtual void loop() = 0;
	void parse_next_command(std::string ss);
protected:
        virtual void list_commands();
	std::vector<std::unique_ptr<AbstractCommand>> commands;
};

class Console_IO_Control: public Abstract_Control
{

public:
        Console_IO_Control(): Abstract_Control()
        {
                ;
        }
        void loop();
};

class Socket_IO_Control: public Abstract_Control
{
public:
        Socket_IO_Control(): Abstract_Control()
        {
                ;
        }
        void loop();

};

#endif /* PARSER_HPP_ */

