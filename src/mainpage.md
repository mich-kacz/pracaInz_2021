Introduction
========================

This is the documentation of the software implemented on mobile system for vibration measurments with MEMS accelerometers.
The documentation just includes description of public methods and types. Private methods and types were not included. System was designed to acquire data and save it to memory storage like sd card or USB pendrive. The collected data by the device should make it posible to observe vibrations with frequencies up to at least 8 kHz.

The discussed system consists of: 
-  BeagleBone Black, a single board computer

    The device works on Debian 10.3 operating system. The system image was downloaded from [this site](https://beagleboard.org/latest-images).

- Pair of accelerometers ADXL1001z

    Used devices are single axis, low noise, high frequency MEMS accelerometers. Sensors are characterized by linear frequency response range from dc to 11 kHz and range of +-100g. Full documentation of accelerometers is included at [this page](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL1001-1002.pdf)  

- Self made electronic circuit with:
  + Linear voltage regulator L7805CV
  + IRF 510 mosfet and NE5532 operational amplifier as a switching circuit between two possible power supplies
  + BC547B npn transistor as a switch for bistable button light
  + Other electronic passive components


Gallery
========================
<center>

<img src="zdj1.jpg" width="300">

<caption>Self made electronic circuit</caption>



<img src="zdj2.jpg" width="300">

<caption>Beaglebone Black</caption>



<img src="zdj3.jpg" width="500">

<caption>System with case</caption>
</center>