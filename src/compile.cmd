g++ -Os -g main.cpp rpc.pb.cc BlobProto.pb.cc ExecutionProto.pb.cc LocalProto.pb.cc -Ic:/Boost/include/boost-1_42 -Ic:/A/contester/protobuf-mingw32/include -D_WIN32_WINNT=0x0501 -lws2_32 -Lc:/Boost/lib -llibboost_system-mgw44-mt -Lc:/A/contester/protobuf-mingw32/lib -lprotobuf