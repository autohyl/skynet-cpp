#include "skynet_daemon.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int Operator_Pid::check_pid() {
    ifstream input(pidfile_.c_str(), ios::in);
    if (!input)
        return 0;
    
    int pid = 0;
    input >> pid;

    input.close();

    if (pid == 0 || pid == getpid()) {
		return 0;
	}

	if (kill(pid, 0) && errno == ESRCH)
		return 0;

	return pid;
}

int Operator_Pid::write_pid() {
    FILE *f;
	int pid = 0;
	int fd = open(pidfile, O_RDWR|O_CREAT, 0644);
	if (fd == -1) {
		std:: cerr << "Can't create pidfile ["<< pidfile << "]." << std::endl;
		return 0;
	}
	f = fdopen(fd, "r+");
	if (f == NULL) {
		fprintf(stderr, "Can't open pidfile [%s].\n", pidfile);
		return 0;
	}

	if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
		int n = fscanf(f, "%d", &pid);
		fclose(f);
		if (n != 1) {
			fprintf(stderr, "Can't lock and read pidfile.\n");
		} else {
			fprintf(stderr, "Can't lock pidfile, lock is held by pid %d.\n", pid);
		}
		return 0;
	}

	pid = getpid();
	if (!fprintf(f,"%d\n", pid)) {
		fprintf(stderr, "Can't write pid.\n");
		close(fd);
		return 0;
	}
	fflush(f);

	return pid;
}

int Skynet_Daemon::daemo_init(const std::string pidfile) {
    int pid = oppid_.check_pid();
    if (pid) {
		std::cerr << "Skynet is already running, pid = " << pid << "." << std::endl;
		return 1;
	}

#ifdef __APPLE__
	std::cerr << "'daemon' is deprecated: first deprecated in OS X 10.5 , use launchd instead." << std::endl;
#else
	if (daemon(1, 1)) {
		std::cerr << "Can't daemonize." << std::endl;
		return 1;
	}
#endif

	pid = oppid_.write_pid();
	if (pid == 0) {
		return 1;
	}

	if (redirect_fds()) {
		return 1;
	}

	return 0;
}

int Skynet_Daemon::daemo_exit() {

}