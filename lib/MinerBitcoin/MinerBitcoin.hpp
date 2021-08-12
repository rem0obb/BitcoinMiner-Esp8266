/**
 * @file MinerBitcoin.hpp
 * @author VitorMob
 * @brief lib for block mining
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef  MINER_H
#define MINER_H


#include <sha256.hpp>
#include <Arduino.h>
#include <logging.hpp>


#define DefaultZeros 4
#define Time 2000
#define Port 19200
#define pinLight(){ pinMode(LED_BUILTIN, OUTPUT);delay(Time);digitalWrite(LED_BUILTIN, 0x1);}
#define pinLow(){ pinMode(LED_BUILTIN, OUTPUT);delay(Time);digitalWrite(LED_BUILTIN, 0x0);}


class MinerBitcoin
{
    protected:
        logging log;  
        int NumberBlock;
        const char* Transactions;
        int AmountZeros;  
        const char* PreviousHash;
        
    public:
        void MinerBit(int nBlock, const char* nTrans, const char* pHash, int aZeros=DefaultZeros);
        void sha256(std::string str);
        std::string getsha256();
};

#endif // !MINER_H
