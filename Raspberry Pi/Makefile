httpd: httpd.c
	gcc -std=gnu99 httpd.c -I ../../libmicrohttpd/src/include -I ../../libmicrohttpd/src/microhttpd -I ../../libmicrohttpd/symbian -l microhttpd -o httpd
dsm: dsm.c
	gcc -std=gnu99 dsm.c -l wiringPi -l bcm2835 -o dsm
spi-slave: spi-slave.c
	gcc -std=gnu99 spi-slave.c -l wiringPi -o spi-slave

