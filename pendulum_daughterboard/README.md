# Pendulum Driver Daughterboard

The task is to design and fabricate a drop in replacement for the motor driver board on the new remote labs PCB. The original daughterboard is the Infineon motor control shield:
  https://uk.rs-online.com/web/p/shields-for-arduino/

The new PCB will be driving the pendulum experiment, the circuit and experiment is documented in this github repo:
https://github.com/practable/penduino

![Pendulum Driver Origional Circuit](https://user-images.githubusercontent.com/97303986/172808053-d8fad1c2-18dd-4ce7-b26b-86a0a3df9bc0.png)


RL supervisor PCB repo found at:
https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB

### Schematic Showing connections to motherboard
 ![Infineon Motor Driver Connections to motherboard](https://user-images.githubusercontent.com/97303986/172808025-e9ffd484-5b0c-436a-84e9-058f29666111.png)


I have created a folder for the pendulum daughterboard, if you could keep all the KiCAD files and any notes you make in this folder. Part of the reasoning of this project is “showing our working” so documenting any design decisions you make, current draw calculations, trace sizes etc would be valuable.

The new daughterboard needs to fit into the slot for the old daughterboard, and must match its pinout. We have 3 digital inputs available to the daughterboard, ENABLE, IN_1 and IN_2 and 2 Analog outputs from the daughterboard. The analog outputs go through a set of buffers to feed the ADC pins on each MCU, and both have a 470r resistor to GND. 

On the schematic it shows 4 digital inputs, so I would have a quick chat with Tim Drysdale (CCed In) and ask him if we can tie the two LEDs to the drive and the load pin. This means we would have 2 digital inputs, and one spare. Don’t worry about the encoder as that plugs directly into the motherboard and doesn’t need any additional work.

I don’t know if it is required, but it might be worthwhile thinking about adding some kind of current sensing to the daughterboard which can be output on the analog pins. This could be via a current sense IC, or some other method. It would likely need to measure current through the coil in both directions, but this is a stretch goal. The important part is just replicating the function of the existing circuit.

Power input into the daughterboard – unfortunately I didn’t think of putting 5v on any of the spare pins, however there is a 5v header on the motherboard, so we will run a wire from here into a large 5v Vin pin on your daughterboard. The coil connections will come out on 2 large pads, like the motor driver board and this will be wired to the screw terminals on the motherboard. 
