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

byte hash[SHA256_SIZE]; // Hash variable

void MinerBitcoin::sha256(std::string str)
{   
    SHA256 Hasher;
    SHA256 HashAgain;
    
    HashAgain.doUpdate((byte*)&str, str.size());
    HashAgain.doFinal(hash);
}

std::string MinerBitcoin::getsha256()
{
    std::string str;
    for(size_t i=0;i<SHA256_SIZE;i++)
        str = Serial.print(hash[i], HEX);
    return str;
}

void MinerBitcoin::MinerBit(int nBlock, const char* nTrans, const char* pHash, int aZeros)
{
    Serial.begin(Port);
    
    this->NumberBlock=nBlock;
    this->PreviousHash=pHash;
    this->Transactions=nTrans;
    this->AmountZeros=aZeros;
    int nonce=0;

    delay(Time);
    
    log.__logging__(WARNING, "Mining...");
    while(true)
    {
        std::string str = (
        std::to_string(nonce)+ 
        std::to_string(this->NumberBlock)+ 
        this->Transactions+ 
        this->PreviousHash
        );

        MinerBitcoin::sha256(str);Serial.print("\r");
        
        //Debugger mining...
        Serial.printf("[Nonce] %i  ", nonce);
        Serial.printf("[Hash]");getsha256();

        if(hash[0] == 0 
        && hash[1] == 0
        && hash[2] == 0 
        && hash[3] == 0
        && hash[AmountZeros] == 0)
        {
            log.__logging__(DONE, "[Block Mined !]\n");
            log.__logging__(DONE,"[Block] %i\n", this->NumberBlock);
            log.__logging__(DONE,"[Hash] %s", getsha256());
            log.__logging__(DONE,"[Nonce] %i\n", nonce);

            Serial.print("[Status] Block Mined !");
            
            break;
        }else
            nonce+=1;
    }
}
