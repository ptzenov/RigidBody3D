#include <common.hpp>

/**
 * Compares two strings for equality. 
 * @param c1
 * @param c2 
 * @returns true if c1 is syntactically equal to c2 and false otherwise.
 */
bool compStr(const char* c1, const char* c2)
{
	return std::string(c1).compare(c2) == 0;	
}



