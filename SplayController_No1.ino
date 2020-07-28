#include <Servo.h>
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  //シリアル通信
  Serial.begin(9600);

  // サーボ用に9pinをPWM出力
  myservo.attach(9);
  
  // 0度にする
  myservo.write(0);  
}

float Vcc = 5.0;  //電源電圧
float distance_1;
float distance_2;
const int ANALOG = 5;//センサ信号入力

bool sensorCheck(){
  // put your main code here, to run repeatedly:

  // センサの出力地を距離に変換
  distance_1 = Vcc*analogRead(ANALOG)/1023;
  distance_2 = 26.549*pow(distance_1,-1.2091);
  //Serial.println(distance_2); 

  // 20cmより近づいたら ON
  if(distance_2 < 20){
    //Serial.println("true"); 
    return true ;
  }else{
    //Serial.println("false"); 
    return false;
  }
}

bool oneShot = false;
int count = 0;              // サーボ制御用のカウンター
const int trigger_on  = 20; // トリガーONをにするカウント値
const int trigger_off = 10; // トリガーOFFをにするカウント値

void loop() {
  // put your main code here, to run repeatedly:

  // センサーチェック
  if( count == 0 && sensorCheck() ){
    if( oneShot == false ){
      oneShot = true ;
      Serial.println("oneShot"); 
      count = trigger_on ;
    }
  }else if(sensorCheck() == false){
    oneShot = false ;
  }

  // カウンターの値によりサーボを駆動
  if(count == trigger_on){        // トリガーON
    myservo.write(150);
  }
  else if(count == trigger_off){  // トリガーOFF
    myservo.write(0);
  }

  // カウントダウン
  if( 0 < count && count <= trigger_on)
    count --;

  // 100ms停止
  delay(100);
}
