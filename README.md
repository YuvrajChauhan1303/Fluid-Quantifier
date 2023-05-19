# Fluid-Quantifier
Fluid Quantifier tracks the water consumed by an individual at a certain time.

More In-Depth Explanation:

Fluid Quantifier uses a YFS-201 Sensor to accurately measure water flowing throug a pipe. It also uses an RFID Scanner System to track and record data for particular individuals. An IR Sensor Switch is used to power a Relay Switch ON or OFF. As an added security measure, it requires both RFID System and IR system to work as intended, So until you scan your NFC Card/NFC Tag, you wont be allowed to use water. We have also used a wifi module called NodeMCU to send Data to a databse, or to run a protocol that collects all the data from YFS-201, as well as from the RFID Scanner and prints it onto a Google SpreadSheet by running the protocol for an AppsScript. Arduino UNO R3 has been used as the Primary Brains for the Fluid Quantifier 
