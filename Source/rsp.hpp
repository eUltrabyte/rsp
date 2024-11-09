#pragma once
#ifndef RSP_HEADER
#define RSP_HEADER

#include "Platform.hpp"
#include "Config.hpp"
#include "Socket.hpp"

namespace rsp {
    class App {
    public:
        App();
        virtual ~App() = default;

        virtual int Run();

        virtual Config* GetConfig();
        virtual uint16_t& GetPort();
        virtual std::string& GetIP();

    private:
        bool m_isRunning;
        std::unique_ptr<Config> m_config;
        uint16_t m_port;
        std::string m_ip;
        std::unique_ptr<Socket> m_socket;

    };
};

#endif
