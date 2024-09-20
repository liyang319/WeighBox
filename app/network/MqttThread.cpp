#include "MqttThread.h"
#include "Base.h"
#include <unistd.h>

// MQTT服务器地址和端口号
#define MQTT_HOST "192.168.80.132"
#define MQTT_PORT 1883

// MQTT客户端ID
#define MQTT_CLIENT_ID "mqtt_cpp_client"

// MQTT主题
#define MQTT_TOPIC "test_topic"

// 消息内容
#define MQTT_MESSAGE "Hello from MQTT C++ Client"

bool MqttThread::isRunning = false;
bool MqttThread::isConnected = false;

MqttThread::MqttThread()
{
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        std::cerr << "创建mosquitto客户端失败" << std::endl;
        return;
    }

    mosquitto_message_callback_set(mosq, message_callback);
    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_disconnect_callback_set(mosq, disconnect_callback);
}

MqttThread::~MqttThread()
{
    stop();
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void MqttThread::start()
{
    if (!isRunning)
    {
        isRunning = true;
        thread = std::thread([this]
                             {
            while (isRunning)
            {
                if (!isConnected && mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60))
                {
                    std::cerr << "连接到MQTT服务器失败，尝试重连" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待5秒后重连
                }
                else
                {
                    if (!isConnected && mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0))
                    {
                        std::cerr << "订阅" << MQTT_TOPIC << "失败" << std::endl;
                        return;
                    }

                    if (!isConnected)
                    {
                        isConnected = true;
                        std::cout << "连接成功" << std::endl;
                    }

                    mosquitto_loop_start(mosq);
                }
            } });
    }
}

void MqttThread::stop()
{
    if (isRunning)
    {
        isRunning = false;
        mosquitto_disconnect(mosq);
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void MqttThread::join()
{
    if (thread.joinable())
    {
        thread.join();
    }
}

void MqttThread::message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if (message->payloadlen)
    {
        std::cout << "收到消息: " << (char *)message->payload << std::endl;
    }
    else
    {
        std::cout << "收到空消息" << std::endl;
    }
}

void MqttThread::connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    if (!result)
    {
        isConnected = true;
        COUT << "连接成功" << std::endl;
    }
    else
    {
        COUT << "连接失败" << std::endl;
    }
}

void MqttThread::disconnect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    std::cerr << "连接断开，尝试重新连接" << std::endl;
    isConnected = false;
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待5秒后重连

    while (isRunning && mosquitto_reconnect(mosq))
    {
        std::cerr << "重连失败，等待5秒后重试" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待5秒后重连
    }
}
