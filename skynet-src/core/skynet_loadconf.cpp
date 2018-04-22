#include "skynet_loadconf.h"
#include <assert.h>
#include <string.h>
#include <iostream>
#include <sstream>

const char *Skynet_LoadConfig::load_config = "\
	local result = {}\n\
	local function getenv(name) return assert(os.getenv(name), [[os.getenv() failed: ]] .. name) end\n\
	local sep = package.config:sub(1,1)\n\
	local current_path = [[.]]..sep\n\
	local function include(filename)\n\
		local last_path = current_path\n\
		local path, name = filename:match([[(.*]]..sep..[[)(.*)$]])\n\
		if path then\n\
			if path:sub(1,1) == sep then	-- root\n\
				current_path = path\n\
			else\n\
				current_path = current_path .. path\n\
			end\n\
		else\n\
			name = filename\n\
		end\n\
		local f = assert(io.open(current_path .. name))\n\
		local code = assert(f:read [[*a]])\n\
		code = string.gsub(code, [[%$([%w_%d]+)]], getenv)\n\
		f:close()\n\
		assert(load(code,[[@]]..filename,[[t]],result))()\n\
		current_path = last_path\n\
	end\n\
	setmetatable(result, { __index = { include = include } })\n\
	local config_name = ...\n\
	include(config_name)\n\
	setmetatable(result, nil)\n\
	return result\n\
";

void Skynet_LoadConfig::init() {
    config.thread =  8;
	config.module_path = "./cservice/?.so";
	config.harbor = 1;
	config.bootstrap = "snlua bootstrap";
	config.daemon = "";
	config.logger = "";
	config.logservice = "logger";
	config.profile = 1;
}

bool Skynet_LoadConfig::load_config_file(const char* config_file) {
    int err = luaL_loadbufferx(L, load_config, strlen(load_config), "=[skynet config]", "t");
    assert(err == LUA_OK);
    lua_pushstring(L, config_file);

    err = lua_pcall(L, 1, 1, 0);
    if (err) {
        std::cerr << lua_tostring(L, -1) << std::endl;
        return false;
    }

    lua_pushnil(L);
    while (lua_next(L, -2)) {
        int keyt = lua_type(L, -2);
        if (keyt != LUA_TSTRING) {
            std::cerr << "Invalid config table" << std::endl;
            return false;
        }

        const char* key = lua_tostring(L, -2);
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            int b = lua_toboolean(L, -1);
            set_opt(key, b);
        }
        else {
            const char* value = lua_tostring(L, -1);
            if (value == NULL) {
                std::cerr << "Invalid config table key = " << key << std::endl;
                return false;
            }
            std::string value_str = value;
            set_opt(key, value_str);
        }
        lua_pop(L, 1);
    }
    lua_pop(L, -1);
    return true;
}

template <class T>
void Skynet_LoadConfig::set_opt(const char* key, T value) {
    std::stringstream os;
    os << value;
    std::string key_str = key;
    if (key_str == "thread") {
        os >> config.thread;
    }
    else if (key_str == "cpath") {
        os >> config.module_path;
    }
    else if (key_str == "harbor") {
        os >> config.harbor;
    }
    else if (key_str == "bootstrap") {
        os >> config.bootstrap;
    }
    else if (key_str == "daemon") {
        os >> config.daemon;
    }
    else if (key_str == "logger") {
        os >> config.logger;
    }
    else if (key_str == "logservice") {
        os >> config.logservice;
    }
    else if (key_str == "profile") {
        os >> config.profile;
    }
    else {
        //std::cerr << "error config key " << key << std::endl;
    }
}