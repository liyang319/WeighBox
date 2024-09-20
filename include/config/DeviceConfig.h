/**
 * @Class MyConfig
 * @Brief 配置管理类，实现对配置文件ControlBox.ini文件的解析，配置项的获取等 */

#pragma once

#include <sstream>
#include <map>
#include <string>

using namespace std;

#define DEFAULT_CONFIG_FILE_NAME "WeighsBox.ini"

class DeviceConfig
{
    map<string, string> iniMap;

private:
    int init();
    string trimString(string &str);
    void readConfig();
    std::string getComment(const std::string &line);
    std::string configFile;

public:
    DeviceConfig(/* args */);
    static DeviceConfig &getInstance()
    {
        static DeviceConfig instance;
        return instance;
    }
    ~DeviceConfig();

    string getValue(string key);
    void setValue(const std::string &key, const std::string &value);
    void saveConfig();
    map<string, string> getConfigMap();
};
