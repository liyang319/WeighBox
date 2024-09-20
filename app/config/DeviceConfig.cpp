#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include "DeviceConfig.h"
#include "Base.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

using namespace std;
using namespace rapidjson;

DeviceConfig::DeviceConfig(/* args */)
{
    init();
}

DeviceConfig::~DeviceConfig()
{
}

int DeviceConfig::init()
{
    this->configFile = DEFAULT_CONFIG_FILE_NAME;
    try
    {
        this->readConfig();
    }
    catch (const exception &e)
    {
        CERR << "Error: " << e.what() << endl;
    }

    return 0;
}

void DeviceConfig::readConfig()
{
    std::ifstream file(configFile);
    string line;
    if (!file.is_open())
    {
        throw runtime_error("Unable to open file");
    }

    while (getline(file, line))
    {
        istringstream is_line(line);
        string key;

        if (getline(is_line, key, '='))
        {
            key = trimString(key);

            string value;
            if (getline(is_line, value))
            {
                iniMap[key] = trimString(value);
            }
        }
    }

    file.close();
}

string DeviceConfig::trimString(string &str)
{
    size_t start = 0;
    const char *buffer = str.c_str();

    // 去掉开始部分的空格
    for (; start < str.size(); start++)
    {
        char cha = buffer[start];
        if (cha != ' ')
        {
            break;
        }
    }

    // 去掉注释
    size_t pos = str.find_first_of(";", 0);
    string temp(str);
    if (pos > 0)
    {
        temp = str.substr(start, pos - start);
    }

    // 尾部去掉空格
    buffer = temp.c_str();
    size_t end = temp.size() - 1;

    for (; end >= 0; end--)
    {
        char cha = buffer[end];
        if (cha != ' ')
        {
            break;
        }
    }

    return temp.substr(0, end + 1);
}

std::string DeviceConfig::getValue(std::string key)
{
    for (const auto &pair : iniMap)
    {
        if (pair.first.compare(key) == 0)
        {
            return pair.second;
        }
    }
    return "";
}

void DeviceConfig::setValue(const std::string &key, const std::string &value)
{
    if (iniMap.find(key) == iniMap.end())
    {
        return;
    }
    iniMap[key] = value;
}

std::string DeviceConfig::getComment(const std::string &line)
{
    size_t pos = line.find(';');
    if (pos != std::string::npos)
    {
        return line.substr(pos);
    }
    else
    {
        return "";
    }
}

void DeviceConfig::saveConfig()
{
    std::ifstream infile(configFile);
    std::ofstream outfile("temp.ini");
    if (infile.is_open() && outfile.is_open())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            std::string key = line.substr(0, line.find('='));
            if (iniMap.find(key) != iniMap.end())
            {
                outfile << key << "=" << iniMap[key] << "   " << getComment(line) << std::endl;
            }
            else
            {
                outfile << line << std::endl;
            }
        }

        infile.close();
        outfile.close();

        // Replace the original file with the temporary file
        std::remove(configFile.c_str());
        std::rename("temp.ini", configFile.c_str());
    }
}

map<string, string> DeviceConfig::getConfigMap()
{
    return iniMap;
}
