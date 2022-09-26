#include "../inc/recovery.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Inappropriate usage. Should be: demo <video path>." << endl;
        return -1;
    }

    Recovery recover;
    recover.readVideo(argv[1]);
    recover.process();
    recover.showResult();
    return 0;
}
