LUA_STATICLIB := 3rd/lua/liblua.a
LUA_LIB ?= $(LUA_STATICLIB)
LUA_INC ?= 3rd/lua/

SKYNET_SRC = skynet-src
INC = -I./ -I$(LUA_INC) -I$(SKYNET_SRC)/core/
LIB += $(LUA_STATICLIB) -ldl
CFLAGS = -g

TARGET = skynet

SKYNET_OBJ = $(SKYNET_SRC)/skynet_main.o\
		$(SKYNET_SRC)/core/skynet_loadconf.o

$(TARGET):$(SKYNET_OBJ)
	$(CXX) $(CFLAGS) $(INC) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

$(LUA_STATICLIB):
	cd 3rd/lua && $(MAKE) CC='$(CC) -std=gnu99' linux

clean:
	rm -f $(TARGET)
	rm -f $(SKYNET_SRC)/core/*.o
	rm -f $(SKYNET_SRC)/*.o

cleanall: clean
	cd 3rd/lua && $(MAKE) clean
	rm -f $(LUA_STATICLIB)
