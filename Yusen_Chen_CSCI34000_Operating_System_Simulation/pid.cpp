//Yusen Chen

#include "pid.h"
#include <string>

pid::pid():ID(0),data_size(0),process_type("normal"),status("unknown"),rangeStart(0),rangeEnd(0){}

pid::pid(long long int id, long long int datasize, std::string datatype, bool now, long long int startRange, long long int endRange): ID(id), data_size(datasize), process_type(datatype), rangeStart(startRange), rangeEnd(endRange){
set_status(now);
}

long long int pid::getID()
{
    return ID;
}

long long int pid::get_datasize()
{
    return data_size;
}

std::string pid::get_type()
{
    return process_type;
}

std::string pid::get_status()
{
    return status;
}

void pid::set_status(bool now)
{
    if(now)
        status = "running";
    else
        status = "waiting";
}

void pid::printself()
{
    std::cout << ID << "    " << data_size << "        " << process_type << "  " << status;
}
//The extra function is just to make display a bit neater.
void pid::printselfAR()
{
  std::cout << ID << "    " << data_size << "          " << process_type << "     " << status;
}

long long int pid::getStart()
{
    return rangeStart;
}

long long int pid::getEnd()
{
    return rangeEnd;
}
