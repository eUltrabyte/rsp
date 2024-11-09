#pragma once
#ifndef RSP_PLATFORM_HEADER
#define RSP_PLATFORM_HEADER

#if defined(_WIN32)
    #include <winsock2.h>
    #include <io.h>
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

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

#if defined(RSP_DEBUG)
    #define RSP_LOG(x) { std::cout << "rsp [log] >> " << x << '\n'; }
    #define RSP_ERROR(x) { std::cout << "rsp [error] >> " << x << '\n'; }
#else
    #define RSP_LOG(x) 
    #define RSP_ERROR(x)
#endif

#endif
