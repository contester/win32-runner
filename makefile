
SOURCES := src/w32invoke.c src/pipes.c src/winmisc.c src/inject.c
HEADERS := src/pipes.h src/winmisc.h src/inject.h
EXT_HEADERS := include/w32invoke.h include/win32-gcc.h include/msstdint.h
CXX := g++.exe
CPPFLAGS := -pipe -Wall -g -Os -mno-cygwin -Ic:/Boost/include/boost-1_42 -Ic:/A/contester/protobuf-mingw32/include -I../runlib32/include -D_WIN32_WINNT=0x0501
LDFLAGS := -pipe -Wall -g -Os -mno-cygwin -lws2_32 -Lc:/Boost/lib -llibboost_system-mgw44-mt -Lc:/A/contester/protobuf-mingw32/lib -lprotobuf -L../runlib32/build -lrunlib32-static -ladvapi32 -lpsapi -luserenv -lmswsock -lrunlib32-static


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

build/main.exe: build/main.o build/librpc.a build/LocalProto.pb.o build/BlobProto.pb.o build/ExecutionProto.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: all