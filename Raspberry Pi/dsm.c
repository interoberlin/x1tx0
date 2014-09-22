#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>

/*
 * Rasperry Pi pins in use
 *
 * CLK: output pin to output sync pulses; when low, data is transferred to DSM module
 * RID: output pin to send remote control ID
 * SIG: output pin to send control signals
 * IRQ: using PWM pin, connected to IRQ_RID and IRQ_SIG pins, to make use of interrupts instead of delays
 * IRQ_RID: input pin connected to CLK, triggers RID interrupt handler
 * IRQ_SIG: input pin connected to CLK, triggers SIG interrupt handler
 */
#define CLK 25
#define RID 23
#define SIG 24
#define IRQ 18
#define IRQ_RID 27
#define IRQ_SIG 22

unsigned char RemoteControlID[] = {1,1,0,0,2,2,0,0};
bool RID_bits[64];

void initGPIO()
{
    wiringPiSetupGpio();

    pinMode(CLK, OUTPUT);
    pinMode(RID, OUTPUT);
    pinMode(SIG, OUTPUT);
    
    digitalWrite(CLK, HIGH);
    digitalWrite(RID, LOW);
    digitalWrite(SIG, LOW);
    
    pinMode(IRQ, PWM_OUTPUT);
    pinMode(IRQ_RID, INPUT);
    pinMode(IRQ_SIG, INPUT);
}

void calculateRIDbits()
{
    // 8 bytes
    for (int i=0; i<8; i++) // i in [0;7]
    {
        int k = i*8;
        // 8 bits per byte
        // little endian
        for (int j=0; j<8; j++)
        {
            int bitmask = 128 >> j;
            RID_bits[k+j] = ((RemoteControlID[i] & bitmask) > 0);
        }
    }
}

void setInterruptClock()
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
    pwmWrite(IRQ, 4);
}

void transmitRID()
{
    digitalWrite(CLK, LOW);
    
    // zwei direkt aufeinanderfolgende HIGH-LOW in der for-schleife dauern 250ns
    // digitalWrite(HIGH); takes 80ns
    // digitalWrite(LOW); takes 40ns

    void high()
    {
        digitalWrite(RID, HIGH);
        delayMicroseconds(2); 
        digitalWrite(RID, LOW);
        delayMicroseconds(1); 
    }

    void low()
    {
        digitalWrite(RID, HIGH);
        delayMicroseconds(1); 
        digitalWrite(RID, LOW);
        delayMicroseconds(2); 
    }

    delayMicroseconds(4);
    for (int i=0; i<64; i++)
    {
        if (RID_bits[i])
            high();
        else
            low();
    }
  
    digitalWrite(CLK, HIGH);
}

void transmitSIG()
{
    // 4 blocks
    for (int i=0; i<4; i++) // i in [0;3]
    {
        digitalWrite(SIG, HIGH);
        delayMicroseconds(2); 
        digitalWrite(SIG, LOW);
        delayMicroseconds(1); 
    }
}

void attachInterruptHandlers()
{
    wiringPiISR(IRQ_RID, INT_EDGE_RISING, transmitRID);
    wiringPiISR(IRQ_SIG, INT_EDGE_RISING, transmitSIG);
}
 
int main()
{
    initGPIO();
    calculateRIDbits();
    setInterruptClock();
    attachInterruptHandlers();
    while (1)
    {
        delay(3000);
    }
}
