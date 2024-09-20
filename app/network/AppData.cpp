// appdata.cpp
#include "AppData.h"

AppData &AppData::getInstance()
{
    static AppData instance;
    return instance;
}

void AppData::addDataToDataRecvQueue(std::string &data)
{
    std::lock_guard<std::mutex> lock(data_recv_queue_mutex);
    data_recv_queue.push(data);
}

std::string AppData::getDataFromDataRecvQueue()
{
    std::lock_guard<std::mutex> lock(data_recv_queue_mutex);
    if (!data_recv_queue.empty())
    {
        std::string data = data_recv_queue.front();
        data_recv_queue.pop();
        return data;
    }
    return "";
}

void AppData::addDataToDataSendQueue(std::string &data)
{
    std::lock_guard<std::mutex> lock(data_send_queue_mutex);
    data_send_queue.push(data);
}

std::string AppData::getDataFromDataSendQueue()
{
    std::lock_guard<std::mutex> lock(data_send_queue_mutex);
    if (!data_send_queue.empty())
    {
        std::string data = data_send_queue.front();
        data_send_queue.pop();
        return data;
    }
    return "";
}

AppData::AppData()
{
    // constructor
}
