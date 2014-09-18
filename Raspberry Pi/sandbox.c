#include <stdio.h>
#include <wiringPi.h>

int main() {
    wiringPiSetupGpio();

    pinMode(23, OUTPUT);

    while(1)
    {
        digitalWrite(23, HIGH);
        delay(1);
        digitalWrite(23, LOW);
        delay(2);
    }
}