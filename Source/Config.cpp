#include "Config.hpp"

namespace rsp {
    Config::Config(std::string_view filename, std::string_view path)
    : m_filename(filename), m_path(path) {
        if(Exist()) {
            std::ifstream file(m_path + m_filename);
            std::string line;
            if(file.is_open()) {
                while(std::getline(file, line)) {
                    m_data.emplace_back(line);
                }

                file.close();
            }
        }
    }

    bool Config::Exist() {
        return std::filesystem::exists(m_path + m_filename);
    }

    std::string Config::Get(std::string_view parameter) {
        for(auto i = 0; i < m_data.size(); ++i) {
            if(m_data[i].find(parameter) != std::string::npos) {
                return m_data[i].substr(parameter.length() + 1, m_data[i].length());
            }
        }

        return "";
    }

    std::string& Config::GetFilename() {
        return m_filename;
    }
    
    std::string& Config::GetPath() {
        return m_path;
    }
};