#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>

// using namespace rapidjson;
// maeusing namespace std;

// MQTT服务器地址和端口号
#define MQTT_HOST "192.168.80.132"
#define MQTT_PORT 1883

// MQTT客户端ID
#define MQTT_CLIENT_ID "mqtt_cpp_client"

// MQTT主题
#define MQTT_TOPIC "test_topic"

// 消息内容
#define MQTT_MESSAGE "Hello from MQTT C++ Client"

void on_connect(struct mosquitto *mosq, void *userdata, int result)
{
    if (result == 0)
    {
        std::cout << "Connected to MQTT server" << std::endl;
        mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(MQTT_MESSAGE), MQTT_MESSAGE, 0, false);
    }
    else
    {
        std::cerr << "Failed to connect to MQTT server" << std::endl;
    }
}

int main()
{
    // COUT << "=========WeighBox=============" << VERSION << endl;
    struct mosquitto *mosq;

    mosquitto_lib_init();
    mosq = mosquitto_new(MQTT_CLIENT_ID, true, NULL);

    mosquitto_connect_callback_set(mosq, on_connect);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Unable to connect to MQTT server" << std::endl;
        return 1;
    }

    mosquitto_loop_start(mosq);

    // 等待连接和消息发布
    sleep(5);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
