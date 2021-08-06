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

void MinerBitcoin::getsha256()
{
    std::string strHash; 
    for(int8_t i=0;i<SHA256_SIZE;i++)
        Serial.print(hash[i], HEX);
}

void MinerBitcoin::MinerBit(int nBlock, const char* nTrans, const char* pHash, int aZeros)
{
    Serial.begin(Port);
    
    this->NumberBlock=nBlock;
    this->PreviousHash=pHash;
    this->Transactions=nTrans;
    this->AmountZeros=aZeros;
    int nonce=0;

    while(true)
    {
        std::string str = (
        std::to_string(nonce) + 
        std::to_string(NumberBlock) + 
        nTrans + 
        pHash
        );

        MinerBitcoin::sha256(str);

        if(hash[0] == 0 
        && hash[1] == 0
        && hash[2] == 0 
        && hash[AmountZeros] == 0)
        {
            Serial.print("\nHash: ");MinerBitcoin::getsha256();
            Serial.printf("\nNonce: ");Serial.print(nonce);
            Serial.println("\nStatus: Mined");

            break;
        }else
            nonce+=1;
    }
}
