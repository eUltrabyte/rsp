#pragma once
#ifndef RSP_HEADER
#define RSP_HEADER

#include "Platform.hpp"

namespace rsp {
    class App {
    public:
        App();
        virtual ~App() = default;

        virtual uint16_t& GetPort();
        virtual std::string& GetIP();
        virtual std::string& GetConfigName();

    private:
        uint16_t m_port;
        std::string m_ip;
        std::string m_configName;

    };
};

#endif
