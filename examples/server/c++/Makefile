CC = g++
TARGETS = demo
CFLAGS = -g -I/usr/local/include/jsoncpp
LIBS = -lcrypto   -L/usr/local/lib -ljsoncpp -lcurl
OBJS = demo.o CryptHelper.o Sdk.o

%.o : %.cpp
	    $(CC) $(CFLAGS) $< -c $(CFLAGS)

$(TARGETS): $(OBJS)
	    $(CC) $^ $(LIBS) -o $@

clean :
	rm -f *.o $(TARGETS)
