//Yusen Chen

#ifndef SIMULATEDOS_H_INCLUDED
#define SIMULATEDOS_H_INCLUDED
#include<iostream>
#include "pid.h"
#include "hardDisk.h"
#include "theQueues.h"
#include "simulatedRam.h"

class simulatedOS{

public:

    void startSimulation();

    std::pair<std::string,std::string> getInputs();

    bool aCommand(std::string command);

    bool arCommand(std::string command);

    bool qCommand(std::string command);

    bool tCommand(std::string command);

    bool dCommand(std::string command);

    bool DCommand(std::string command);

    bool srCommand(std::string command);

    bool siCommand(std::string command);

    bool smCommand(std::string command);



private:

    theQueues mainQ;
    simulatedRam simRam;
    hardDisk theDisks;

};


#endif // SIMULATEDOS_H_INCLUDED
