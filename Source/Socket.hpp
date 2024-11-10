#pragma once
#ifndef RSP_SOCKET_HEADER
#define RSP_SOCKET_HEADER

#include "Platform.hpp"

namespace rsp {
    class Socket {
    public:
        Socket(const uint16_t& port, std::string_view ip);
        virtual ~Socket() = default;

        virtual void Connect();

    private:
        #if defined(RSP_WINDOWS)
            SOCKET m_socket;
        #elif defined(RSP_LINUX)
            int m_socket;
        #endif

        sockaddr_in m_server;

    };
};

#endif
