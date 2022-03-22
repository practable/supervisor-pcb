#Circuit Simulation

_File created to document any circuit simulation undertaken as part of the design process_




## High Side MOSFET Switches for Experiment power.

In order to control the 12v power to each experiment, a high-side P-Channel MOSFET switch was selected. In order to fully shut off power, this requires driving
the gate to ~12v. The following circuit was selected for driving the gate voltage to a Vmax ~12v from the 5v output of the AtMega328p.

![image](https://user-images.githubusercontent.com/53580358/154959532-70c2d510-0010-4a74-b4e7-872c0a8f85d9.png)


This circuit was simulated in Pspice using KiCAD.

### Vin = 0

Circuit: KiCad schematic <br>
Doing analysis at TEMP = 27.000000 and TNOM = 27.000000 <br>
Initial Transient Solution <br>

|Node|                                   Voltage
|----|                                   -------
|vcc|                                         12
|out |                                 0.0029115
|/vb2 |                                 0.686963
|xq2.11|                              0.00117613
|/vc    |                                6.34348
|/vb     |                           1.90442e-07
|xq1.11   |                              6.34348
|vin       |                                   0
|v1#branch  |                        -0.00176536
|v2#branch   |                       1.90442e-11
| Reference value : | 0.00000e+00
|No. of Data Rows :| 1008

#### Vin = 5

Circuit: KiCad schematic <br>
Background thread stopped with timeout = 0 <br>
Doing analysis at TEMP = 27.000000 and TNOM = 27.000000 <br>
Initial Transient Solution <br>

|Node  |                                 Voltage
|----   |                                -------
|vcc     |                                    12
|out      |                                   12
|/vb2      |                          0.00340635
|xq2.11     |                                 12
|/vc         |                        0.00340599
|/vb          |                         0.677878
|xq1.11        |                      0.00135468
|vin            |                              5
|v1#branch       |                   -0.00119966
|v2#branch        |                 -0.000432212
| Reference value : | 0.00000e+00
|No. of Data Rows : |1008


