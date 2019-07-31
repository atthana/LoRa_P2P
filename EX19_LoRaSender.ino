/*
 * EX19_LoRaSender
 * ทดสอบส่งข้อมูลผ่านเครือข่าย LoRa พร้อมแสดงค่า RSSI
 * บนคลื่นความถี่ 433MHz
 */
 #include<ArduinoJson.h>
#include <U8x8lib.h>
#include <LoRa.h>
#include <SimpleDHT.h> 

String receivedText;
String receivedRssi;
//String packageForSending = "Q-Love";
String packageForSending = "Q-Love";

// WIFI_LoRa_32 ports

// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS      18
#define RST     14
#define DI0     26
//#define BAND    923.2E6
#define BAND    921E6
#define PABOOST true

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(15,4,16);

int counter = 0;

//=================== Setup DHT 11 ============================
int DHTPIN = 21; 
SimpleDHT11 dht11;              //defind model of sensor : DHT11
byte temperature = 0;         
byte humidity = 0;  
//=============================================================

void setup() {
  pinMode(25,OUTPUT); //Send success, LED will bright 1 second

  Serial.begin(115200);
  delay(1000);

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  
  Serial.println("LoRa Sender");
  u8x8.drawString(0, 1, "LoRa Sender");
  
  SPI.begin(5,19,27,18);
  LoRa.setPins(SS,RST,DI0);
  
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(5);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setPreambleLength(8);

  if (!LoRa.begin(BAND,PABOOST)) {
    Serial.println("Starting LoRa failed!");
    u8x8.drawString(0, 1, "Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initial OK!");

    

  // StaticJsonObject allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument  doc(200);

  // Add values in the document
  //
 
  
  
  Serial.println();
}

void loop() {
  
  Serial.print("Sending packet: " + packageForSending + " : ");
  //Serial.print();
  u8x8.drawString(0, 4, "PacketID");
  Serial.println(counter);
  String txt = String(counter);
  
  char currentid[5];
  txt.toCharArray(currentid, 64);
  u8x8.drawString(9, 4, currentid);
readTemp();
StaticJsonDocument<200> doc;
  // send packet
  LoRa.beginPacket();
   doc["temp"] = String(temperature);
  doc["humi"] =String(humidity);

  serializeJson(doc, LoRa);
  
  //LoRa.print(packageForSending);
  //LoRa.print(counter);
  //LoRa.print(humidity);
  LoRa.endPacket();
  serializeJson(doc, Serial);
   u8x8.drawString(0, 5, "Payload");
   //=======================================
   char charBuf[8];                           // new from Sachi to display by variable
   packageForSending.toCharArray(charBuf, 8); // new from Sachi
   u8x8.drawString(9, 5, charBuf);            // new from Sachi
   //u8x8.drawString(9, 5, "hello");
   //=======================================
   
   char buffer_temp[30];
   char buffer_humi[30];
   String str_temp;
   String str_humi;

   str_temp = "Temp : " + String(temperature) + " C'";
   str_humi = "Humi : " + String(humidity) + " %";
   str_temp.toCharArray(buffer_temp, 30);
   str_humi.toCharArray(buffer_humi, 30);
      
   u8x8.drawString(0, 6, buffer_temp);
   u8x8.drawString(0, 7, buffer_humi);
   
   
  counter++;
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  
  delay(3000);
}

void readTemp(){
  
    dht11.read(DHTPIN, &temperature, &humidity, NULL);  // Read value from sensor
    delay(2000);                                    //wait 2 seconds
    Serial.print("DHT11 read: ");
    Serial.print((int)temperature); Serial.print(" *C, "); 
    Serial.print((int)humidity); Serial.println(" %H");
  }
