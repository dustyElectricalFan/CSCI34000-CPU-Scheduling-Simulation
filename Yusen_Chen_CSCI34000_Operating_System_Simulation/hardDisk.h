//Yusen Chen

#ifndef HARDDISK_H_INCLUDED
#define HARDDISK_H_INCLUDED
#include <deque>
#include <map>
#include "pid.h"

class hardDisk{

public:

hardDisk();

hardDisk(long long int num);

long long int getNumOfDisks();

void setNumOfDisks(long long int num);

bool isEmpty(long long int num);

void enquePid(pid x, long long int num);

pid dequePid(long long int num);

void printAll();



private:
std::map<long long int, std::deque<pid>> hardDiskQueue;
long long int numOfDisks;
};


#endif // HARDDISK_H_INCLUDED
