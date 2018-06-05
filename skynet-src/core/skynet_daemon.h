#ifndef __SKYNET_DAEMON_H__
#define __SKYNET_DAEMON_H__

#include <string>

class Operator_Pid {
public:
    Operator_Pid(const std::string pidfile) : pidfile_(pidfile) {}
    int check_pid();
    int write_pid();

private:
    std::string pidfile_;
};

class Skynet_Daemon {
public:
    Skynet_Daemon(const std::string pidfile) : pidfile_(pidfile), oppid_(pidfile) {}
    int daemo_init();
    int daemo_exit();

private:
    std::string pidfile_;
    Operator_Pid oppid_;    
};

#endif