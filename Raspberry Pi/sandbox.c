#include <stdio.h>
#include <wiringPi.h>

#define CLK 18
#define RID 23
#define SIG 24
#define IRQ 25

unsigned char senderID[] = {1,1,0,0,2,2,0,0};

int main() {
    wiringPiSetupGpio();

    pinMode(CLK, PWM_OUTPUT);
    pinMode(RID, OUTPUT);

    // http://raspberrypi.stackexchange.com/questions/4906/control-hardware-pwm-frequency
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(4095);
    int range = 100;
    pwmSetRange(range);

    pwmWrite(CLK, 5);

    while (1)
    {
        // transmit 8 bytes
        for (int i=0; i<2; i++) // 8
        {
            delayMicroseconds(4);
            // cache for faster variable access
            int b = senderID[i]; 
            // all 8 bits: bitmask from highest bit to lowest
            for (int j=0x80; j>=1; j>>1)
            {
                // is this bit set ?
                if (b & j > 0)
                {
                    digitalWrite(RID, HIGH);
                    delayMicroseconds(2); 
                    digitalWrite(RID, LOW);
                    delayMicroseconds(1); 
                } else {
                    digitalWrite(RID, HIGH);
                    delayMicroseconds(1); 
                    digitalWrite(RID, LOW);
                    delayMicroseconds(2); 
                }
            }
        }
    }

    pwmWrite(CLK, 0);
}