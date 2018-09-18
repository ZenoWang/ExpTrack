//
// Created by zeno on 18-9-13.
//

#include "Monitor.h"

using namespace std;

time_t Monitor::startTime = 0;
time_t Monitor::endTime = 0;

bool Monitor::isExpStart() {
    string s[10];
    long int len = 0;

    while (1) {
        system("w -h > wtemp");
        ifstream is("wtemp", std::ifstream::in);

        if (is.is_open()) {
            while (!is.eof()) {
                for (int i=0;i<3;i++) {
                    is >> s[i];
                    cout << s[i] << endl;
                }
                len = s[2].length();
                if (len > 10) {
                    ip = s[2];
                    time(&startTime);
                    cout << "开始时间： " << startTime << endl;
                    is.close();
                    return true;
                }
                getline(is, s[3]);
                cout << s[3] << endl;
            }
        }
        is.close();
        sleep(2);
    }

}

bool Monitor::isExpEnd() {
    string s[10];
    long int len = 0;
    bool findIp = false;

    while (1) {
        system("w -h > wtemp");
        ifstream is("wtemp", std::ifstream::in);

        if (is.is_open()) {
            findIp = false;
            while (!is.eof()) {
                for (int i=0;i<3;i++) {
                    is >> s[i];
                    cout << s[i] << endl;
                }
                if (s[2]==ip) {
                    findIp = true;
                }
                getline(is, s[3]);
                cout << s[3] << endl;
            }
        }
        is.close();
        if (!findIp) {
            time(&endTime);
            cout << "结束时间： " << endTime << endl;
            HandleData hd;
            char s[] = "wtemp";
            hd.RM(s);
            return true;
        }
        sleep(2);
    }
}

long int Monitor::getStartTime() {
    return startTime;
}

long int Monitor::getEndTime() {
    return endTime;
}