// remove Tx and Rx before uploading.

#include<Wire.h>
#include <LiquidCrystal_I2C.h>

const int IR_PIN = A0; // IR sensor output pin
const int RELAY_PIN = 4; // Relay control pin

int irValue; // Variable to store the IR sensor value
LiquidCrystal_I2C lcd(0x3F , 16 , 2);

volatile int flow_frequency; // Measures flow sensor pulse

// Calculated litres/hour

float vol = 0.0,l_minute,speed;
int check,flag;

unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;


void flow () // Interrupt function
{
   flow_frequency++;
}

void setup()  
{
  Serial.begin(9600); // try to change your baud rate if you do not see any thing on your serial monitor
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); 
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  currentTime = millis();
  cloopTime = currentTime;
     
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Fluid Quantifer");
  lcd.setCursor(0,1);
  lcd.print("Welcome IIITVICD");

  // Initialize the IR sensor and relay pins
  pinMode(IR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}


void loop() 
{
    char c;
    irValue = digitalRead(IR_PIN);
    if (Serial.available()>0) { // check if there is any data available from NODE MCU
    c = Serial.read();
    }
  // If the IR sensor does not detect an object, turn off the relay
  if (irValue == HIGH) 
  {
    digitalWrite(RELAY_PIN, HIGH);
    if (vol > 0) 
    {
      while(flag < 15)
      {
        delay(1000);
        String volume = String(vol);
        Serial.println(volume);
        delay(2000);
        flag= flag+1; 
        c = 'Z';
        check=0;
      }
    }
  }
  // Otherwise, turn on the relay
  else
  {
    if(c == 'A') // if node mcu do not sends any value the relay won't start.
    {
      digitalWrite(RELAY_PIN, LOW);
      if(check== 0)
      {
        check=10;
        flag = 0;
        vol=0; // resets volume to 0 for each new use.
      }
    }
  }

  currentTime = millis();
  // Every second, calculate and print litres/hour
  if(currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0)
    {
      //Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = ((flow_frequency )/ 7); // (Pulse frequency x 60 min) / 7Q = flowrate in L/hour. if you get error in total reading use 7.5.
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print(flow_frequency);
      lcd.print(" L/hr");
      l_minute = l_minute/60;
      //basically you have to change some values to calibrate your code because sensors do not work at their given values as mentioned in their data sheet.
      vol = vol +l_minute;
      lcd.setCursor(0,1);
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
      flow_frequency = 0; // Reset Counter
      //Serial.print(l_minute,DEC);
      //Serial.println("L/hour");
    }
    else //when there is no reading at the sensor.
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print( flow_frequency );
      lcd.print(" L/hr");
      lcd.setCursor(0,1);
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
    }
  }
}
