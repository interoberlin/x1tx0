#!/usr/bin/python

import RPi.GPIO as GPIO
from RPi.GPIO import OUT
from time import sleep

pin = 31

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, OUT)

for i in range(20):
	GPIO.output(pin, True)
	sleep(0.1)
	GPIO.output(pin, False)
	sleep(0.1)