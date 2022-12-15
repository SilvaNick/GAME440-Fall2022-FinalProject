#include <ESP8266WiFi.h>
char ssid[] = "NETGEAR";
char pass[] = "";
int attempts = 5;
int stations = 0;


WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  server.begin(80);
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (attempts == 0)
  {
    KingLives();
    attempts = -1;
  }
  WiFiClient client = server.available();
  if (client.connected()){
    Serial.println("Something connected!");
    String data = "";
    data = client.readStringUntil('\n');
    Serial.println(data);
    if (data == "0"){
      Serial.println("Guard dead");
      RemoveAttempt();
    }
    if (data == "1")
    {
      Serial.println("King Dead");
      KingDied();
    }
    if (data == "2")
    {
      stations = stations + 1;
      if (stations == 4){
        RemoveAttempt();
        stations = 0;
      }
    }
    else {
      Serial.println(data);
    }
    client.stop();
  }  
}

void KingLives(){
  //play buzzer? or some kind of notification that announces the end of the game
  //server.close();
  Serial.println("King Lives");
}

void KingDied(){
  //play another unique buzzer?/other notification that announces the end of the game
  //server.close();
  Serial.println("King Died");
}

void RemoveAttempt(){
  //play a third unique buzzer/other notification that announces the assassins lost an attempt
  //possibly make a unique sound for each attempt being lost? or do the players need to keep track themselves?
  attempts = attempts - 1;
  Serial.println("Attempt Lost");
}
