#include "skynet_start.h"

int Skynet_Start::SIG  = 0;

void Skynet_Start::start() {
    // register SIGHUP for log file reopen
	struct sigaction sa;
	sa.sa_handler = &handle_hup;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);

    if (skynet_config->daemon.size()) {
		//if (daemon_init(config->daemon)) {
			//exit(1);
		//}
	}
}