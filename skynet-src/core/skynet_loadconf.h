#ifndef __SKYNET_LOADCONF_H__
#define __SKYNET_LOADCONF_H__

#include <lua.hpp>
#include <string>
#include "singletion.h"

struct skynet_config {
	int thread;
	int harbor;
	int profile;
	std::string daemon;
	std::string module_path;
	std::string bootstrap;
	std::string logger;
	std::string logservice;
};

class Skynet_LoadConfig {
public:
    Skynet_LoadConfig(struct lua_State *l) : L(l) {
        luaL_openlibs(L);	// link lua libs
        init();
    }
    Skynet_LoadConfig() {
        L = luaL_newstate();
        luaL_openlibs(L);	// link lua libs
        init();
    }
    ~Skynet_LoadConfig() {
        lua_close(L);
    }
    
    bool load_config_file(const char* config_file);

    const skynet_config* getConfig() const {
        return &config;
    }

    template <class T>
    void set_opt(const char* key, T value);

private:

    void init(); //��ʼ��һЩ����

    struct lua_State *L; //operator lua config
    static const char *load_config;
    struct skynet_config config;
};

#endif