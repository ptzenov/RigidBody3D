#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <iostream>
#include <string>

#define DEBUG

#ifdef DEBUG
#define DBG_MSG(MSG,F,L) std::cout<<F << "|" << L <<":" << MSG << std::endl;
#endif


/**
 * Compares two strings for equality. 
 * @param c1
 * @param c2 
 * @returns true if c1 is syntactically equal to c2 and false otherwise.
 */
bool compStr(const char* c1, const char* c2);


#define OMP_NUM_THREADS 2
// define the thread types...
#define THREAD_SIMULATION 0
#define THREAD_USER_IO 1

#define ROT_PLANE_XY 2 // corresponds to 0 0 1
#define ROT_PLANE_XZ 1 // corresponds to 0 1 0
#define ROT_PLANE_YZ 0 // corresponds to 1 0 0

// constants specifying the possible trajectory types
#define TRAJ_TYPE_LINEAR 0
#define TRAJ_TYPE_CIRCULAR 1
#define TRAJ_TYPE_HELICAL 2
#define TRAJ_TYPE_SEQUENTIAL 3

/// this macro here specifies the total number of commands currently supported
#define NR_CMDS 32

#endif /* COMMON_HPP_ */
