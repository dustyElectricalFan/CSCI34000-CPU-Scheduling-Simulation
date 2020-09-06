//Yusen Chen

#include "simulatedOS.h"


std::pair<std::string,std::string> simulatedOS::getInputs()
{
    std::cout << "Please enter amount of RAM (in bytes):    " << '\n';
    std::string ramSize;
    std::string hardDiskNum;


    bool bothChecker = false;

    while(!bothChecker)
    {
        getline(std::cin,ramSize);
        if(ramSize == "exit")
            exit(0);

        long long int counter = 0;
        long long int orgSize = ramSize.length();
        for(long long int f = 0; f < ramSize.length(); f++)
        {
            if(ramSize[f] == ' ' || ramSize[f] == '\t')
            {
                ramSize.erase(f,1);
                f--;
                counter++;
            }
        }
        if(counter == orgSize)
        {
            std::cout << "You only entered in whitespace/tabs. What are you doing? Please re-enter the RAM size" << '\n';
            continue;
        }


        bothChecker = true;


        for(long long int i = 0; i < ramSize.length(); i++)
        {
          if(ramSize[0] == '0' || ramSize[i] < '0' || ramSize[i] > '9')
          {
            std::cout << "invalid RAM size input please re-enter only whole numeric values" << '\n';
            bothChecker = false;
            break;
          }
        }

        if(ramSize.length() < 1 || !bothChecker)
            continue;

        if(std::stoll(ramSize) > 4000000000 || ramSize.length() > 10)
        {
            std::cout << "Invalid RAM size. Maximum amount of RAM is up to 4 bil bytes" << '\n';
            bothChecker = false;
            continue;
        }
    }


    bothChecker = false;

    std::cout << "Please enter number of hard disks:   " << '\n';


    while(!bothChecker)
    {
        getline(std::cin,hardDiskNum);

        if(hardDiskNum == "exit")
             exit(0);

        long long int counter = 0;
        long long int orgSize = hardDiskNum.length();
        for(long long int f = 0; f < hardDiskNum.length(); f++)
        {
            if(hardDiskNum[f] == ' ' || hardDiskNum[f] == '\t')
            {
                hardDiskNum.erase(f,1);
                f--;
                counter++;
            }
        }
        if(counter == orgSize)
        {
            std::cout << "You only entered in whitespace/tabs. What are you doing? Please re-enter the hard disk number." << '\n';
            continue;
        }


        bothChecker = true;

        for(long long int i = 0; i < hardDiskNum.length(); i++)
        {
            if(hardDiskNum[0] == '0' || hardDiskNum[i] < '0' || hardDiskNum[i] > '9')
            {
                std::cout << "invalid number of hard disks. Please re-enter only whole numeric values" << '\n';
                bothChecker = false;
                break;
            }
        }
        if(hardDiskNum.length() < 1 || !bothChecker)
            continue;


        if(std::stoll(hardDiskNum) > 4000000000 || hardDiskNum.length() > 10)
        {
            std::cout << "Invalid harddisk number. Maximum amount of hard disks is up to 4 bil." << '\n';
            bothChecker = false;
            continue;
        }
     }

    return std::make_pair(ramSize,hardDiskNum);
}

bool simulatedOS::aCommand(std::string command)
{
    if(command.length() > 1 && command.substr(0,1) == "A" && command.substr(1,1) != "R")
        {
            std::string proxy = command.substr(1);
            if((proxy.find_first_not_of("0123456789")) && proxy.substr(0,1)!= "0")
            {
                if(!simRam.checkSize(std::stoll(proxy)))
                    std::cout << "Process data is too big for RAM" << '\n';
                else
                {
                    pid newEntry = simRam.insertPid(std::stoll(proxy),"common");
                    if(newEntry.get_status() != "unknown")
                        mainQ.enqueCommon(newEntry);
                    else
                        std::cout << "There is no available space in RAM for the process" << '\n';
                }
                return true;
           }
           return false;
        }
    else
        return false;
}

bool simulatedOS::arCommand(std::string command)
{
    if(command.length() > 2 && command.substr(0,2) == "AR")
        {
            std::string proxy = command.substr(2);
            if((proxy.find_first_not_of("0123456789")) && proxy.substr(0,1)!= "0")
                {
                    if(!simRam.checkSize(std::stoll(proxy)))
                        std::cout << "process data is too big for RAM" << '\n';

                    else
                    {
                        pid newEntry = simRam.insertPid(std::stoll(proxy),"AR");
                        if(newEntry.get_status() != "unknown")
                            mainQ.enqueAR(newEntry);
                        else
                            std::cout << "There is no available space in RAM for the process" << '\n';
                    }
                    return true;
               }
        return false;
        }
    else
        return false;
}

bool simulatedOS::qCommand(std::string command)
{
    if(command == "Q")
        {
            if(!mainQ.isAREmpty())
            {
                mainQ.dequeAR();
            }
            else if(mainQ.isAREmpty() && !mainQ.isCommonEmpty())
            {
               mainQ.dequeCommon();
            }
            else
            {
               std::cout << "Both queues are empty." << '\n';
            }
            return true;
        }
    else
       return false;
}

bool simulatedOS::tCommand(std::string command)
{
    if(command == "t")
        {
            pid memRef = mainQ.terminateAR();
            if(simRam.getSize() < 1 || memRef.getID() == 0)
                std::cout << "The is no process to terminate" << '\n';
            else
                simRam.deletePid(memRef.getID());

          return true;
        }
    else
        return false;
}

bool simulatedOS::DCommand(std::string command)
{
    if(command.length() > 1 && command.substr(0,1) == "D")
        {
            std::string proxy = command.substr(1);
            if(proxy.find_first_not_of("0123456789"))
            {
                if(std::stoll(proxy) > theDisks.getNumOfDisks() -1)
                    std::cout << "No Disc of that number" << '\n';
                else
                {
                   if(!theDisks.isEmpty(std::stoll(proxy)))
                   {
                       pid memRef = theDisks.dequePid(std::stoll(proxy));
                       if(memRef.get_type() == "common")
                        mainQ.enqueCommon(memRef);
                       else
                        mainQ.enqueAR(memRef);
                   }
                   else
                    std::cout << "The disk is currently servicing no processes" << '\n';
                return true;
                }
            }
            return false;
        }
        else
            return false;
}

bool simulatedOS::dCommand(std::string command)
{
    if(command.length() > 1 && command.substr(0,1) == "d")
        {
            std::string proxy = command.substr(1);
            if(proxy.find_first_not_of("0123456789"))
            {
                if(std::stoll(proxy) > theDisks.getNumOfDisks() - 1)
                    std::cout << "No Disc of that number" << '\n';
                else
                {
                    pid memRef = mainQ.terminateAR();
                    if(memRef.getID() != 0)
                    theDisks.enquePid(memRef,std::stoll(proxy));
                    else
                    std::cout << "There are no running processes" << '\n';
                }
                return true;
            }
            return false;
        }
        else
            return false;
}

bool simulatedOS::srCommand(std::string command)
{
    if(command == "Sr")
            {
                mainQ.printCommon();
                mainQ.printAR();
                return true;
            }
            else
                return false;
}

bool simulatedOS::siCommand(std::string command)
{
    if(command == "Si")
    {
        theDisks.printAll();
        return true;
    }
    else
        return false;


}

bool simulatedOS::smCommand(std::string command)
{
    if(command == "Sm")
    {
        simRam.readMem();
        return true;
    }
    else
        return false;

}


void simulatedOS::startSimulation()
{

    std::pair<std::string,std::string> startPair = getInputs();
    mainQ = theQueues();
    simRam = simulatedRam(std::stoll(startPair.first));
    theDisks = hardDisk(std::stoll(startPair.second));

    std::string command;
    bool arSingle = false;
    while(getline(std::cin,command))
    {
        if(command == "exit")
            exit(0);

        if(command.find_first_of("A") < command.length())
        {
            if(command.find_first_of("R") < command.length())
            {
                if(command.find_first_of("R") - command.find_first_of("A") != 1)
                {
                    std::cout << "Invalid input! AR is a single command with no spaces in between!" << '\n';
                    arSingle = true;
                }

            }
        }


        for(long long int i = 0; command[i]; i++)
            if(command[i] == ' ' || command[i] == '\t')
            {
                command.erase(i,1);
                i--;
            }

        if(command.length() > 12 || command.empty())
        {
            std::cout << "INVALD INPUT" << '\n';
            arSingle = false;
            continue;
        }



        bool commandSuccess = false;
        while(!commandSuccess)
        {
        commandSuccess = aCommand(command);
        if(commandSuccess)
            break;
        if(!arSingle)
            commandSuccess = arCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = qCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = tCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = dCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = DCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = srCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = siCommand(command);
        if(commandSuccess)
            break;
        commandSuccess = smCommand(command);
        break;
        }
        if(!commandSuccess)
            std::cout << "INVALID INPUT" << '\n';

        arSingle = false;

    }
}



