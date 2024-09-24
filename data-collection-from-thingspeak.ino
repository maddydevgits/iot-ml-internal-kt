#include <WiFi.h>
#include <ThingSpeak.h>

const int channelid=2669076;
const char* apikey="KCSJL3214HY1B5EK";

const char* ssid="The WIFI";
const char* password="123madhu";

WiFiClient client;

int sensor=35;
int threshold=2800; // getThresholdFromCloudAsPerTheUser()

String state;
String action;

void setup() {
  pinMode(sensor,INPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  delay(200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");
  ThingSpeak.begin(client);
}

void loop() {
  int m=analogRead(sensor);
   if(m>threshold) // 4095>2800 - dry
    state="dry";
  else
    state="wet";
  if (state=="dry")
    action="motor on";
  else if(state=="wet")
    action="motor off";

  Serial.print("#"); // # - SOF
  Serial.print(","); // , - Seperator
  Serial.print(m); // value1
  Serial.print(","); // , - Seperator
  Serial.print(state); // value2
  Serial.print(","); // , - Seperator
  Serial.print(action); // value3
  Serial.print(",");
  Serial.println("~"); // ~ - EOF

  ThingSpeak.setField(1,m);
  ThingSpeak.setField(2,state);
  ThingSpeak.setField(3,action);
  int code=ThingSpeak.writeFields(channelid,apikey);
  if(code==200)
    Serial.println("Data Uploaded");
  delay(10000);
}
