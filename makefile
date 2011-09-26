
BOOST := c:/Boost
PROTOBUF := c:/A/protobuf-2.4.1
RUNLIB32 := c:/A/runlib-win32
SOURCES := src/w32invoke.c src/pipes.c src/winmisc.c src/inject.c
HEADERS := src/pipes.h src/winmisc.h src/inject.h
EXT_HEADERS := include/w32invoke.h include/win32-gcc.h include/msstdint.h
CXX := g++.exe
CPPFLAGS := -pipe -Wall -g -Os -I$(BOOST)/include -I$(PROTOBUF)/include -I$(RUNLIB32)/include -D_WIN32_WINNT=0x0501 -DBOOST_THREAD_USE_LIB -Isrc/
LDFLAGS := -pipe -Wl,--allow-multiple-definition -Wall -g -Os -mno-cygwin -lws2_32 -L$(BOOST)/lib -Wl,-Bstatic -lboost_date_time-mt -lboost_system-mt -lboost_thread-mt -L$(PROTOBUF)/lib -lprotobuf -L$(RUNLIB32)/src -lrunlib32-static -Wl,-Bdynamic -ladvapi32 -lpsapi -luserenv -lmswsock


build/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

all: build/main.exe

build:
	mkdir build

build/rpc.pb.o: src/rpc.pb.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

build/rpc_object.o: src/rpc_object.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

build/rpc_object_session.o: src/rpc_object_session.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

build/rpc_session.o: src/rpc_session.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

build/rpc_server.o: src/rpc_server.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^
                              
build/librpc.a: build/rpc.pb.o build/rpc_object.o build/rpc_object_session.o build/rpc_session.o build/rpc_server.o
	ar.exe rcs $@ $^

build/main.o: src/main.cc 
	$(CXX) $(CPPFLAGS) -c -o $@ $^

build/main.exe: build/main.o build/librpc.a build/contester/proto/LocalProto.pb.o build/contester/proto/BlobProto.pb.o build/contester/proto/ExecutionProto.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: all