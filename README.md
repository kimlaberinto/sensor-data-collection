sensor-data-collection
======================

About
-----

The goal of this is to try to make it easier to collect data from sensors. Personnally what I had in mind was to use it to design more effective capacitance sensor configurations, but I now realize that it could be used for any analog sensor configurations really. Currently, when you press the button, it serial.prints out all the sensor values (minus the reference) on pins A0 and A1.


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