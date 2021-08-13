/**
 * @file logging.cpp
 * @author VitorMob
 * @brief registry to monitor your mining process
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <logging.hpp>

                            // ERROR, DONE, WARNING, INFO
int logging::__logging__(std::string __macro__, std::string __info__, ...)
{
    Serial.begin(Port);
    std::string str =  __macro__ + __info__;
    EEPROM.begin(strlen(str.c_str()));

    delay(LongTime);

    if(__macro__ != ERROR ||
    __macro__ != WARNING ||
    __macro__ != DONE ||
    __macro__ != INFO) return EXIT_FAILURE;

    Serial.println(str.c_str());
    logging::__write__(str.c_str());

    return EXIT_SUCCESS;
}

void logging::__write__(const char* str)
{
    Serial.printf("%s %s\n", INFO, "Writing memory...");        
    for(size_t it=0;it < sizeof(str);it++)
        EEPROM.write(0x0F+it, strlen(str));
    EEPROM.commit();
    Serial.printf("%s %s\n", DONE, "Write with success !");        

}


void logging::__read_logging__()
{
    Serial.printf("%s %s\n", DONE, "Reading Memory...");        
    for(size_t it=0;it<EEPROM.length();it++)
        Serial.print(EEPROM.read(0x0F+it), HEX);
    Serial.print("\n");
}

void logging::__clean_logging__()
{
    for(size_t it=0;it<EEPROM.length();it++)
        EEPROM.write(0x0F+it, 0);

    Serial.printf("%s %s\n", DONE, "Memory clean with success !");        
}

