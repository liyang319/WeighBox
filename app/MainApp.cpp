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
#include "Base.h"
#include "Version.h"

#include "MqttThread.h"

// using namespace rapidjson;
// maeusing namespace std;

int main()
{
    MqttThread mqttThread;
    mqttThread.start();

    while (true)
    {
        sleep(10);
    }

    mqttThread.stop();
    mqttThread.join();

    return 0;
}
