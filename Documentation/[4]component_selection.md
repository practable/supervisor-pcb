# Component Selection & PCB Specification - [Project Title]

_A form to document and record specific part selections and PCB specifications for use during the PCB layout, and with PCB fabrication services like JLC PCB._ 


## Pre-PCB Layout Process

1. Verify schematic is correct.
2. Use Reference Designator tool to assign parts numbers to schematic symbols.
3. Perform Electrical Rules Check - NOTE: There will always be some errors & warnings that are unable to be cleared, this is not a problem as long as each one can be justified for your use case.
4. Assign footprints, use specified parts & JLCpcb parts library to cross check selected components against suitable item in parts libary. This will ensure that selected part is attainable and cost effective before moving onto layout.
5. Assign footprints to each component using the assign footprints tool. Use the [Component Selection] section of this form to assist in picking the correct parts & footprints. It is helpful
to gather specific parts numbers and suppliers at this stage.
6. Define net classes in Eschema using [File] > [Schematic Setup] > {Project} -> [Net Classes]. See [Net Classes]() below.
	- Note: This is only viewable on the schematic for now. Don't change line thickness, but different colours can be used to make sure net classes are being assigned correctly.
	- When we move into PCB layout we can define the thickness required for each net class.
7. Open PCB in board editor.




## Component Selections Notes

_This document should be filled in alongside assigning footprints in eschema, to ensure that the correct footprints have been selected before moving to PCB layout. At this stage of the 
design process, it is important to consider fabrication and start colating information that will be required by the fabrication house._

#### Tips & Considerations:

1. Check advantages of TH or SMD/SMT, especially regarding electrolytic capacitors, cost of component Vs Ease of Sourcing Vs Cost/Time to Manufacture should be considered.

2. Consider the advantages of automated assembly Vs Hand Soldered components. for JLC:
	- Hand soldering fee is: $3.5 + ($0.02 PER JOIN)
		- 1 extra day of assembly time.
		- "We accept the single-sided placement, so parts for manual and SMT assembly only can be placed on the same side."
	- SMT setup fee is: $8.00 + ($0.0015 PER JOIN)
	
	SMT is a higher initial cost, but lower per join. For current design, there are ~ 600 Joins, so cost is:
	- [Board Cost] + [Stencil?maybe] + [$8 SMT SETUP] + [600 * $0.0015] + [Component Costs] + [Shipping] = Board Cost + $8.90 + Components + shipping
	For TH heavy design using same number of components:
	- [Board Cost] + [$3.5 HAND SOLDERING] + [600 * $0.02] + [Component Costs] + [Shipping] = Board Cost + $15.5 + Components + shipping

3. Cost difference between Basic & Extended parts from JLC parts library
	- "When a part from the Extended Components Library is used, the operator needs to mount the feeders manually,
		which increases the labor cost, ***we charge $3 per extended component.***"
		
	- This represents the largest potential for cost saving by trying to use basic parts as often as possible over extended parts.
		
4. Minimum order quantity: If a part is used that has a MOQ of 100, and the board uses 1, you will be charged for 100. Double check and try and source components with a MOQ that is suitable for
the quantity of parts you actually require.

5. What is Ext price? - Only relivent if adding components to personal parts library @ JLC. In this case MOQ is usually by "the reel" and is often in multiples of 1000.

6. Consider the information and Files needed for SMT assembly.
	- Gerber files [^gerber]
	- BOM [^1]
	- CPL Component Placement List / PNP Pick & Place File[^2]



## Components

_Components & Parts selection table_

#### JLC Sourced Components

| Type					|Value	| Footprint | Price(pU)	|Min Quantity	| Price(min Q)	|JLC Part No|Vmax	| SMD/TH 	|Basic Part?|
|---					|---	|---		|---		|---			|---			|---		|--		|---		|			|
|Film/MLCC				| 100n	| 0805		|0.0046		|	4000		|				|C49678		|100	|	SMD		|	Yes		|
|Film/MLCC				| 22n	| 0805		|0.0112		|	4000 or 20	| 0.0112		|C1804		|50		|	SMD		|	Yes		|
|Electrolytic Capacitor | 100u 	| 6.3x7.7	|0.0895		| 	900			| 80.55			|C65221		|35		|	SMD		|			|
|Electrolytic Capacitor | 22u	| 6.3x5.4	|0.0383		|  	1000 or 10?	| 38.3			|C72505		|50		|	SMD 	|			|	
|Film/MLCC				| 1n	| 0805		|0.0076		| 	4000 or 20? | 30.4			|C46653		|50		|	SMD		|	Yes		|
|Electrolytic Capacitor	| 680u	| 12.5x20	|0.2914		|	100 or 1?	| 29.14			|C270015	|50		| 	TH		|			|
|Electrolytic Capacitor	| 220u	| 6.3x7.7	|0.0467		|	1000 or 10	| 46.7			|C2887273	|16		| 	SMD		|	Yes		|
|Film/MLCC				| 4n7	| 0805		|0.0054		| 	4000 or 20? | 21.6			|C1744		|50		|	SMD		|	Yes		|
|Zener Diode			| 18v 	| MINIMELF	|0.0289		|	2500 or 20	|	72?			|C410854	|19.1	|	SMD		|			|	
|LED					| Blue	| 0805		|0.038		|	3000		|	114?		|C138557	| n/a	|	SMD		|			|
|Schottky Diode 1N5821	|SS36-E3| DO-214AB	|0.3063 	|	850 or 2	|  255!?!		|C35722		| 60	| 	SMD		|	Yes	 	| Used D_SMA Footprint
|PRTR5V0U2X				|		| SOT-143	|0.0649		|	3000 or 10	| 				|C2827688	|		|	SMD		|			|
|LED					|Green	| 0805		|0.0178		|				|				|C84257		|		|	SMD		|			|	
|LED					|Red	| 0805		|0.0123		|				|				|C84256		|		|	SMD		|	Yes		| 
|USB Connector			| A   	| USB-A-TH	|0.0343		|	100 or 20	|	3.43		|C46406		|		|	TH		|			|
|USB Connector			|Mini B | USB mini-B - Lumburg|0.0615|	1000 or 10 | 61.5		|C2681563	|		|	SMD		|			|
|Inductor				|10uH	| 0805		|0.0166		|	4000 or 20	| 64			|C1046		|		|	SMD		|	Yes		|
|Inductor				|33uH	| 12x12x8	|0.3181		| 500 or 1		|159.05			|C339951	|		| 	SMD		|  			|
|Power MOSFET			|IRF5305|TO-263-2	|1.1936		|	50 or 1		| 55.			|C878890	|		|	SMD		|			|
|NPN BJT				|BC817	| SOT-23	|0.0177		|3000 or 50		| 53.0			|C181151	|		|	SMD		|			|	
|PNP BJT				|BC807	| SOT-23	|0.0271		|3000 or 50		| 53.0			|C8587		|		|	SMD		|	Yes		|
|Resistors				|10k	| 0805		| 			|				|				|C17414		|		|			|			|
|Resistors				|1k		| 0805		| 			|				|				|C17513		|		|			|			|
|Resistors				|330r	| 0805		| 			|				|				|			|		|			|			|
|Tactile Switch Pushbutton|SPST	| EVQPE1	|0.0544		| 4000 or 10	|  217.6		|C455280	|		|	SMD		|			|
|ESP32-WROOM-32U		|		|ESP32-		|4.0605		|	650 or 1	|	2600		|C328062	|		|	SMD		|			|
|AMS1117-3.3 3V3 LDO	|3V3	| SOT-223-3_TabPin2	|0.1734	|2500		|				|C6186		|		|	SMD		|	Yes		|
|AtMega328p-MU			|		|QFN-32		|8.9386		|490 or 1		| expense		|C967933	|		|	SMD		| 			|
|ACS712xLCTR			|		|SOIC-8_3.9x4.9x1.27|2.8912|3000 or 1	| much expense	|C10681		|		|	SMD		|			|
|LM2596S-5				|5vFixed|TO-263-5	|0.7778		|500 or 1		|MuchExpenseWow	|C347421	|		|	SMD		| 			|
|CH340				|	|SOP/SOIC-16_3.9x10.1x1.27P|0.8454|50 or 1		|				|C84681		|		|	SMD		|			|
|TXS0102DTC			|	|SSOP-82.8x3.0x0.65	|0.5977		|3000 or 1		|				|C324082	|		|	SMD		|			|
|TL431					|		|SOT23-3	|0.0394		|3000 or 15		|				|C181103	|		|	SMD	 	|			|
|HEF4093 NAND Gate Shmitt|		|SOIC-14_3.9x8.7x1.27|0.2356|2500 or 1	|				|C7867		|		|	SMD		|			|
|5032-4P Xtal			|16MHz	|Xtal_SMD_abracon_ABM3C-4p_5.0x3.2|0.4071|1000 or 1|	|C242216	|		|	SMD		|			|
|MOSFET					|SI2301CDS|SOT-23-3	|0.0941		|	3000 or 15	|				|C10487		|		|	SMD		|	Yes

So far 23 extended components @ $3 each = $69 extra fee for component loading in pick & place machine.


#### Parts Options
_Alternative options for components that have been rejected_

| Type					|Value	| Footprint | Price(pU)	|Min Quantity	| Price(min Q)	|JLC Part No|Vmax	| SMD/TH 	|Basic Part?|Reason Against|
|---					|---	|---		|---		|---			|---			|---		|--		|---		|---		|---		|
|Tactile Switch pushbutton|SPST	|SW4_5.1x5.1x5.1|0.0169	|4000 or 5		|	67.6		|C318884	|		|	SMD		|	Yes		|	No suitable Footprint		|
|AtMega328p-AU			|		|TQFP-32_7x7mm_P0.8mm|8.9386|490 or 1	| expense		|C14877		|		|	SMD		| 	Yes		|	16 dollars! |

	


#### Externally Sourced Components
_Components that must be sourced seperatly due to stock @ JLC or due to cost difference_ 

_Note: Components purchased seperatly will need to be assembled by the client, JLC will not accept 3rd party components for their in house fabrication service._

| Type 			| Value | Footprint 	| Price(pu)	| Min Q	| Price (Min Q)	|	Supplier 		| Supplier ID 	| Link 	|
|---			|---	|---			|---		|---	|---			|---				|---			|---	|	
| XT60			| male	| custom		|			|		|				|					|				|		|
| XT30			| female| AMASS_XT30PW-F|1.34		|1		|1.34			|Switch Electronics	|482193			|https://www.switchelectronics.co.uk/female-xt60pw-gold-plated-connector-30a-amass |
| Fuse/Holder	|		|				|			|		|				|					|				|		|
| Fan			| 40\*10.5mm|Fan12v12V_40by10.5mm|	|		|				|					|				|		|
| Screw Terminal?|||||||||






## Net Classes
_List Net Classes & Specifications._


1oz Copper = ~35 um (0.035mm)
2oz Copper = ~70 um   


All trace width calculations assume:
- Trace Thickness to be 0.070mm
- External Conductors

 **THIS DESIGN REQUIRES 2oz Copper for external layers!**
 
 In order to lower the operating temperature, high current BUS will be routed over 2 layers and stiched with vias, however calculations
 are performed assuming JUST the external conductor layer.
 
 Formula used:
 
 I = K * dT^(0.44) * (W * H)^(0.725)
 
 Where:
 
 I = Max Current (A)
 dT = Temperature rise above ambient (degC)
 W = width (mil)
 H = Thickness/height (mil)
 K = Constant for Internal Traces (0.024) or External Traces (0.048)

_all distances in mm_


| Bus/Net Class		| Type 	| Vmax	| Vtyp 	| Imax 	| Ityp 	| Pmax	| Ptyp	|dt	|Width	|Clearance	|Vias	|Colour	| Notes |
|----				|----	|----	|----	|----	|----	|----	|----	|---|----	|----		|----	|----	|----	|
| Default			|Signal	| 	12	|	5	|		|		|		|		|20	|0.2	| 	0.2		| 0.8	|Default|		|		
| GND				|Power	|	0	|	0	|	16	| 6.16	|		|		|20	|2.5	|	0.2		| 	" 	|Brown 	|	|
| PWR_GND			|Power	| 	0	|	0	| 28.83	|		|	346	|150.9	|20	| 6.5	|	0.2		|		|RedBrown		|Same power requirements as 24V_BUS			|
|DIGITAL_GND		|Power	|	5	| 	0	|	n/a	|		|		|		|20	|0.3		|			|		|Grey		|		|
| MID_PWR_BUS		|Power	|		|		|   12	|		|		|		|20	| 3		|x||bright Yellow| For power bus connections near end of long runs - ensure no more than 2 per|
| 24V_BUS			|Power	|	30	|	24	| 14.4	| 6.16	|	346	| 147.9	|20	|4		|	0.2		|	"	|Red	|24v must be able to provide sum total of all other power bus		|
| 12V_BUS			|Power	|	12	|	12	| 20.83	| 10.2	|	250	| 122.4	|20	|6.5	|	0.2		|	"	|Orange	|Imax is @ max power available from DC/DC - Unlikely condition	|
| 5V_BUS			|Power	|	5	|	5	| 16	| 4.8	|	81	| 24	|20	|4.5	|	0.2		|	"	|Yellow	|Imax assumes 6x raspi drawing 2.5A, typical is 0.4-0.8A	|
| MCU_5V_BUS		|Power	|	5	|	5	| 3		| 0.5	|	15	| 1.5	|20	|0.3	|	0.2		|	"	|Lime	|max taken from max available from large wall plug USB chargers	|
| USB_PBUS			|Power	|	"	|	"	| "		|  "	|	"	| " 	|20	|0.3	|	0.2		|	"	|Aqua	|Same as above Not included in 24v calcs	|
| Digital			|Data	|	5	|	2.5	|	n/a	|	n/a	|	n/a	|	n/a	|20	|0.2	|	0.2		|	"	|Purple	|		|
| CURRENT_SENSOR	|Power	|	12	|	12	|20.83	|	10.2|		|		|20	|7		|	0.2		|	"	|Blue	| High Current + Low Temp Rise Required + Heatsink		|
| ANALOG			|Analog |	5	|	2.5	| mA   	|  mA	|	n/a	|	n/a	|20	|0.2		|	0.2		|	"	|Pink	|		|
|PWR_OUTPUT			|Power	| 		|		| 8		|		|		|		|20	| 2		|			|		|		|	for one single high current OP	|


Trace Thicknesses have been modified during routing to account for DRM violations where tracks meet footprint pins. 
In each case judgement can be made, EG the 12v bus is specified for full 20A
current for 5x experimental outputs, however in order to fit everything on the PCB, this width must be ristricted where possible.

In this case, the last connections on this bus provide current to a single experimental output, so the trace has been specified for 12A, and 3mm width. 
This is still over specification for the requirements at this point on the bus, giving reassurance that it can perform within the required tolerances, leaving some spare capacity 
for future use cases.  



## PCB Layout Process

1. Group components by functional block and move them off to the side. 
2. Draw PCB outline.
2. Turn off GND nets using [Appearance] > [Nets] toolbar, as all grounds can connect directly to GND plane on bottom copper layer.
3. Place all mechanical hardware, I.E Any component that has a specific location to meet operational needs, line up with other PCBs, or enclosures, buttons that may need to be spaced
	specifically for ergonomic reasons etc.
4. Arrange functional blocks of components, minimising nets crossing and aiming to get joined pins as close to each other as possible.
5. Move functional blocks into free space on the PCB, taking care to minimise distances and number of nets that cross each other. This is not a perfect process, and no layout meets idealised
design parameters. Choose your priorites.
6. Rearrange components as needed to make the layout more efficient.
7. Once all components are placed on PCB, start running traces. Prioritise:
	- 1. High Power traces as they take up more space on the PCB
	- 2. Single components with a large number of connections (MCUs, large connectors, etc)
	- 3. Traces which cross large areas of the PCB.
	Deprioritise:
	- Short local connections, these will be easy to join later using free layers
	- Ground connections, any missing at the end can usually be easily joined using a short trace and via to GND plane.
	
	Note:
	- Avoid using B.Cu layeras much as possible, as we want a single GND plane to cover the entire back of the PCB with little breaks through it.
	- Use vias where needed, but bear in mind overuse can make tracing the circut difficult and messy.
	- Dont be afraid to delete all traces and start again - it usually takes me at least 3 starts before I can complete the circuit, and often this still requires large deletions and changes.

Repeat steps 6 & 7 until all nets except GNDs are joined with copper traces.

8. Use Add Filled Zone tool to fill B.Cu with a GND plane.
9. Use vias and short traces to join any remaining GND pads to GND plane.

10. Run DRC - Design Rules Check. Expect warnings and errors.

Repeat steps 6 - 10 untill DRC is passed, or errors/warnings can be justified, eg. Soldermask & Silkscreen layers can intersect, however it will throw warnings.

11. Aestheic checks. Using the 3D viewer, ensure that silkscreen layer is legiable and has the information required. Add Text, graphics, anything else required for the correct fabrication.


## TODO

PCB Layout


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
