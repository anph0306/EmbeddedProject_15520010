#include <SocketIOClient.h>
#include <ESP8266WiFi.h>

SocketIOClient client;
const char* ssid     = "Redmi";
const char* password = "andeptrai";


char host[] = "52.221.207.44";
int port = 80;
extern String RID;
extern String Rname;
extern String Rcontent;
unsigned long previousMillis = 0;
long interval = 5000;
int i = 0, x = -1, y = -1;

void setup()
{
  Serial.begin(115200);
  delay(10);

   Serial.print("Connect to Wifi ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
         delay(500);
         Serial.print('.');
   }

    Serial.println();
    Serial.println(F("Wifi is connected"));
    Serial.println(F("ESP8266 IP address (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
 
    if (!client.connect(host, port))
    {
        Serial.println(F("Connect to socket server fail!"));
        return;
    }
 
    if (client.connected())
    {
        Serial.println("Connected");
        client.send("connection", "message", "Connected !!!!");
    }
//  if (client.connected())
//  {
//    Serial.println("connection successful");
//    delay(1000);
//    client.send("device", "deviceName", "JT_Thanos");
//  }
}


void loop()
{
  while (Serial.available())
  {
        char inChar = (char)Serial.read();

        if (inChar > 47 && inChar < 58)
        {
          if (i == 0)
              x = inChar; //x = inChar - 48;
          if (i == 1)
              y = inChar; //y = inChar - 48;
          if (i == 2)
          {
              client.send("espshot", "pos", (String)inChar);
              i = 0;
          }
        }
        i++;
  }

  unsigned long currentMillis = millis();
  if (millis() - previousMillis > interval)
  {
      previousMillis = millis();

//    client.send("controlDevice", "control", (String)'_');
  }
}   
