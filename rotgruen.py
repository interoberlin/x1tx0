#!/usr/bin/python

import RPi.GPIO as GPIO
from RPi.GPIO import OUT
from time import sleep

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

rot = [18, 23, 24, 25, 22]
gruen = [31, 30, 27, 28, 4]

pins = rot+gruen

for pin in range(len(pins)):
	GPIO.setup(pins[pin], OUT)

def walk(pins):
	for pin in range(len(pins)):
		GPIO.output(pins[pin], True)
		sleep(0.1)
		GPIO.output(pins[pin], False)

for i in range(5):
	walk(rot)
	walk(rot[::-1])
	walk(gruen)
	walk(gruen[::-1])
