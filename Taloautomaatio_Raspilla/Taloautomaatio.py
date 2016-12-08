import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
lights = False

#Servo init
GPIO.setup(18, GPIO.OUT)
pwm = GPIO.PWM(18, 100)
pwm.start(5)

def servo(angle):
        duty = float(angle) / 13.0 + 3.5
        pwm.ChangeDutyCycle(duty)
#END Servo init

#7segment init
import time
import datetime
from Adafruit_7Segment import SevenSegment
from math import *

segment = SevenSegment(address=0x70)

def display_wtime():
        now = datetime.datetime.now()
        hour = now.hour
        minute = now.minute
        second = now.second

        segment.writeDigit(0, int(hour)/10)
        segment.writeDigit(1, int(hour)%10)
        
        segment.setColon(second % 2)
        
        segment.writeDigit(3, int(minute)/10)
        segment.writeDigit(4, int(minute)%10)

def display_w(d1, d2, d3, d4):
        segment.writeDigit(0, int(d1))
        segment.writeDigit(1, int(d2))
        segment.writeDigit(3, int(d3))
        segment.writeDigit(4, int(d4))

def display_clear():
        segment.writeDigitRaw(0, 0)
        segment.writeDigitRaw(1, 0)
        segment.setColon(False)
        segment.writeDigitRaw(3, 0)
        segment.writeDigitRaw(4, 0)
#END 7segment init

#ADC init
import spidev
import time
import os
 
spi = spidev.SpiDev()
spi.open(0,0)
 
def ReadChannel(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  data = ((adc[1]&3) << 8) + adc[2]
  return data

def ConvertVolts(data,places):
  volts = (data * 3.3) / float(1023)
  volts = round(volts,places)
  return volts
 
def ConvertTemp(data,places):
  temp = ((data * 330)/float(1023))-50
  temp = round(temp,places)
  return temp
 
# Define sensor channels
light_channel = 0
temp_channel  = 1 
#END ADC init

#Keypad init
rows = [4, 23, 24, 25]
cols = [17, 27, 22]
keys = [
	['1', '2', '3'],
	['4', '5', '6'],
	['7', '8', '9'],
	['*', '0', '#']]

for row_pin in rows:
	GPIO.setup(row_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
for col_pin in cols:
	GPIO.setup(col_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
def get_key():
	key = -1
	for col_num, col_pin in enumerate(cols):
		GPIO.setup(col_pin, GPIO.OUT, initial=1)
		for row_num, row_pin in enumerate(rows):
			if GPIO.input(row_pin):
				key = keys[row_num][col_num]
		GPIO.setup(col_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	return str(key)
#END Keypad init

#Tilakone init
TILA_0 = "Nappainlukko paalla"
TILA_1 = "Nappainlukko paalla. Yksi oikein"
TILA_2 = "Nappainlukko auki. Ovi kiinni"
TILA_3 = "Yksi oikein"
TILA_4 = "Kaksi oikein"
TILA_5 = "Kolme oikein"
TILA_6 = "Nelja oikein"
TILA_7 = "Ovi auki"

pin = ['1', '2', '3', '4']
nappainlukko = ['1', '*']

tilat = [TILA_0, TILA_1, TILA_2, TILA_3, TILA_4, TILA_5, TILA_6, TILA_7]
nykytila = tilat[0]

def seuraava_tila(nykytila):
    luku = get_key()
    if luku != '-1':
        if nykytila == TILA_0:
            if luku == nappainlukko[0]:
                nykytila = TILA_1
            else:
                print('Nappainlukko aktiivinen. Paina 1 ja * avataksesi.')
        elif nykytila == TILA_1:
            if luku == nappainlukko[1]:
                nykytila = TILA_2
                print('Syota pin')
            else:
                nykytila = TILA_0
                print('Nappainlukko aktiivinen. Paina 1 ja * avataksesi.')
        elif nykytila == TILA_2:
            if luku == pin[0]:
                nykytila = TILA_3
        elif nykytila == TILA_3:
            if luku == pin[1]:
                nykytila = TILA_4
            else:
                nykytila = TILA_2
        elif nykytila == TILA_4:
            if luku == pin[2]:
                nykytila = TILA_5
            else:
                nykytila = TILA_2
        elif nykytila == TILA_5:
            if luku == pin[3]:
                nykytila = TILA_6
            else:
                nykytila = TILA_2
        elif nykytila == TILA_6:
            if luku == '#':
                nykytila = TILA_7
                print("Ovi auki")
                servo(170)
                #nykytila = TILA_1    
        print(luku)
    time.sleep(0.2)
        
    return nykytila
#END Tilakone init


while True:
        nykytila = seuraava_tila(nykytila)
        #print(nykytila)

        # Read the light sensor data
        light_level = ReadChannel(light_channel)
        #light_volts = ConvertVolts(light_level,2)
 
        # Read the temperature sensor data
        temp_level = ReadChannel(temp_channel)
        #temp_volts = ConvertVolts(temp_level,2)
        temp = ConvertTemp(temp_level,2)

        if nykytila == TILA_0 or nykytila == TILA_1:
                display_wtime()
                servo(35)
        elif nykytila == TILA_6:
                segment.writeDigitRaw(0, 1)
        elif nykytila == TILA_7:
                luku = get_key()
                if luku == '*':
                        display_w(0, floor(temp/100), floor(temp/10), temp%10)
                elif luku == '0':
                        if lights == False:
                                GPIO.setup(4, GPIO.OUT, initial=1)
                                lights = True
                        else:
                                GPIO.setup(row_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
                                lights = False
                elif luku == '#':
                        nykytila = TILA_0
                else:
                        display_clear()
                        segment.writeDigit(0, -1)
        else:
                display_clear()
    
	