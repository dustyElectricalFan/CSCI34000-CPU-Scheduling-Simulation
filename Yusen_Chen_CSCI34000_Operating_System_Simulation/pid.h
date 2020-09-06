//Yusen Chen

#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED
#include <string>
#include <iostream>
class pid
{
public:
    pid();
    pid(long long int id, long long int datasize, std::string datatype, bool now, long long int startRange, long long int endRange);
    long long int getID();
    long long int get_datasize();
    std::string get_type();
    std::string get_status();
    void set_status(bool now);
    void printself();
    void printselfAR();
    long long int getStart();
    long long int getEnd();



private:
long long int ID;
long long int data_size;
std::string process_type;
std::string status;
long long int rangeStart;
long long int rangeEnd;

};


#endif // PID_H_INCLUDED
