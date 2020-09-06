//Yusen Chen

#ifndef THEQUEUES_H_INCLUDED
#define THEQUEUES_H_INCLUDED
#include <deque>
#include "pid.h"

class theQueues{

public:

void enqueCommon (pid x);
void enqueAR (pid x);
void dequeCommon ();
void dequeAR ();
bool isCommonEmpty ();
bool isAREmpty ();
void printCommon();
void printAR();
pid terminateCommon();
pid terminateAR();


private:

std::deque<pid> commonQ;
std::deque<pid> arQ;



};


#endif // THEQUEUES_H_INCLUDED
