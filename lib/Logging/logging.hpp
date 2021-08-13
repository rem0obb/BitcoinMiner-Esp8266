/**
 * @file logging.hpp
 * @author VitorMob
 * @brief Store block mined using memory flash emulate in esp8266
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <Arduino.h>
#include <EEPROM.h>


#define LongTime 5000
#define Door 9999
#define Port 19200
#define ERROR   "[!][ERROR] "
#define DONE    "[*][Done] "
#define WARNING "[#][Warning] "
#define INFO    "[?][Info] "

class logging
{
    protected:
        void __write__(const char* str);

    public:
        int  __logging__(std::string __macro__, std::string __info__, ...);
        void __clean_logging__();
        void __read_logging__();
};
