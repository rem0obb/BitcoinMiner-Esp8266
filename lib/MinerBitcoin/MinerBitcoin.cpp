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

#include <MinerBitcoin.hpp>

byte hash[SHA256_SIZE];

void MinerBitcoin::sha256(std::string str)
{ 
    SHA256 sha256;

    sha256.doUpdate(str.c_str(), sizeof(str));
    sha256.doFinal(hash);
}

std::string MinerBitcoin::getsha256()
{
    std::string str;
    for(byte i=0;i<SHA256_SIZE;i++)
        str = Serial.print(hash[i], HEX);
    return str;
}

void MinerBitcoin::MinerBit(int nBlock, const char* nTrans, const char* pHash, int  tStamp, int aZeros)
{
    Serial.begin(Port);
    
    this->TimeStamp=tStamp;
    this->NumberBlock=nBlock;
    this->PreviousHash=pHash;
    this->Transactions=nTrans;
    this->AmountZeros=aZeros;
    int nonce=0;

    delay(Time);
    
    while(true)
    {
        std::string str = (
        std::to_string(nonce)+ 
        std::to_string(this->NumberBlock)+ 
        std::to_string(this->TimeStamp)+
        this->Transactions+ 
        this->PreviousHash
        );

        MinerBitcoin::sha256(str);Serial.print("\r");
        
        //Debugger mining...
        Serial.printf("[Nonce] %i  ", nonce);
        Serial.print("[Hash]");getsha256();

        if(getsha256()[0] == '0' && 
           getsha256()[1] == '0' &&
           getsha256()[2] == '0' &&
           getsha256()[3] == '0' &&
           getsha256()[AmountZeros] == '0'
           ){
                Serial.println("[Block Mined]");
                Serial.printf("[Nonce] %i  ", nonce);
                Serial.print("[Hash]");getsha256();
        
                break;
        }else
            nonce+=1;
    }
}
