# PCB Design Changelog

### Changes from V1.0 to V1.1

- Optical Encoder power out changed from 3v3 to 5v rpi bus

 - Increase size of stepper motor driver PCB holes from 0.7mm to 1mm
 - Reduced distance between stepper motor driver pins by 1.27mm 

- Increased size of holes for DC/DC Buck converter from 0.7mm to 1mm

- Removed component values from PCB Silkscreen
- Increased text size for component references.

- Changed orientation of Optical Encoder connector as Vcc and GND were reversed

 - Increase CLR for 12v bus LED - DONE NOW 10k

- Changed STEPP_EN enable pin from both MCUs to SLP pin on stepper controller

- Changed SHIFT Reg Q7 output to STEPP_EN for Supervisor MCU. No Control for Student MCU 
- doesnt seem to change anything but at least its there incase

- Tied pull down resistors on stepper MODE inputs to VCC to pull up - standard mode is now finest resolution
- Tied Mode switches to GND to pull down when actuated.


#TODO:

- Add STEPP_SLP To Q7 shift register - How can this be coordinated between 2 MCUs?
 - NOTE ON ABOVE.
  CHANGING ENABLE PIN TO OPEN 
  SLEEP PIN NOW CONTROLLED INSTEAD OF ENABLE
- Stepper motor output make match evisting connectors?



