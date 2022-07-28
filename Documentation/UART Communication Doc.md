# UART Communication with Arduino Nano 33 IoT and Odroid C4 (Ubuntu MATE)/Raspberry Pi (Raspberry OS)
*Author: Bhavith Manapoty
Created On: 28 July 2022
https://bhavithmanapoty.com*

**Note: All steps are identical for ODROID and Pi unless otherwise stated.**

**For ODROID, the home directory is /home/odroid
For Pi, the home directory is /home/pi**

**This documentation has been tested for both ODROID and Pi, but all comands in this documentation were initially written for ODROID. Thus, all file location commands might need to be modified to match your device appropriately.**

### Connections:
|Nano|RPi/ODROID Pin No.|RPi Pin Name|ODROID Pin Name|
|-----|-----------|--------------|-------------------|
|3v3|1|3v3|3v3|
|GND|6|GND|GND|
|Rx0|8|Tx|Tx|
|Tx0|10|Rx|Rx|
|RST|12|GPIO 18|GPIO 1|

## Install Arduino-CLI

```
sudo apt-get update && upgrade -y
```
```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```
```
arduino-cli
```
The above command should output a list of all available arduino commands. If you get an error that says arduino-cli cannot be found, then you might need to add it to your PATH, by doing the following.
```
nano ~/.bashrc
```
Next add the following line to the end of the file.
```
export PATH=$PATH:/home/pi/bin
```
Now we need to reboot our device.
```
sudo reboot
```
## Configure Arduino-CLI:
Once the installation script has completed we will first need to create a configuration file using the following command.
```
arduino-cli config init
```
This will create a configuration YAML file and echo the path in which the file was created.

## Create Blink Sketch
Now we need to create our first sketch to upload. There is some further configuration required so for now we will just create a basic blink sketch in order to complete the configuration.

```
arduino-cli sketch new blink
```
```
nano blink/blink.ino
```
In this file, we need to add the following code:
```
void setup() {
    pinMode(13, OUTPUT);
}
 
void loop() {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
```

## Modify Arduino-CLI to enable Serial UART
Now, we need to add the board cores for the Arduino AVR Boards and SAMD boards. To this, run the following commands:
```
arduino-cli core update-index
```
```
arduino-cli core install arduino:avr
```
```
arduino-cli core install arduino:samd
```
```
arduino-cli core update-index
```

Now we can make the necessary modification to arduino-cli in order to support the GPIO serial port. The serial port itself will work without modification, however we need to add DTR functionality so that the Arduino is reset into bootloader mode by a spare Raspberry Pi GPIO pin. For this, we need to locate the avrdude folder. This folder location can change for every installation and thus needs to be found using a verbose output from arduino-cli.

Run the following command:
```
arduino-cli compile --fqbn arduino:avr:nano blink -v
```

The compiler will run with more output than usual, producing a mess of output before echoing the usual success message. Within this information you will be able to see the path to the tools folder towards the end of the output.

For me, the path is ```cd /home/odroid/.arduino15/packages/arduino/tools/```. Once in this directory, we need to open the bin directory.
```
cd avrdude/6.3.0-arduino17/bin
```
Next we need to rename the avrdude file within the bin directory to avrdude-original.
```
mv avrdude avrdude-original
```
Now we can download the modified avrdude files by entering the following curl commands.
```
curl https://raw.githubusercontent.com/Siytek/avrdude-rpi/master/autoreset -o autoreset
```
```
curl https://raw.githubusercontent.com/Siytek/avrdude-rpi/master/avrdude -o avrdude
```
Finally we need to install some dependencies to support the autoreset script, so go ahead and run the following command.
```
sudo apt-get install -y python-dev python-rpi.gpio minicom
```

**NOTE: To try and replicate the double tap reset required for Nano IoT33, we need to modify the new autoreset avrdude python file**
```
nano /home/odroid/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/autoreset
```
added these lines to the bottom of ```def reset()```
```
#added lines guessing at required delays
  time.sleep(0.5)
  GPIO.output(pin, GPIO.HIGH)
  time.sleep(0.32)
  GPIO.output(pin, GPIO.LOW)
  time.sleep(1)
```
### Instructions for ODROID C4:
If you are using an ODROID C4, we also need to change the pin Number in the autoreset file. If you are using a Raspberry Pi, skip to the next section.

Run the following command
```
nano /home/odroid/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/autoreset
```
and change the following line
```pin=18``` to ```pin=1```

This changes the GPIO Pin Number that is used by the script. ODROID uses GPIO Pin 1 wheras Raspberry Pi uses GPIO Pin 18.

-------------------------------------------
We also need to modify user permissions to make each file executable by any user.
```
sudo chmod ugo+rwx avrdude
sudo chmod ugo+rwx avrdude-original
sudo chmod ugo+rwx autoreset
```
Finally, we need to add the ```bin``` folder to our PATH
Navigate to the directory to be added to PATH
``` cd /home/pi/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin```
and enter the following command.
```
PATH="$(pwd):$PATH"
```
This needs to be repeated every time the Pi/ODROID is rebooted. To avoid this, this can be added to the bash file. To do this, enter the following command
```
sudo nano ~/.bash_profile
```
and add the following line at the end of the file.
```
export PATH="$PATH:/home/pi/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin"
```
Then run the following command
```
source ~/.bash_profile
```
This will permanently update your PATH to include the required folder.

Now when arduino-cli calls for avrdude, the newly added bash script will launch the original avrdude with the addition of using the autoreset script to pulse the Arduino reset pin just at the correct time. Awesome!

## Programming the Arduino Nano 33 IoT
Make the necessary connections as shown in the table at the start of the page and run the following commands.

First, we need to compile our sketch.
```
arduino-cli compile --fqbn arduino:samd:nano_33_iot blink
```
Next, we need to check which Serial port is being used by our Arduino Board. To do this, run the following command.
```
arduino-cli board list
```
This will show the available boards and their port. If there are multiple ports being displayed, then it is just trial and error until you find the right one :)

For me, my board is connected to port /dev/ttyS1.
Once you have your port, we can upload the code to the Arduino.

We need to place the Arduino Nano 33 IoT in programming mode by double clicking the reset button. Then run the following command.
```
   arduino-cli upload --port /dev/ttyS1 --fqbn arduino:samd:nano_33_iot blink
```
This should successfully upload your code to the Arduino Nano 33 IoT through UART Communication from the Raspberry Pi or ODROID C4.