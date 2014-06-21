sensor-data-collection
======================

Designed and programmed onto an Arduino Uno by Kim Laberinto.
GitHub: https://github.com/kimlaberinto/sensor-data-collection

Latest Update on: June 21, 2014.

About
-----

The goal is to to make it easier to collect data from sensor configurations. Simply hook up a button, attach your sensors and upload this .ino into your arduino. The arduino will start flashing, and will initilize after 5 seconds (taking reference values), then it will be ready to collect tests and output readings. Simply press the button and it will output the all averages of the sensor values over some period of time.

Personnally what I had in mind was to use it to design more effective capacitance sensor configurations, but I now realize that it could be used for any analog sensor configurations, and see the outputs during specific situations.

To Do
-----

- [x] Modifable Button Pin (easy)
- [x] Modifable led Pin (easy)
 - [ ] Possibly make if unnecessary (check if ledPIN is null or something)
- [x] Add running count, will make it easier to parse through data

- [ ] Settings List
  - [x] Number of sensorValues (for each sensor) per button press
  - [ ] Spit out all sensorValues or average them out
  - [ ] Y/N Normalized (if Y reference taken and minused from values)
  - [x] Delay between readings of the sensorValues

- [x] Customizable Sensor Pin List
- [x] implement runningSum Array

- [?] Maybe add print out min/max per button press

- [ ] Write a better README
  - [ ] Improve About section
  - [ ] Add How To Use section
  - [ ] Add examples of readings