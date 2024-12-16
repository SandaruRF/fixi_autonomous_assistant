#include <IRremote.h>
#include <Servo.h>
////////////////////////////////////////
int touchValPrev = 0;
int state = 0;
int redskrew;
int spanner;
int yellowskrew;
int touchPin=7;

int stateDet(){
  int touchVal = digitalRead(touchPin);
  if (touchValPrev == 0 && touchVal == 1 && state == 1){
    state = 0;
  }else if (touchValPrev == 0 && touchVal == 1 && state == 0){
    state = 1;
  }
  touchValPrev = touchVal;
  //Serial.println(state);
  delay(100);
  return state;
}

int object_num;
int touchSensorLoopCondition=0;

int servoPinD = 6; 
Servo ServoD;
int DbeginingPositon=30; 
int gripperOpenAngle=0;
int DservoPos;
void gripperGive(){
      DservoPos=DbeginingPositon; // 30
      if(DbeginingPositon<gripperOpenAngle){//30<0
        for(int count=DbeginingPositon; count<gripperOpenAngle; count ++){
            DservoPos++;
            ServoD.write(DservoPos); 
            delay(35);
        } 
      }else{
        for(int count=DbeginingPositon; count>gripperOpenAngle; count --){//30 to 0
            DservoPos--;
            ServoD.write(DservoPos); 
            delay(35);
        } 
      }
     
  
  }
  void gripperClose(){       

      DservoPos=gripperOpenAngle;// 
      
      if(gripperOpenAngle<DbeginingPositon){//0<30
      
          for(int count=gripperOpenAngle; count<DbeginingPositon; count ++){//0 to 30
            DservoPos++;
            ServoD.write(DservoPos);
            delay(60);

            }
      }else{
          for(int count=gripperOpenAngle; count>DbeginingPositon; count --){
            DservoPos--;         
            ServoD.write(DservoPos); 
            delay(60);

        }}


          
        }
/////////////////////////////////////
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  ////////////////
  Serial.begin(115200);
    ServoD.attach(servoPinD); 
  ServoD.write(DbeginingPositon);
  ///////////////////
  irrecv.enableIRIn();
  irrecv.blink13(true);

  ///////////////////////////////
  
   while(!Serial){};
   ////////////////////////////
   
}

void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("CH-");
          break;
          case 0xFF629D:
          Serial.println("CH");
          break;
          case 0xFFE21D:
          Serial.println("CH+");
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          break;
          case 0xFF02FD:
          Serial.println(">>|");
          break ;  
          case 0xFFC23D:
          Serial.println(">|");
          break ;               
          case 0xFFE01F:
          Serial.println("-");
          break ;  
          case 0xFFA857:
          Serial.println("+");
          break ;  
          case 0xFF906F:
          Serial.println("EQ");
          break ;  
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("100+");

          //////////////////////////////
          gripperGive();
          state=1;
          redskrew=0;
          spanner=0;
          yellowskrew=0;
          while (state == 1){
             Serial.println("Start");
          stateDet();
          if(Serial.available()>0){
          String message=Serial.readStringUntil('\n');  //(142, 159)redskrew (0.95)
          
          
          int startX = message.indexOf('(') + 1;
          int endX = message.indexOf(',');
          int startY = endX + 2;
          int endY = message.indexOf(')');
          int startTool = endY + 1;
          int endTool = message.indexOf(' ', startTool);
          int startProb = endTool + 2;
          int endProb = message.indexOf(')', startProb);
           String X = message.substring(startX, endX);
          String Y = message.substring(startY, endY);
          String Tool = message.substring(startTool, endTool);
          String Prob = message.substring(startProb, endProb);

          ////////////////////////////////////////////////////


          if(Tool=="redskrew"){
            redskrew++;
          }else if(Tool=="spanner"){
            spanner++;
          }else if(Tool=="yellowskrew"){
            yellowskrew++;
          }

   
          

          ////////////////////////////////////////////////////
      
          int intX = X.toInt();
          int intY = Y.toInt();

          int errorY = intY -120;
          int errorX = intX -180;
          }
//          Serial.print("redskrew : ");
//          Serial.println(redskrew);
//          Serial.print("spanner : ");
//          Serial.println(spanner);
//          Serial.print("yellowskrew : ");
//          Serial.println(yellowskrew);
        }
        
        if(redskrew>=spanner && redskrew>=yellowskrew){
            object_num=3;
          }else if(spanner>=redskrew && spanner>=yellowskrew){
            object_num=1;
          }else {
            object_num=2;
          }
          delay(10);

          Serial.println(object_num);
          delay(10);
          Serial.println("Stop");
          delay(10);
          Serial.println(object_num);

          gripperClose();
          /////////////////////////////
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          break ;
          case 0xFF30CF:
          Serial.println("1");
          break ;
          case 0xFF18E7:
          Serial.println("2");
          break ;
          case 0xFF7A85:
          Serial.println("3");
          break ;
          case 0xFF10EF:
          Serial.println("4");
          break ;
          case 0xFF38C7:
          Serial.println("5");
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;   
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
