#!/usr/bin/python
import bobo
import RPi.GPIO as GPIO
from RPi.GPIO import OUT
from time import sleep

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

throttle = 23
steering = 24
GPIO.setup(throttle, OUT)
GPIO.setup(steering, OUT)

TH = GPIO.PWM(throttle, 1000)
TH.start(0)
ST = GPIO.PWM(steering, 1000)
ST.start(0)

on = False

@bobo.post('/')
def lp(bobo_request, x=0, y=0):
	global on
	if on:
		return ""
	on = True
	try:
		print str(x)+' - '+str(y)
		x = 50+int(x)*5
		y = 50+int(y)*5
		TH.ChangeDutyCycle(y)
		ST.ChangeDutyCycle(x)
	except:
		print "exception"
	sleep(0.3)
	on = False
	return ""

