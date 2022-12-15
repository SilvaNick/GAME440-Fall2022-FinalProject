#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define SS_PIN 15
#define RST_PIN 0

char ssid[] = "NETGEAR";
char pass[] = "";
bool King = false;

IPAddress server(192, 168, 1, 5);
WiFiClient client;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

int shortDelay = 400;
int longDelay = 1000;

int yellowState = 0;
int greenState = 0;
int redState = 0;
int blueState = 0;

int role = 0;
bool alive = true;

String assassinID = "03 20 DD 11";
String kingID = "E3 D9 F7 11";
String assassinID2 = "B3 1B BE 11";

String animalName = "Pig";

void setup() 
{
  // Initiate a serial communication
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  SPI.begin();         // Initiate  SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan your card...");
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  int roundCount = 0;
  int playerTurn = 1;
  bool buttonPress = false;
  int currentNote;
  int userInput = 0;
  bool loss = false;
  delay(500);

  if (role == 0) {
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    if ((content.substring(1) == assassinID)) {
      role = 1;
      Serial.println("Assassin");
    } else if (content.substring(1) == kingID) {
      role = 2;
      Serial.println("King");
    } else if (content.substring(1) == assassinID2) {
      role = 1;
      Serial.println("Assassin");
    } else {
      role = 3;
      Serial.println("Guard");
    }
  }


  if (role != 0) {
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    if ((content.substring(1) == assassinID) && (role != 1)) {
      alive = false;
      if  (role == 2) {
        Serial.println("Dead!");
        client.connect(server, 80);
        client.print("1");
      }
      if  (role == 3) {
        Serial.println("Dead!");
        client.connect(server, 80);
        client.print("0");
        SendName();
      }
    }
    if ((content.substring(1) == assassinID2) && (role != 1)) {
      alive = false;
      if  (role == 2) {
        Serial.println("Dead!");
        client.connect(server, 80);
        client.print("1");
      }
      if  (role == 3) {
        Serial.println("Dead!");
        client.connect(server, 80);
        client.print("0");
        SendName();
      }
    }
    delay(150);
 
  }
}

void SendName(){
  client.connect(server, 80);
  client.print(animalName);
}