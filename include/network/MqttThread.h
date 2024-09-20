#ifndef MQTT_THREAD_H
#define MQTT_THREAD_H

#include <iostream>
#include <thread>
#include <mosquitto.h>

class MqttThread
{
public:
    MqttThread();
    ~MqttThread();

    void start();
    void stop();
    void join();

private:
    struct mosquitto *mosq;
    std::thread thread;
    static bool isRunning;
    static bool isConnected;

    static void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void connect_callback(struct mosquitto *mosq, void *userdata, int result);
    static void disconnect_callback(struct mosquitto *mosq, void *userdata, int result);
};

#endif // MQTT_THREAD_H
