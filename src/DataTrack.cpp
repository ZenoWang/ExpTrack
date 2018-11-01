//
// Created by zeno on 18-9-13.
//

#include "DataTrack.h"


char DataTrack::CMDHIS[] = "CMDHistory";

char DataTrack::CMDENCRYPT[] = "CMDEncrypt";

char DataTrack::EXPDATA[] = "ExpData";

char DataTrack::EXPENCRYPT[] = "ExpEncrypt";

char DataTrack::LASTCOMM[] = "Lastcomm";

char DataTrack::LASTENCRYPT[] = "LastEncrypt";

DataTrack::DataTrack() {
    encryptor = new Encrypt();
}

//启动线程方法
void DataTrack::getCMDHistory() {
    char sh[] = "FlushHistory.sh";
    out.open(sh, std::ofstream::out);
    if (out.is_open()) {
        out << "#!/bin/bash\n" <<
            "HISTFILE=~/.bash_history\n" <<
            "set -o history\n" <<
            "history -a\n" <<
            "history\n\n" <<
            "exit 0";
    }
    out.close();

    system("chmod +x FlushHistory.sh");
    std::string cmd = "./FlushHistory.sh > ";
    cmd.append(CMDHIS);
    system(cmd.c_str());

    HandleData hd;
    hd.RM(sh);

    encryptor->encrypt(CMDHIS, CMDENCRYPT);

#ifndef DEBUG
    hd.RM(CMDHIS);
#endif

}

int DataTrack::moniProcRunTime() {

    return system("accton on");

}

void DataTrack::getExpData() {
    ExpData expData;
    Monitor m;
    expData.startTime = m.getStartTime();
    expData.endTime = m.getEndTime();
    getStudentInfo(expData);

    printExpData(expData);

    encryptor->encrypt(EXPDATA, EXPENCRYPT);

#ifndef DEBUG
    HandleData hd;
    hd.RM(EXPDATA);
#endif

}

void DataTrack::printExpData(ExpData &expData) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "startTime", expData.startTime);
    cJSON_AddNumberToObject(json, "endTime", expData.endTime);
    cJSON_AddItemToObject(json,"studentID",cJSON_CreateString(expData.studentID));
    cJSON_AddItemToObject(json,"classID",cJSON_CreateString(expData.classID));
    cJSON_AddItemToObject(json,"name",cJSON_CreateString(expData.name));
    cJSON_AddItemToObject(json,"taskID",cJSON_CreateString(expData.taskID));

    char *buffer = cJSON_Print(json);
    cJSON_Delete(json);

    out.open(EXPDATA, std::ofstream::out);
    out << buffer << "\n";
    free(buffer);

    out.close();
}

void DataTrack::getStudentInfo(ExpData &expData) {
    //引导学生输入学号，姓名，课程号，作业号
    strcpy(expData.studentID, "");
    strcpy(expData.classID, "");
    strcpy(expData.name, "");
    strcpy(expData.taskID, "");
}

void DataTrack::getLastcomm() {
    std::string cmd = "lastcomm zeno > ";
    cmd.append(LASTCOMM);
    system(cmd.c_str());

    encryptor->encrypt(LASTCOMM, LASTENCRYPT);

#ifndef DEBUG
    HandleData hd;
    hd.RM(LASTCOMM);
#endif
}

DataTrack::~DataTrack() {
    delete encryptor;
}