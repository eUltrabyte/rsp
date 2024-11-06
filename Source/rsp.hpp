#pragma once
#ifndef RSP_HEADER
#define RSP_HEADER

#if defined(_WIN32)
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    #define RSP_WINDOWS
#elif defined(__linux__)
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define RSP_LINUX
#else
    #error "rsp >> error - unknown operating system"
#endif

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#endif