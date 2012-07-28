
BOOST := c:/a/Boost
PROTOBUF := c:/a/protobuf
RUNLIB32 := c:/a/runlib32
RPCLIB := ../boost-rpclib
SOURCES := src/w32invoke.c src/pipes.c src/winmisc.c src/inject.c
HEADERS := src/pipes.h src/winmisc.h src/inject.h
EXT_HEADERS := include/w32invoke.h include/win32-gcc.h include/msstdint.h
CXX := g++.exe
CPPFLAGS := -pipe -Wall -g -Os -I$(BOOST)/include -I$(PROTOBUF)/include -I$(RUNLIB32)/include -I$(RPCLIB)/src -D_WIN32_WINNT=0x0501 -DBOOST_THREAD_USE_LIB -Isrc/
LDFLAGS := -pipe -static-libgcc -static-libstdc++ -Wl,--allow-multiple-definition -Wall -g -Os -L$(BOOST)/lib -Wl,-Bstatic -L$(RPCLIB)/src -lrpc -lboost_date_time-mt -lboost_system-mt -lboost_thread-mt -lboost_chrono-mt -L$(PROTOBUF)/lib -lprotobuf -L$(RUNLIB32)/src -lrunlib32 -Wl,-Bdynamic -lws2_32 -ladvapi32 -lpsapi -luserenv -lmswsock

libproto_sources := \
	src/contester/proto/LocalProto.pb.cc \
	src/contester/proto/BlobProto.pb.cc \
	src/contester/proto/ExecutionProto.pb.cc

sources := $(libproto_sources) src/main.cc

all: src/main.exe

%.d: %.cc
	$(CXX) -MM -MF $@ -MT $(@:.d=.o) $(CPPFLAGS) $< 

%.o: %.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $<

%.a: %.o
	$(AR) r $@ $*.o

include $(sources:.cc=.d)

src/libproto.a: $(libproto_sources:.cc=.o)
	$(AR) cr $@ $^

src/main.exe: src/main.o src/libproto.a
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: all
