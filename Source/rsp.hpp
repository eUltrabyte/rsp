#pragma once
#ifndef RSP_HEADER
#define RSP_HEADER

#include "Platform.hpp"
#include "Config.hpp"

namespace rsp {
    class App {
    public:
        App();
        virtual ~App() = default;

        virtual Config* GetConfig();
        virtual uint16_t& GetPort();
        virtual std::string& GetIP();

    private:
        std::unique_ptr<Config> m_config;
        uint16_t m_port;
        std::string m_ip;

    };
};

#endif
