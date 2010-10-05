
BOOST := d:/Boost
PROTOBUF := d:/A/protobuf-mingw32
RUNLIB32 := d:/A/runlib-win32
SOURCES := src/w32invoke.c src/pipes.c src/winmisc.c src/inject.c
HEADERS := src/pipes.h src/winmisc.h src/inject.h
EXT_HEADERS := include/w32invoke.h include/win32-gcc.h include/msstdint.h
CXX := g++.exe
CPPFLAGS := -pipe -Wall -g -Os -mno-cygwin -I$(BOOST)/include/boost-1_44 -I$(PROTOBUF)/include -I$(RUNLIB32)/include -D_WIN32_WINNT=0x0501 -Isrc/
LDFLAGS := -pipe -Wall -g -Os -mno-cygwin -lws2_32 -L$(BOOST)/lib -lboost_system-mgw45-mt-1_44 -L$(PROTOBUF)/lib -lprotobuf -L$(RUNLIB32)/build -lrunlib32-static -ladvapi32 -lpsapi -luserenv -lmswsock -lrunlib32-static


build/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

all: build/main.exe

build:
	mkdir build

build/rpc.pb.o: src/rpc.pb.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/rpc_object.o: src/rpc_object.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/rpc_object_session.o: src/rpc_object_session.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/rpc_session.o: src/rpc_session.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/rpc_server.o: src/rpc_server.cc
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/librpc.a: build/rpc.pb.o build/rpc_object.o build/rpc_object_session.o build/rpc_session.o build/rpc_server.o
	ar.exe rcs $@ $^

build/main.o: src/main.cc 
	$(CXX) $(CPPFLAGS) -c -combine -o $@ $^

build/main.exe: build/main.o build/librpc.a build/contester/proto/LocalProto.pb.o build/contester/proto/BlobProto.pb.o build/contester/proto/ExecutionProto.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: all