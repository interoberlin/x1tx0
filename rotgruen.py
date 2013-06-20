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
		sleep(0.02)
		GPIO.output(pins[pin], False)

def test1():
	for i in range(15):
		walk(rot)
		walk(rot[::-1])
		walk(gruen)
		walk(gruen[::-1])

def switch(pins, state):
	for pin in range(len(pins)):
		GPIO.output(pins[pin], state)

def setvalue(v):
	switch(rot+gruen, False)
	if v > 0:
		switch(gruen[:v], True)
	elif v < 0:
		switch(rot[:v*-1], True)

def test2():
	d=0.02
	for i in range(11):
		setvalue(i-5)
		print i-5
		sleep(d)
	for i in range(11):
		setvalue(5-i)
		print 5-i
		sleep(d)

for i in range(15):
	test2()

switch(rot+gruen, False)