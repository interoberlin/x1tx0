
/*
http://wiringpi.com/examples/blink/
https://projects.drogon.net/raspberry-pi/wiringpi/functions/
*/
#include <wiringPi.h>

void resetPins()
{
    digitalWrite(SIG, LOW);
    digitalWrite(RID, LOW);
    digitalWrite(CLK, HIGH);
}

void digitalEncode(long signal, int bits)
{
    long mask = 1 << (bits-1);
    for (int i=0; i<bits; i++)
    {
        digitalWrite(SIG, (signal & mask) > 0 ? HIGH : LOW);
        delayMicroseconds(4);
        mask = mask >> 1;
    }
}

void repetetiveSignal()
{
    digitalWrite(CLK, LOW);

    /*
    block 1: unknown function
    total: 46us
    */
    digitalEncode(1 << 12, 18);
/*    delayMicroseconds(20);
    digitalWrite(SIG, HIGH);
    delayMicroseconds(4);
    digitalWrite(SIG, LOW);
    delayMicroseconds(48); */
    
    /*
    block2: steering
    total: 56us
    */
    digitalEncode(42, 14);

    /*
    block 3: throttle
    total: 56us
    */
    digitalEncode(42, 14);

    /*
    block 4: unknown function
    duration: 49us
    H 4 4
    L 4 8
    H 4 12
    L 16 28
    H 4 32
    L 4 36
    H 12 48 L
    1010 0001 0111
    */
    digitalEncode(0b101000010111, 12);

    resetPins();
}

int main(void)
{
    wiringPiSetupGpio();

    pinMode(SIG, OUTPUT);
    pinMode(RID, OUTPUT);
    pinMode(CLK, OUTPUT);

    resetPins();

    /*
    TODO: timer
    every 5.5ms
    duration 233us
    */
    for (;;)
    {
        delay(5);
        repetetiveSignal();
    }

    return 0;
}
