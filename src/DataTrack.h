//
// Created by zeno on 18-9-13.
//

#ifndef UNTITLED_DATATRACK_H
#define UNTITLED_DATATRACK_H

#include <fstream>
#include "HandleData.h"
#include "../lib/Encrypt.h"
#include "../lib/cJSON.h"
#include "Monitor.h"

struct ExpData {
    char studentID[20];
    char name[20];
    char classID[20];
    char taskID[20];
    long int startTime;
    long int endTime;
};

class DataTrack {
private:
    std::ofstream out;

    void printExpData(ExpData &);
    void getStudentInfo(ExpData &);

    Encrypt *encryptor;

public:
    DataTrack();
    ~DataTrack();

    static char CMDHIS[];
    static char CMDENCRYPT[];
    static char EXPDATA[];
    static char EXPENCRYPT[];
    static char LASTCOMM[];
    static char LASTENCRYPT[];

    void getCMDHistory();
    void getExpData();
    int moniProcRunTime();


    void getLastcomm();
};


#endif //UNTITLED_DATATRACK_H
