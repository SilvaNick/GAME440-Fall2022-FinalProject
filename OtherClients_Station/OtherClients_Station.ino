#include <ESP8266WiFi.h>
char ssid[] = "Dreki";
char pass[] = "VetrarDreki";
const int buttonPin = D5;
const int ledRed = D2;
const int ledGreen = D1;

int buttonState = 0;

IPAddress server(192, 168, 20, 229);
WiFiClient client;


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Serial.println();
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
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
}

void loop() {
  //old code for testing sending a message to server and basics of the station code
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    client.connect(server, 80);
    int rand = random(10, 31);
    client.print("2");
    rand = rand * 1000;
    delay(rand);
  }
  else{
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
  }   

  // section for new code:
  // if statements for determining if bodyguard, king, or assassin triggered the card reader
  // if bodyguard, mimic the code from above
  // if assassin, same code except...
  // int rant = 30;
  // skip client print
  // if king, completely ignore the reading and do nothing
  // the old else statement should work as intended for this iteration
}
