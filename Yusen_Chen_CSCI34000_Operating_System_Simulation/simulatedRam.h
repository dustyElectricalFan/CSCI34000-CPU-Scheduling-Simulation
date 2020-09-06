//Yusen Chen

#ifndef SIMULATEDRAM_H_INCLUDED
#define SIMULATEDRAM_H_INCLUDED
#include <deque>
#include "pid.h"

class simulatedRam{

public:
    simulatedRam();

    simulatedRam(long long int num);

    bool checkSize(long long int num);

    long long int getSize();

    pid insertPid(long long int num, std::string whichQ);

    void deletePid(long long int num);

    void readMem();

private:

    long long int memLimit;
    long long int ID = 1;
    long long int currMem = 0;
    std::deque<pid> memVec;


};


#endif // SIMULATEDRAM_H_INCLUDED
