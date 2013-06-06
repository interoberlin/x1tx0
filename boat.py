#!/usr/bin/python
import bobo

@bobo.query('/')
def index():
	return open('index.html').read()

@bobo.post('/setxy')
def lp(bobo_request, text):
	open('server.log','a').write('test')
	return bobo.redirect('/')
