//
// Created by zeno on 18-9-13.
//

#include "HandleData.h"


void HandleData::RM(char *file) {
    char cmd[64] = "rm -f ";
    strcat(cmd,file);

    puts(cmd);
    system(cmd);
}

void HandleData::Tar(char *file1, char *file2) {
    std::string cmd = "tar -zcv -f ~/ExpTracData.tar.gz ";
    cmd.append(file1);
    cmd.append(" ");
    cmd.append(file2);
    system(cmd.c_str());
}