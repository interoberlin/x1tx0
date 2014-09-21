#include <stdio.h>
#include <wiringPi.h>

/*
 * Rasperry Pi pins in use
 *
 * CLK: output pin to output sync pulses, in which data is transferred to DSM module
 * RID: output pin to send remote control ID
 * SIG: output pin to send control signals
 * RID_IRQ: input pin connected to CLK, triggers RID interrupt handler
 * SIG IRQ: input pin connected to CLK, triggers SIG interrupt handler
 */
#define CLK 18
#define RID 23
#define SIG 24
#define RID_IRQ 27
#define SIG_IRQ 22

unsigned char RemoteControlID[] = {1,1,0,0,2,2,0,0};

void initGPIO()
{
    wiringPiSetupGpio();
    pinMode(CLK, PWM_OUTPUT);
    pinMode(RID, OUTPUT);
    pinMode(SIG, OUTPUT);
    pinMode(RID_IRQ, INPUT);
    pinMode(SIG_IRQ, INPUT);
}

void disableClock()
{
    pwmWrite(CLK, 0);
}

void setClock()
{
    /*
     * Clock/interrupt setup
     * http://raspberrypi.stackexchange.com/questions/4906/control-hardware-pwm-frequency
     */
    pwmSetMode(PWM_MODE_MS);
    /*
     * timer divisor; value between [1..4095] ?
     * desired result is approx. 180Hz or 5.5ms between clock pulses
     */
    pwmSetClock(1024);
    int range = 100;
    pwmSetRange(range);
    pwmWrite(CLK, 4);
}

void RID_interrupt()
{
    // transmit 8 bytes
    for (int i=0; i<8; i++) // i in [0;7]
    {
        delayMicroseconds(4);
        // cache to separate variable for faster access
        int b = RemoteControlID[i]; 
        // all 8 bits: bitmask from highest bit to lowest
        for (int j=128; j>=1; j>>1)
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

void SIG_interrupt()
{
}

void attachInterruptHandlers()
{
}

int main()
{
    initGPIO();
    disableClock();
    attachInterruptHandlers();
    setClock();
    while (1)
    {
        delay(1000);
    }
}
