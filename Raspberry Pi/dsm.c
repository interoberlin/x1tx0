
#include <wiringPi.h>
#include <bcm2835.h>
#include <stdio.h>

#define MOSI 10 // green
#define MISO 9 
#define SCLK 11 // brown
#define SS 8    // blue

void sendWord(w)
{
uint8_t in0 = bcm2835_spi_transfer(w >> 8);
delayMicroseconds(4);
uint8_t in1 = bcm2835_spi_transfer(w & 0xff);
delayMicroseconds(4);
//printf("Read from SPI: %02X %02X\n", in0, in1);
}

int main(int argc, char **argv)
{
    wiringPiSetupGpio();
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
    pinMode(SCLK, OUTPUT);
    pinMode(SS, OUTPUT);

    if (!bcm2835_init())
        return 1;

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024);  // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    uint16_t setup = 0x0100;
    
    // steering interval:
    // from left = 0x0000 to right = 0x0fff
    // middle = 0x988
    uint16_t steering = 0x0988;
    // throttle interval:
    // from off = 0x1000 to full power = 0x1fff
    // minimal:  0x1310
    // normal:   0x1400
    // fast:     0x1500
    // ultrafast:0x1700
    // insane:   0x1fff
    uint16_t throttle = 0x1700;
    uint16_t id = 0x182e;

    while (1)
    {
        sendWord(setup);
        sendWord(steering);
        sendWord(throttle);
        sendWord(id);
        delay(3);
    }

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}
