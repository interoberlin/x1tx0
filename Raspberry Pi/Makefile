dsm: dsm.c
	gcc -std=gnu99 dsm.c -l wiringPi -l bcm2835 -o dsm
sandbox: sandbox.c
	#g++ sandbox.c -o sandbox -lwiringPi
	gcc -std=gnu99 sandbox.c -lwiringPi -o sandbox
spi-slave: spi-slave.c
	gcc -std=gnu99 spi-slave.c -lwiringPi -o spi-slave

