#include "common.hpp"

void dbg_msg(const char * msg, const char* file, int line)
{
        std::cout<<"<FILE(" << file << "); LINE("<< line << ");MSG(" <<  msg << ")>" << std::endl;
}

