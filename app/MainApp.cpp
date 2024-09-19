#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>
#include "Utility.h"

#include "document.h"
#include "stringbuffer.h"
#include "writer.h"
#include <thread>
#include <chrono>

#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

#include "Base.h"
#include "Version.h"

using namespace rapidjson;
// maeusing namespace std;
#define DEFAULT_VERSION_PATH "/opt/version"
#define APP_NAME "WeighBox"
#define CONFIG_NAME "WeighBox.ini"

int main()
{
    COUT << "=========WeighBox=============" << VERSION << endl;
    return 0;
}
