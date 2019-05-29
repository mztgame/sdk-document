CC =g++
TARGETS = demo
#CFLAGS = -ggdb  -I/usr/local/include/jsoncpp -std=c++11
CFLAGS = -ggdb  -I/usr/local/include/jsoncpp 
LIBS = -lcrypto    -L/usr/local/lib -ljsoncpp -lcurl
OBJS = demo.o CryptHelper.o Sdk.o

%.o : %.cpp
	    $(CC) $(CFLAGS) $< -c $(CFLAGS)

$(TARGETS): $(OBJS)
	    $(CC) $^ $(LIBS) -o $@

clean :
	rm -f *.o $(TARGETS)
