#include <lua.hpp>
#include <string>

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

class LoadConf {
public:
    LoadConf(struct lua_State *l) : L(l) {
        luaL_openlibs(L);	// link lua libs
        init();
    }
    LoadConf() {
        L = luaL_newstate();
        luaL_openlibs(L);	// link lua libs
        init();
    }
    ~LoadConf() {
        lua_close(L);
    }
    
    bool load_config_file(const char* config_file);

    template <class T>
    void set_opt(const char* key, T value);

private:

    void init(); //初始化一些配置

    struct lua_State *L; //operator lua config
    static const char *load_config;
    struct skynet_config config;
};