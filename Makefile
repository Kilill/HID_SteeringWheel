all: 
	pio run -e linux

up:
	pio run -e linux -t upload

mon:
	pio run -e linux -t monitor

upm:
	pio run -e linux -t upload -t monitor
