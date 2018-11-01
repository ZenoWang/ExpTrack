#include "src/Monitor.h"
#include "src/DataTrack.h"
#include <iostream>
//#define  DEBUG

int main() {
    Monitor monitor;
    DataTrack dt;
    HandleData hd;


#ifndef DEBUG
    if (monitor.isExpStart()) {
        //监控到学生连接
        if (dt.moniProcRunTime() < 0) {
            std::cout << "开启accton服务失败" << std::endl;

            return -1;
        }
        if (monitor.isExpEnd()) {

            dt.getCMDHistory();
            dt.getLastcomm();
            dt.getExpData();

            hd.Tar(DataTrack::CMDENCRYPT, DataTrack::EXPENCRYPT);
        }
    }
#endif

#ifdef DEBUG
    std::cout << "system : " << dt.moniProcRunTime() << std::endl;
    dt.getCMDHistory();
    dt.getExpData();
#endif

    return 0;
}