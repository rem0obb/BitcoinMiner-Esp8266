#include <MinerBitcoin.hpp>

// ========================= Miner  ========================= //

byte hash[SHA256_SIZE]; // Generate Hash variable

void MinerBitcoin::sha256(std::string str)
{   
    SHA256 Hasher;
    SHA256 HashAgain;
    
    int8_t start_t=0, end_t=0, total_t=0;

    start_t = micros();

    HashAgain.doUpdate((byte*)&str, str.size());
    HashAgain.doFinal(hash);

    end_t = micros();
    total_t = (start_t - end_t);
    
    Serial.printf("\n\nTime:");Serial.print(total_t);
}

void MinerBitcoin::Getsha256()
{
    std::string strHash; 
    for(int8_t i=0;i<SHA256_SIZE;i++)
        Serial.print(hash[i], HEX);
}

void MinerBitcoin::MinerBit(int nBlock, const char* nTrans, const char* pHash, const char* aZeros)
{
    Serial.begin(Port);
    
    this->NumberBlock=nBlock;
    this->PreviousHash=pHash;
    this->Transactions=nTrans;
    this->AmountZeros=aZeros;
    int nonce=0;

    while(true)
    {
        nonce+=1;

        std::string str = (
        std::to_string(nonce) + 
        std::to_string(NumberBlock) + 
        nTrans + 
        pHash
        );
        MinerBitcoin::sha256(str);
        
        for(size_t i=0;i<strlen(AmountZeros);i++)
        {AmountZeros = "0";}
        
        if(Serial.findUntil(hash, AmountZeros))
        {
            Serial.print("\nHash: ");MinerBitcoin::Getsha256();
            Serial.printf("\nNonce: ");Serial.print(nonce);
            break;
        }
    }
}