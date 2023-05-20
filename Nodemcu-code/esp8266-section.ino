//THIS PROJECT AS A WHOLE WILL NOT WORK IF YOU DO NOT CONNECT IT WITH HOTSPOT.

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <SoftwareSerial.h>
//-----------------------------------------------------------
const String web_app_url = "YOUR google sheets APP SCRIPT";
//-----------------------------------------------------------
#define WIFI_SSID "YOUR SSID"
#define WIFI_PASSWORD "PASSWORD"
//-----------------------------------------------------------
int blocks[] = {4,5,6,8}; // add new block number here.
#define blocks_len  (sizeof(blocks) / sizeof(blocks[0]))
//-----------------------------------------------------------
//GPIO 0 --> D3
//GPIO 2 --> D4
//GPIO 4 --> D2
//GPIO 5 --> D1
#define RST_PIN  5
#define SS_PIN   4
//#define BUZZER   0 // if you want to add buzzer.
//-----------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
MFRC522::StatusCode status;      
//-----------------------------------------
/* Be aware of Sector Trailer Blocks */
int blockNum = 2;  
float  vol;
int c,q;
/* Create another array to read data from Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
byte bufferLen = 100;
byte readBlockData[100];
//-----------------------------------------
String pointer[4]; //replace 4 with blocks_len if you are using different number of blocks


/****************************************************************************************************
 * setup() function
 ****************************************************************************************************/
void setup()
{
  //--------------------------------------------------
  /* Initialize serial communications with the PC */
  Serial.begin(9600); // start serial communication
  //--------------------------------------------------
  //WiFi Connectivity
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //--------------------------------------------------
  /* Set BUZZER as OUTPUT */
  //pinMode(BUZZER, OUTPUT);
  //--------------------------------------------------
  /* Initialize SPI bus */
  SPI.begin();
  //--------------------------------------------------
}

/****************************************************************************************************
 * loop() function
 ****************************************************************************************************/
 void loop()
{ String volume;
  char volbuff[10]="";
    if (Serial.available()>0) { // check if there is any data available from Arduino Uno
    delay(5000);
    volume = Serial.readStringUntil('\n');
    Serial.println(volume);}

  if(Serial.available()>0){
    while(q < 2){
    delay(3000);
      String temp , fullURL;
        //if(Serial.available()<=0){return;}
        c=0;
      //volume = String(vol);
       //Serial.println(volume + "1");
        temp = pointer[1] ;
      fullURL = "data" + String(1) + "=" + temp;

      temp = pointer[2] ;
      fullURL += "&data" + String(2) + "=" + temp;

      temp = pointer[3] ;
      fullURL += "&data" + String(3) + "=" + temp;
      
      temp = pointer[3] ;
      fullURL += "&data" + String(3) + "=" + temp;
      
      /* temp = pointer[3] ;
      fullURL += "&data" + String(3) + "=" + temp;*/
      // change values accordingly

    fullURL += "&data" + String(4) + "=" + volume;
  
  //Serial.println(fullURL);
  fullURL.trim();
  fullURL = web_app_url + "?" + fullURL;
  fullURL.trim();
  Serial.println(fullURL);
  //------------------------------------------------------------------------
  //digitalWrite(BUZZER, HIGH);
  //delay(200);
  //digitalWrite(BUZZER, LOW);
  //delay(200);
  //digitalWrite(BUZZER, HIGH);
  //delay(200);
  //digitalWrite(BUZZER, LOW);
  //delay(3000);
  //------------------------------------------------------------------------

  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  if (WiFi.status() == WL_CONNECTED) {
    //-------------------------------------------------------------------------------
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    //-------------------------------------------------------------------------------
    client->setInsecure();
    //-------------------------------------------------------------------------------
    HTTPClient https;
    Serial.print(F("[HTTPS] begin...\n"));
    //-------------------------------------------------------------------------------

    //HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
    if (https.begin(*client, (String)fullURL)){
      //-----------------------------------------------------------------
      // HTTP
      Serial.print(F("[HTTPS] GET...\n"));
      // start connection and send HTTP header
      int httpCode = https.GET();
      //-----------------------------------------------------------------
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // file found at server
        q = q+1;
      }
      //-----------------------------------------------------------------
      else 
      {Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());}
      //-----------------------------------------------------------------
      https.end();
      delay(1000);
    }
    //HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
    else {
      Serial.printf("[HTTPS} Unable to connect\n");
    }
    //HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
  }
    
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
}
  }
  //------------------------------------------------------------------------
  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  /* Look for new cards */
  /* Reset the loop if no new card is present on RC522 Reader */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  /* Select one of the cards */
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  /* Read data from the same block */
  Serial.println();
  Serial.println(F("Reading last data from RFID...")); 

  //------------------------------------------------------------------------
  String fullURL = "", temp;
  char a = 'A';//this will be sent to arduino as a response that card has been read
  Serial.write(a);
  while(c < 5){
    q=0;
  for (byte i = 1; i <= blocks_len; i++) {
    if(i < blocks_len){
    ReadDataFromBlock(blocks[i], readBlockData);
    if(i == 1){
      temp = String((char*)readBlockData);
      temp.trim();
       pointer[i] = temp;
      fullURL = "data" + String(i) + "=" + temp;
    }
    else{
      
      temp = String((char*)readBlockData);
      temp.trim();
       pointer[i] = temp;
      fullURL += "&data" + String(i) + "=" + temp;
      }}}
      c=c+1;
  }
    //-----------------------------------------------------------------------
 //uncomment this if values are not getting uploaded.   
 /*if(Serial.available()>0){
      String temp;
        //if(Serial.available()<=0){return;}
        c=0;
      //volume = String(vol);
       //Serial.println(volume + "1");
        temp = pointer[1] ;
      fullURL = "data" + String(1) + "=" + temp;

      temp = pointer[2] ;
      fullURL += "&data" + String(2) + "=" + temp;

      temp = pointer[3] ;
      fullURL += "&data" + String(3) + "=" + temp;

    fullURL += "&data" + String(4) + "=" + volume;
    
  //Serial.println(fullURL);
  fullURL.trim();
  fullURL = web_app_url + "?" + fullURL;
  fullURL.trim();
  Serial.println(fullURL);
  //------------------------------------------------------------------------
  //digitalWrite(BUZZER, HIGH);
  //delay(200);
  //digitalWrite(BUZZER, LOW);
  //delay(200);
  //digitalWrite(BUZZER, HIGH);
  //delay(200);
  //digitalWrite(BUZZER, LOW);
  //delay(3000);
  //------------------------------------------------------------------------

  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  if (WiFi.status() == WL_CONNECTED) {
    //-------------------------------------------------------------------------------
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    //-------------------------------------------------------------------------------
    //uncomment following line, if you want to use the SSL certificate
    //client->setFingerprint(fingerprint);
    //or uncomment following line, if you want to ignore the SSL certificate
    client->setInsecure();
    //-------------------------------------------------------------------------------
    HTTPClient https;
    Serial.print(F("[HTTPS] begin...\n"));
    //-------------------------------------------------------------------------------

    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
    if (https.begin(*client, (String)fullURL)){
      //-----------------------------------------------------------------
      // HTTP
      Serial.print(F("[HTTPS] GET...\n"));
      // start connection and send HTTP header
      int httpCode = https.GET();
      //-----------------------------------------------------------------
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // file found at server
      }
      //-----------------------------------------------------------------
      else 
      {Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());}
      //-----------------------------------------------------------------
      https.end();
      delay(1000);
    }
    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
    else {
      Serial.printf("[HTTPS} Unable to connect\n");
    }
    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  }
    }*/
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}




/****************************************************************************************************
 * ReadDataFromBlock() function
 ****************************************************************************************************/
void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{ 
  //----------------------------------------------------------------------------
  /* Prepare the ksy for authentication */
  /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //----------------------------------------------------------------------------
  /* Authenticating the desired data block for Read access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  //----------------------------------------------------------------------------s
  if (status != MFRC522::STATUS_OK){
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  //----------------------------------------------------------------------------
  else {
    Serial.println("Authentication success");
  }
  //----------------------------------------------------------------------------
  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //----------------------------------------------------------------------------
  else {
    readBlockData[16] = ' ';
    readBlockData[17] = ' ';
    Serial.println("Block was read successfully");  
  }
  //----------------------------------------------------------------------------
}
