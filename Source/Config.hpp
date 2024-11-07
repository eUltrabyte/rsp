#pragma once
#ifndef RSP_CONFIG_HEADER
#define RSP_CONFIG_HEADER

#include "Platform.hpp"

namespace rsp {
    class Config {
    public:
        Config(std::string_view filename = "default.cfg", std::string_view path = "");
        virtual ~Config() = default;

        virtual bool Exist();
        virtual std::string Get(std::string_view parameter);

        virtual std::string& GetFilename();
        virtual std::string& GetPath();

    private:
        std::string m_filename;
        std::string m_path;
        std::vector<std::string> m_data;

    };
};

#endif
