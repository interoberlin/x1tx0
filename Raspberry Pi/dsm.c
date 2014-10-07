
#include <wiringPi.h>
#include <bcm2835.h>
#include <stdio.h>

#define MOSI 10
#define MISO 9
#define SCLK 11
#define SS 8

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

    uint16_t setup = 0x0200;
    uint16_t steering = 0x0100;
    uint16_t throttle = 0x1f00;
    uint16_t id = 0x182e;

    while (1)
    {
        // Send a byte to the slave and simultaneously read a byte back from the slave
        // If you tie MISO to MOSI, you should read back what was sent
        sendWord(setup);
        sendWord(steering);
        sendWord(throttle);
        sendWord(id);
        delay(5);
    }

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}
