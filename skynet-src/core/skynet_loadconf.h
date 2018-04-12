extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LoadConf {
public:
    LoadConf(struct lua_State *l) : L(l) {
        luaL_openlibs(L);	// link lua libs
    }
    ~LoadConf() {
        lua_close(L);
    }
    
    bool load_config_file(const char* config_file);

private:
    struct lua_State *L;
    static const char *load_config;
};