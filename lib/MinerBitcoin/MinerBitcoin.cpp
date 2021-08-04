#include <MinerBitcoin.hpp>

uint8_t* HexDecode(const char* value, size_t len, uint8_t* output)
{
    unsigned int i, mg, ng, rg;
    for(mg = 0, i = 0; i < len; i+=2,++mg)
    {
        ng = (value[i] > '9' )  ? value[i]   - 'a' + 10 : value[i]   - '0';
        rg = (value[i+1] > '9') ? value[i+1] - 'a' + 10 : value[i+1] - '0';
        output[mg] = (ng << 4 ) | rg;
    }
    return output;
}

void MinerBitcoin::MinerBit(void)
{
    Serial.begin(Port);

    pinLight();

    start_t = micros();

    HexDecode(HeaderHex, strlen(HeaderHex) , HashBytes);
    
    Hasher.doUpdate(HashBytes, sizeof(HashBytes));
    byte hash[SHA256_SIZE];
    Hasher.doFinal(hash);

    HashAgain.doUpdate(hash, sizeof(hash));
    byte hash2[SHA256_SIZE];
    HashAgain.doFinal(hash2);
    
    
    end_t = micros();
    total_t = (end_t - start_t);

    Serial.print("\n\n\nTime:");Serial.println(total_t);
    pinLow();

    unsigned long ended = micros(); 
    unsigned long delta = ended - start;
    
    Serial.printf("\nNonce: %lu\n", delta);
    pinLow();

    /*Bytes are stored in descending order of their 
    "numeric weight" at successive memory addresses 
    (largest end first or big-endian). */
    Serial.print("Big Endian: ");
    for(byte i=32; i > 0; i--){
        if(hash2[i-1]<0x10)
        { 
            Serial.print('0');
        }
        Serial.print(hash2[i-1], HEX);
    }
    
    JumpLine();

    /* Bytes are stored in ascending order of their 
    //"numeric weight" at successive memory addresses 
    (small end first or little-endian).*/
    Serial.print("Little Endian: ");
    for (byte i=0; i < SHA256_SIZE ; i++){
        if(hash2[i]<0x10) 
        {
             Serial.print('0'); 
        }
        Serial.print(hash2[i], HEX);
    }    
}
