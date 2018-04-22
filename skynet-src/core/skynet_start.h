#ifndef __SKYNET_START_H__
#define __SKYNET_START_H__

#include <signal.h>
#include "skynet_loadconf.h"

#define skynet_config Singletion<Skynet_LoadConfig>::install().getConfig()

class Skynet_Start {
public:
    Skynet_Start() {}
    ~Skynet_Start() {}

    void start();

private:
    static void handle_hup(int signal) {
        if (signal == SIGHUP) {
            SIG = 1;
        }
    }
    static int SIG;
};

#endif