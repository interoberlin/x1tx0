#!/usr/bin/python

import RPi.GPIO as GPIO
from RPi.GPIO import OUT
from time import sleep

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

throttle = 23
steering = 17
GPIO.setup(throttle, OUT)
GPIO.setup(steering, OUT)

p = GPIO.PWM(throttle, 1000)
p.start(0)

sleep(2)
print '33'
p.ChangeDutyCycle(33)
sleep(2)
print '66'
p.ChangeDutyCycle(66)
sleep(2)
print '100'
p.ChangeDutyCycle(100)
sleep(2)

p.ChangeDutyCycle(0)
p.stop()
GPIO.cleanup()
