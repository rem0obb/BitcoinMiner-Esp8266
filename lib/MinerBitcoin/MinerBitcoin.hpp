#ifndef  MINER_H
#define MINER_H

/* ========================== libraries  ========================== */

#include <sha256.hpp>
#include <stdint.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string>

/* ========================== Macros ========================== */

#define DefaultZeros "000"
#define Time 2000
#define TimeRunCode 300
#define Port 19200
#define pinLight(){ pinMode(LED_BUILTIN, OUTPUT);delay(Time);digitalWrite(LED_BUILTIN, 0x1);}
#define pinLow(){ pinMode(LED_BUILTIN, OUTPUT);delay(Time);digitalWrite(LED_BUILTIN, 0x0);}

/* ========================== classes and functions ========================== */

class MinerBitcoin
{
    protected:        
        int NumberBlock;
        const char* Transactions;
        const char* AmountZeros;  
        const char* PreviousHash;

    public:
        void MinerBit(int nBlock, const char* nTrans, const char* pHash, const char* aZeros=DefaultZeros);
        void sha256(std::string str);
        void Getsha256();
};

#endif // !MINER_H