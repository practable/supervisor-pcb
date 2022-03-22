# PCB Design Review - [Project Title] 

_A form to document and record the PCB design review after completing layout in PCB editor._ 


## Design Review Notes

1. What Verification & Validation checks have been/can be carried out?
2. DRC Violations?
3. Will design solve problems?


## DRC - Design Rules Check

_Note down any DRC failings, the solution to remove them or reason for ignoring_

#### Errors

6 Courtyard overlap Errors
 - No solution required as conflicting footprint is surface level & unpopulated.


#### Warnings

1 Track has unconnected end
 - Copper layer is acting as heatsink
 
4 Footprint has no courtyard
 - Applies to silkscreen logos only - Can be ignored.
 
 

## Required Documentation for Fabrication

For PCB Fabrication:

	- Gerber files - In zipped folder [^gerber]


For PCB Fabrication, with component population:
	
	- Gerber files - in zipped folder [^gerber]
	- BOM [^1]
	- CPL Component Placement List / PNP Pick & Place File[^2]



### Documentation Checklist

|PCB				| Folder		|Files				| Checked 	| Checked Via 	|
|----				|----			|----				|----		|----			|
|	ISOpowerPCB		|zipped gerbers	|F_Cu.gbr			|	[]		|				|
|					|				|In1_Cu.gbr			|	[]		|				|
|					|				|In2_Cu.gbr			|	[]		|				|
|					| 				|B_Cu.gbr			|	[]		|				|
|					|				|F_Mask.gbr			|	[]		|				|
|					|		 		|B_Mask.gbr			|	[]		|				|
|					|				|F_Silkscreen.gbr	|	[]		|				|
|					|				|B_Silkscreen.gbr	|	[]		|				|
|					| 				|F_Paste.gbr		|	[]		|				|
|					|				|B_Paste.gbr		|	[]		|				|
|					| 				|Edge_Cuts.gbr		|	[]		|				|
|					|				|PTH.drl			|	[]		|				|
|					|		 		|NPTH.drl			|	[]		|				|
|					|ISO_power_PCB	| BOM.csv			|	[]		| 			|
|					|ISO_power_PCB	| top-pos.csv		|	[]		| 				| 
|----				|----			|----				|	----	|----			|
|ISOpowerWiFi_PCB	|zipped gerbers	|F_Cu.gbr			|	[]		|				|
|					|				|In1_Cu.gbr			|	[]		|				|
|					|				|In2_Cu.gbr			|	[]		|				|
|					| 				|B_Cu.gbr			|	[]		|				|
|					|				|F_Mask.gbr			|	[]		|				|
|					|		 		|B_Mask.gbr			|	[]		|				|
|					|				|F_Silkscreen.gbr	|	[]		|				|
|					|				|B_Silkscreen.gbr	|	[]		|				|
|					| 				|F_Paste.gbr		|	[]		|				|
|					|				|B_Paste.gbr		|	[]		|				|
|					| 				|Edge_Cuts.gbr		|	[]		|				|
|					|				|PTH.drl			|	[]		|				|
|					|		 		|NPTH.drl			|	[]		|				|
|					|ISO_wifi_PCB	| BOM.csv			|	[X]		|	All Parts In Stock JLC PCB			|
|					|ISO_wifi_PCB	| top-pos.csv		|	[X]		|	checked against BOM			|
|					| 				|					|	[]		|				|
|					|				|					|	[]		|				|


## Fabrication Notes

- Keep track of Component Stock, is it required for external fabrication, or purchased seperatly for manual assembly?

- JLC offer for free, specific location for their manufacturing number. Specify with "JLCJLCJLCJLC" on the silkscreen level.







## TODO




# Notes

[^gerber]: List of commonly used file names & formats, accepted by the majority of fabrication houses:
			- F.CU


[^1]: BOM Bill Of Materials
Reccomended formats: .csv, .xls, .xlsx
Example:
| Comment	| Designator	| Footprint | JLCPCB Part # (optional) 	|
|---		|---			|---		|---						|
|	100nF	|  C1			| 0805		|C49678 					|
|	22u		|  C2-5			| 6.3x5.4	|C72505						|
|	100uF	|  C6, C8, C10	| 6.3x7.7	|C65221						|

[^2]: Pick & Place or CPL File <br>
The Pick & Place File must contain the information below:

-	Designator - Component Reference Designator (e.g. C1, L2, R3)
- 	Mid X/Mid Y - The X/Y coordinate of the component centroid. Recommended units: Metric(mm). 
-	Layer - Top / Bottom, the board side where the component should be placed. 
-	Rotation - The rotation of the component given in degrees. Positive values are counter clockwise.
-	Recommended File Format: .csv, .xls and .xlsx.
Example:
| Designator 	| Mid X 	| Mid Y 	| Layer 	| Rotation 	|
|--				|---		|---		|---		|---		|
|	C1			| 95.0518mm	|22.6822mm	|	T		|	270		|
|	C2 			| 106.4056mm|33.2342mm	|	B		| 	90		|