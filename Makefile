LUA_STATICLIB := 3rd/lua/liblua.a
LUA_LIB ?= $(LUA_STATICLIB)
LUA_INC ?= 3rd/lua/

INC = -I./ -I$(LUA_INC)
LIB += $(LUA_STATICLIB) -ldl
CFLAGS = -g

TARGET = skynet

SKYNET_SRC = skynet-src
SKYNET_OBJ = $(SKYNET_SRC)/skynet_main.o

$(TARGET):$(SKYNET_OBJ)
	$(CXX) $(CFLAGS) $(INC) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<


$(LUA_STATICLIB):
	cd 3rd/lua && $(MAKE) CC='$(CC) -std=gnu99' linux

cleanall:
	cd 3rd/lua && $(MAKE) clean
	rm -f $(LUA_STATICLIB)
