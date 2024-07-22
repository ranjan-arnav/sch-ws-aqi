# combined weather station and air quality monitor

this project combines a weather station and an air quality monitor into a single arduino-based system. it measures temperature, humidity, atmospheric pressure, and air quality, displaying the data on an lcd screen and optionally logging it to an sd card.

## components used
- arduino uno
- dht22 sensor (temperature and humidity)
- bmp280 sensor (pressure)
- mq-135 gas sensor (air quality)
- lcd display (16x2 with i2c)
- sd card module (optional, for data logging)

## features
- real-time display of environmental data
- optional data logging to sd card for analysis
- easy-to-build with commonly available components

## usage
1. connect the sensors and modules to the arduino as described in the circuit diagram.
2. upload the provided code to the arduino.
3. observe the data on the lcd screen and check the sd card for logged data (if used).

## applications
- home and office environmental monitoring
- educational projects and demonstrations
- preliminary air quality assessment

