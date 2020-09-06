//Yusen Chen

#include "simulatedRam.h"

simulatedRam::simulatedRam(){};

simulatedRam::simulatedRam(long long int num): memLimit(num){};

bool simulatedRam::checkSize(long long int num)
{
    if(currMem + num > memLimit)
        return false;
    return true;
}

long long int simulatedRam::getSize()
{
    return memVec.size();
}

pid simulatedRam::insertPid(long long int num, std::string whichQ)
{
    if(memVec.empty() || (!memVec.empty() && memVec.begin()->getStart() >= num))
        {
                    pid newEntry = pid(ID,num,whichQ,true,0,num - 1);
                    memVec.push_front(newEntry);
                    currMem += num;
                    ID++;
                    return newEntry;
        }

    else
        {
                    bool found = false;
                    for(std::size_t i = 0; i < memVec.size() - 1; i++)
                    {
                        if(memVec[i+1].getStart() - memVec[i].getEnd() > num)
                        {
                            pid newEntry = pid(ID,num,whichQ,true,memVec[i].getEnd() + 1,memVec[i].getEnd() + num);
                            memVec.insert(memVec.begin() + i + 1,newEntry);
                            found = true;
                            currMem += num;
                            ID++;
                            return newEntry;
                        }
                    }

                    if(!found && memLimit - memVec.rbegin()->getEnd() >= num)
                    {
                        long long int scope = 0;
                        if(memVec.rbegin()->getEnd() + num == memLimit)
                            scope = memLimit - 1;
                        else
                            scope = memVec.rbegin()->getEnd() + num;

                        pid newEntry = pid(ID,num,whichQ,true,memVec.rbegin()->getEnd() + 1, scope);
                        memVec.push_back(newEntry);
                        currMem += num;
                        ID++;
                        return newEntry;
                    }

                    pid newEntry = pid();
                    return newEntry;

         }


}

void simulatedRam::deletePid(long long int num)
{
    for(std::size_t i = 0; i < memVec.size(); i++)
                {
                    if(memVec[i].getID() == num)
                    {
                        currMem -= memVec[i].get_datasize();
                        memVec.erase(memVec.begin() + i);
                        break;
                    }
                }
}

void simulatedRam::readMem()
{
    std::cout << "pid " << "datasize " << "type " << "starting byte " << "ending byte " << '\n' << '\n';
                for(pid x : memVec)
                {
                    if(x.get_type() == "common")
                      std::cout << x.getID() << "   " << x.get_datasize() << "       " << x.get_type() << "       " << x.getStart() << "   -   " << x.getEnd() << '\n';
                    else
                      std::cout << x.getID() << "   " << x.get_datasize() << "        " << x.get_type() << "           " << x.getStart() << "   -   " << x.getEnd() << '\n';

                }
}
