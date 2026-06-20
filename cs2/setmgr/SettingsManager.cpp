#include "SettingsManager.h"
#include "../utils/XorStr.h"


#include "rapidjson/document.h"

#include <fstream>
#include <sstream>
#include <filesystem>

void SettingsManager::LoadSettings()
{
    std::string cfgFile = XS("config.json");
    if (!std::filesystem::exists(cfgFile)) {
        std::cout << XS("[*] Config file not found!") << std::endl;
        return;
    }
	std::cout << XS("[*] Config file found") << std::endl;
    std::string readeddata;
    std::ifstream file(cfgFile);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    readeddata = buffer.str();
    rapidjson::Document kmboxdata;
    kmboxdata.Parse(readeddata.c_str());

    this->type = kmboxdata[XS("type").c_str()].GetString();
    this->language = kmboxdata[XS("en").c_str()].GetString(); // en or ch

    if ((this->type != XS("net")) && (this->type != XS("net+"))) return;

    this->ip = kmboxdata[XS("ip").c_str()].GetString();
    this->port = kmboxdata[XS("port").c_str()].GetInt64();
    this->uuid = kmboxdata[XS("uuid").c_str()].GetString();

    return;
}
