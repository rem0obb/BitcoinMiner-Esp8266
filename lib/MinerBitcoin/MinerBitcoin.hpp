#ifndef  MINER_H
#define MINER_H

/* ========================== References used ========================== 

    https://github.com/MatthewGaber/ESP8266BitcoinMiner
    https://rweather.github.io/arduinolibs/classSHA256.html
    https://pt.wikipedia.org/wiki/Extremidade_(ordenação)

  ========================== libraries  ========================== */

#include <sha256.hpp>
#include <stdint.h>
#include <Arduino.h>

/* ========================== Macros ========================== */

#define MaxHashByts 80
#define Time 1000
#define TimeRunCode 100
#define Port 19200
#define JumpLine(){ Serial.println(); };
#define pinLight(){ pinMode(LED_BUILTIN, OUTPUT); delay(Time);digitalWrite(LED_BUILTIN, 0x1);}
#define pinLow(){ pinMode(LED_BUILTIN, OUTPUT); delay(Time);digitalWrite(LED_BUILTIN, 0x0);}

/* ========================== classes and functions ========================== */

class MinerBitcoin
{
    protected:
        SHA256 Hasher;
        SHA256 HashAgain;

        char header_hex[161] = "0100000081cd02ab7e569e8bcd9317e2fe99f2de44d49ab2b8851ba4a308000000000000e320b6c2fffc8d750423db8b1eb942ae710e951ed797f7affc8892b0f1fc122bc7f5d74df2b9441a42a14695";
        uint8_t HashBytes[MaxHashByts];

    public:
        void MinerBit(void);
};

uint8_t* HexDecode(const char* value, size_t len, uint8_t* output);

#endif // !MINER_H