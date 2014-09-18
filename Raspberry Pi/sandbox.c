#include <stdio.h>
#include <wiringPi.h>

#define CLK 18

int main() {
    wiringPiSetupGpio();

    pinMode(CLK, PWM_OUTPUT);

    // http://raspberrypi.stackexchange.com/questions/4906/control-hardware-pwm-frequency
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(4095);
    int range = 100;
    pwmSetRange(range);

    pwmWrite(CLK, 0);
    int d = 0;
    while(1)
    {
        pwmWrite(CLK, d++);
        d %= range;
        delay(100);
    }
    pwmWrite(CLK, 0);
}