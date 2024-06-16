void setup() {
 Serial.begin(115200);
 while(!Serial){};
}

void loop() {
  if(Serial.available()>0){
    String message=Serial.readStringUntil('\n');
    
    int startIdx = message.indexOf('(');
    int endIdx = message.indexOf(')');
    int commaIdx = message.indexOf(',');

    String num1Str = message.substring(startIdx + 1, commaIdx);
    String num2Str = message.substring(commaIdx + 2, endIdx);

    int num1 = num1Str.toInt();
    int num2 = num2Str.toInt();
    
    Serial.print("x = ");
    Serial.print(num1);
    Serial.print(", y = ");
    Serial.println(num2);
    }
}
