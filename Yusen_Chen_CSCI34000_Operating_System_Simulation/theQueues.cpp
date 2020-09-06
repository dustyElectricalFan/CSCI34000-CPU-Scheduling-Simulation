//Yusen Chen

#include "theQueues.h"

void theQueues::enqueCommon(pid x)
{
  commonQ.push_back(x);
  if(commonQ.size() > 1 || arQ.size() > 0)
    commonQ.rbegin()->set_status(false);
}

void theQueues::enqueAR(pid x)
{
    arQ.push_back(x);
    if(commonQ.size() > 0)
       commonQ.begin()->set_status(false);

    if(arQ.size() > 1)
        arQ.rbegin()->set_status(false);
}

void theQueues::dequeCommon ()
{
    commonQ.begin()->set_status(false);
    commonQ.push_back(commonQ.front());
    commonQ.pop_front();
    commonQ.begin()->set_status(true);
}

void theQueues::dequeAR ()
{
  if(arQ.size() > 1)
  {
  arQ.begin()->set_status(false);
  arQ.push_back(arQ.front());
  arQ.pop_front();
  arQ.begin()->set_status(true);
  }

}

bool theQueues::isCommonEmpty()
{
    if(commonQ.size() > 0)
        return false;
    else
        return true;
}

bool theQueues::isAREmpty()
{
    if(arQ.size() > 0)
        return false;
    else
        return true;
}

void theQueues::printCommon()
{
   std::cout << "pid  " << "datasize " << "  type   " << "status   " << '\n' << '\n';
   for (pid x : commonQ)
   {
       x.printself();
       std::cout << '\n';
   }

}

void theQueues::printAR()
{
    for (pid x : arQ)
    {
         x.printselfAR();
         std::cout << '\n';
    }


}

pid theQueues::terminateCommon()
{
    if(commonQ.size() > 1)
    {
        pid memRef = *commonQ.begin();
        commonQ.pop_front();
        commonQ.begin()->set_status(true);
        return memRef;
    }
    else if(commonQ.size() == 1)
    {
        pid memRef = *commonQ.begin();
        commonQ.pop_front();
        return memRef;
    }
    else
    {
        pid memRef = pid(0,0,"proxy",false,0,0);
        return memRef;
    }

}

pid theQueues::terminateAR()
{
    if(arQ.size() > 1)
    {
        pid memRef = *arQ.begin();
        arQ.pop_front();
        arQ.begin()->set_status(true);
        return memRef;
    }
    else if (arQ.size() == 1)
    {
        pid memRef = *arQ.begin();
        arQ.pop_front();
        if(commonQ.size() > 0)
        {
            commonQ.begin()->set_status(true);
            return memRef;
        }
        else
            return memRef;
    }
    else
    return terminateCommon();

}
