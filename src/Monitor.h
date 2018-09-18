//
// Created by zeno on 18-9-13.
//

#ifndef UNTITLED_MONITOR_H
#define UNTITLED_MONITOR_H

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "HandleData.h"

class Monitor {

private:
    static time_t startTime;
    static time_t endTime;


    std::string ip;

public:

    bool isExpStart();
    bool isExpEnd();

    long int getStartTime();
    long int getEndTime();

};


#endif //UNTITLED_MONITOR_H
