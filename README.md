# Fluid-Quantifier
Fluid Quantifier tracks the water consumed by an individual at a certain time.

More In-Depth Explanation:

Fluid Quantifier uses a YFS-201 Sensor to accurately measure water flowing throug a pipe. It also uses an RFID Scanner System to track and record data for particular individuals. An IR Sensor Switch is used to power a Relay Switch ON or OFF. As an added security measure, it requires both RFID System and IR system to work as intended, So until you scan your NFC Card/NFC Tag, you wont be allowed to use water. We have also used a wifi module called NodeMCU to send Data to a databse, or to run a protocol that collects all the data from YFS-201, as well as from the RFID Scanner and prints it onto a Google SpreadSheet by running the protocol for an AppsScript. Arduino UNO R3 has been used as the Primary Brains for the Fluid Quantifier 

Step-By-Step Instructions to Build the Fluid Quantifier:
1. Components :
    -Arduino UNO
    
    -Breadboard/Project Circuit Board
    
    -Jumper Wires
    
    -Soldering Iron with Kit
    
    -LCD Display 16 x 2 (Change the Arduino-Code if you own a Bigger LCD or an oLED Display)
    
    -I2C Module for LCD Display
    
    -IR Sensor
    
    -Relay Switch
    
    -NodeMCU ESP8266
    
    -YFS-201 Hall Effect Sensor
    
    -MRCC522 RFID Scanner Kit
    
    -Arduino IDE
    
    -NodeMCU ESP8266 Driver (To make Laptop Compatible for NodeMCU)
    
    -Pump or Electric Valve
    
    -PVC Pipes (Inner Diameter : 1.5 inches)
    
    
2. Connections (Follow the Circuit Diagram/Pin Diagram Uploaded) :

    -Connect the RFID System to NodeMCU 
    
    -Connect IR Sensor to Arduino UNO
    
    -Connect LCD Display to Arduino UNO
    
    -Connect Relay to Arduino UNO
    
    -Connect Pump to Relay (connect power lines to COM and NO pins)
    
    -Connect YFS-201 Sensor to Arduino UNO
    
    -Connect NodeMCU to Arduino UNO
    
    -Upload the Code to NodeMCU (MAKE SURE RX AND TX PINS ARE NOT CONNECTED)
    
    -For Data Transfer Connect RX and TX pins (Connect RX from Arduino UNO to TX of NodeMCU and TX from Arduino UNO to RX of NodeMCU)

3. Precautions :
    -Always Connect NodeMCU to Internet before Using
    
    -Always Remove RX TX pins before uploading code
    
    -Dont Work with relay switch if Power is ON for PUMP
    
    -Wear Shoes while working with AC Power Supply for PUMP
    
    -If You wish to change digital Pins for Arduino Update Codes As well
