#include "src/Monitor.h"
#include "src/DataTrack.h"

//#define  DEBUG

int main() {
    Monitor monitor;
    DataTrack dt;
    HandleData hd;


#ifndef DEBUG
    if (monitor.isExpStart()) {
        if (monitor.isExpEnd()) {
            dt.getCMDHistory();
            dt.getExpData();
            hd.Tar(DataTrack::CMDENCRYPT, DataTrack::EXPENCRYPT);
        }
    }
#endif

#ifdef DEBUG
    dt.getCMDHistory();
    dt.getExpData();
#endif

    return 0;
}