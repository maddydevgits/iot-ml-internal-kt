#include <WiFi.h>
#include <HTTPClient.h>

int sensor=35;
int relay=2;

const char* ssid="The WIFI";
const char* password="";

const char* apiRoute="http://172.20.10.2:2000/predict?m=";

void setup() {
  pinMode(sensor,INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  delay(200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("WIFI Connected");
}

void loop() {
  int m=analogRead(sensor);
  int action=getDataFromAPI(m);
  Serial.println(action);
  if(action==1){
    Serial.println("Relay On");
    digitalWrite(relay,0);
  } else if(action==2){
    Serial.println("Relay Off");
    digitalWrite(relay,1);
  }
  delay(2000);
  
}

int getDataFromAPI(int a){
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    http.begin(apiRoute+String(a));
    int responseCode=http.GET();
    if(responseCode>0){
      String response=http.getString();
      Serial.println(response);
      http.end();
      if(response=="on"){
        return(1);
      } else if(response=="off"){
        return(2);
      } else {
        return(0);
      }
    }
  }
}
