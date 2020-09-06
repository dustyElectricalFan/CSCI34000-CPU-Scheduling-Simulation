//Yusen Chen

#include "hardDisk.h"

hardDisk::hardDisk(){};

hardDisk::hardDisk(long long int num): numOfDisks(num){}

long long int hardDisk::getNumOfDisks()
{
    return numOfDisks;
}

void hardDisk::setNumOfDisks(long long int num)
{
    numOfDisks = num;
}

bool hardDisk::isEmpty(long long int num)
{

    if(hardDiskQueue[num].size() > 0)
        return false;
    else
        return true;
}

void hardDisk::enquePid(pid x, long long int num)
{

    if(hardDiskQueue[num].size() > 0)
    {
        x.set_status(false);
        hardDiskQueue[num].push_back(x);
    }
    else
    {
        x.set_status(true);
        hardDiskQueue[num].push_back(x);
    }
}

pid hardDisk::dequePid(long long int num)
{

    pid memRef = *(hardDiskQueue[num].begin());
    hardDiskQueue[num].pop_front();
    if(hardDiskQueue[num].size() > 0)
        hardDiskQueue[num].begin()->set_status(true);
    return memRef;
}

void hardDisk::printAll()
{
    std::cout << "hdd#  " << "pid " << "type " << "status" << '\n';
    for(std::pair<long long int, std::deque<pid>> x : hardDiskQueue)
    {
        if(x.second.size() > 0)
        {
             for(pid y : x.second)
              std::cout << x.first << "     " << y.getID() << "   " <<  y.get_type() << "   " << y.get_status() << '\n';
        }
    }
}
