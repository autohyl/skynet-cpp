#include <iostream>
#include <assert.h>
#include <string.h>
#include "core/skynet_loadconf.h"
#include "core/singletion.h"
#include "core/skynet_start.h"

using namespace std;

int main(int argc, char ** argv) {
    const char * config_file = NULL;
	if (argc > 1) {
		config_file = argv[1];
	} else {
		cerr << "Need a config file." << endl;
		return 1;
	}

	//加载配置文件
	Singletion<Skynet_LoadConfig>::install().load_config_file(config_file);

	//启动服务
	Singletion<Skynet_Start>::install().start();

    return 0;
}