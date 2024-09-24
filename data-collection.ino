int sensor=35;
int threshold=2800; // giri's device

String state;
String action;

void setup() {
  pinMode(sensor,INPUT);
  Serial.begin(9600);
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
  delay(2000);
}
