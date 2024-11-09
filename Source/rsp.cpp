#include "rsp.hpp"
#include <memory>

namespace rsp {
    App::App()
    : m_isRunning(true), m_port(3388), m_ip("127.0.0.1") {
        m_config = std::make_unique<Config>("default.cfg");

        m_port = std::abs(std::atoi(m_config->Get("port").c_str()));
        RSP_LOG("port - " + std::to_string(m_port));

        m_ip = m_config->Get("ip");
        RSP_LOG("ip - " + m_ip);

        m_socket = std::make_unique<Socket>(m_port, m_ip);
    }

    int App::Run() {
        if(m_isRunning) {
            m_socket->Connect();
        }

        return m_isRunning;
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
    return app->Run();
}