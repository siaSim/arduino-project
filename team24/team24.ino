#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

LiquidCrystal_I2C lcd(0x27,16,2);

#define RST_PIN 9 //reset핀은 9번설정
#define SS_PIN 10 //SS핀은 10번설정
                  //SS핀은 데이터를 주고받는 역할의 핀 (SS = Slave Selcetor)

MFRC522 mfrc(SS_PIN, RST_PIN);  //MFR522를 이용하기 위해 mfrc객체를 생성함.


byte mycard[][4] = {
  {193, 50, 206, 36}, //1번
  {115, 106, 46, 46},  //2번
  {233 ,38 ,204 ,246},  //3번
  {4, 137, 2, 2},  //4번
  {37, 162, 94, 211},  //5번
  {199, 130, 187, 136 }    //6번
};

String text[] = {
  "Original card",
  "Original card2",
  "SIA  credit card",
  "Hero Samsung Pay",
  "Hero credit card",
  "SIA student card"
};

int LED_B = 3;
int LED_Y = 4;
int buzzer = 6;

void setup(){
  Serial.begin(9600); //시리얼 통신, 속도는 9600
  SPI.begin();  // SPI 초기화
                // SPI: 하나의 마스터와 다수의 Slave통신방식.
  mfrc.PCD_Init();

  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("Start!!"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print("Who's card?"); //이걸 출력
  lcd.setCursor(0,2); //LCD 3번째 줄에
  lcd.print("Card please~"); //이걸 출력
  
 pinMode(LED_Y, OUTPUT);
 pinMode(LED_B, OUTPUT);
 pinMode(buzzer, OUTPUT);
}

void loop(){
  if( !mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()){
    // 태그 접촉이 되지 않았을때 또는 ID가 읽히지 않았을때.
    delay(500); // 0.5초 딜레이
    return;
  }

  if(mfrc.uid.uidByte[0] == 193 && mfrc.uid.uidByte[1]==50           // 1번
        && mfrc.uid.uidByte[2] == 206 && mfrc.uid.uidByte[3] == 36){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Original card"); //시리얼 모니터에 출력
    Serial.print("Card UID:");

    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
    
    }
    
   else if(mfrc.uid.uidByte[0] == 115 && mfrc.uid.uidByte[1]==106   // 2번 태그  
        && mfrc.uid.uidByte[2] == 46 && mfrc.uid.uidByte[3] == 46){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Original card2"); //시리얼 모니터에 "hellow~~~"출력
    
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }


    else if(mfrc.uid.uidByte[0] == 233 && mfrc.uid.uidByte[1]==38   // 3번 태그  
         && mfrc.uid.uidByte[2] == 204 && mfrc.uid.uidByte[3] == 246){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("SIA  credit card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }

    else if(mfrc.uid.uidByte[0] == 4 && mfrc.uid.uidByte[1]==137     // 4번 태그  
        && mfrc.uid.uidByte[2] == 2 && mfrc.uid.uidByte[3] == 2){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Hero Samsung Pay"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }


    else if(mfrc.uid.uidByte[0] == 37 && mfrc.uid.uidByte[1]==162     // 5번 태그  
    && mfrc.uid.uidByte[2] == 94 && mfrc.uid.uidByte[3] == 211){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Hero credit card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }
        
        
        
    else if(mfrc.uid.uidByte[0] == 199 && mfrc.uid.uidByte[1]==130     // 6번 태그  
    && mfrc.uid.uidByte[2] == 187 && mfrc.uid.uidByte[3] == 136){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("SIA  student card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }
    
    else{
      digitalWrite(LED_Y, HIGH);
      digitalWrite(LED_B, LOW);
      Serial.println("Check card?");
      lcd.setCursor(0,0); //LCD 1번째 줄에
      lcd.print("This is not a"); //제목을 출력
      lcd.setCursor(0,1); //LCD 2번째 줄에
      lcd.print("Registered card"); //이걸 출력
      lcd.setCursor(0,2); //LCD 3번째 줄에
      lcd.print("Register Card please!"); //이걸 출력
      tone(6,523,100);
      delay(300);
      tone(6,523,100);
    }
}#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

LiquidCrystal_I2C lcd(0x27,16,2);

#define RST_PIN 9 //reset핀은 9번설정
#define SS_PIN 10 //SS핀은 10번설정
                  //SS핀은 데이터를 주고받는 역할의 핀 (SS = Slave Selcetor)

MFRC522 mfrc(SS_PIN, RST_PIN);  //MFR522를 이용하기 위해 mfrc객체를 생성함.


byte mycard[][4] = {
  {193, 50, 206, 36}, //1번
  {115, 106, 46, 46},  //2번
  {233 ,38 ,204 ,246},  //3번
  {4, 137, 2, 2},  //4번
  {37, 162, 94, 211},  //5번
  {199, 130, 187, 136 }    //6번
};

String text[] = {
  "Original card",
  "Original card2",
  "SIA  credit card",
  "Hero Samsung Pay",
  "Hero credit card",
  "SIA student card"
};

int LED_B = 3;
int LED_Y = 4;
int buzzer = 6;

void setup(){
  Serial.begin(9600); //시리얼 통신, 속도는 9600
  SPI.begin();  // SPI 초기화
                // SPI: 하나의 마스터와 다수의 Slave통신방식.
  mfrc.PCD_Init();

  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("Start!!"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print("Who's card?"); //이걸 출력
  lcd.setCursor(0,2); //LCD 3번째 줄에
  lcd.print("Card please~"); //이걸 출력
  
 pinMode(LED_Y, OUTPUT);
 pinMode(LED_B, OUTPUT);
 pinMode(buzzer, OUTPUT);
}

void loop(){
  if( !mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial()){
    // 태그 접촉이 되지 않았을때 또는 ID가 읽히지 않았을때.
    delay(500); // 0.5초 딜레이
    return;
  }

  if(mfrc.uid.uidByte[0] == 193 && mfrc.uid.uidByte[1]==50           // 1번
        && mfrc.uid.uidByte[2] == 206 && mfrc.uid.uidByte[3] == 36){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Original card"); //시리얼 모니터에 출력
    Serial.print("Card UID:");

    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
    
    }
    
   else if(mfrc.uid.uidByte[0] == 115 && mfrc.uid.uidByte[1]==106   // 2번 태그  
        && mfrc.uid.uidByte[2] == 46 && mfrc.uid.uidByte[3] == 46){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Original card2"); //시리얼 모니터에 "hellow~~~"출력
    
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }


    else if(mfrc.uid.uidByte[0] == 233 && mfrc.uid.uidByte[1]==38   // 3번 태그  
         && mfrc.uid.uidByte[2] == 204 && mfrc.uid.uidByte[3] == 246){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("SIA  credit card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }

    else if(mfrc.uid.uidByte[0] == 4 && mfrc.uid.uidByte[1]==137     // 4번 태그  
        && mfrc.uid.uidByte[2] == 2 && mfrc.uid.uidByte[3] == 2){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Hero Samsung Pay"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }


    else if(mfrc.uid.uidByte[0] == 37 && mfrc.uid.uidByte[1]==162     // 5번 태그  
    && mfrc.uid.uidByte[2] == 94 && mfrc.uid.uidByte[3] == 211){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("Hero credit card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }
        
        
        
    else if(mfrc.uid.uidByte[0] == 199 && mfrc.uid.uidByte[1]==130     // 6번 태그  
    && mfrc.uid.uidByte[2] == 187 && mfrc.uid.uidByte[3] == 136){
    digitalWrite(LED_B, HIGH);  // 3번핀에 연결된 LED켜지기
    digitalWrite(LED_Y, LOW);  // 3번핀에 연결된 LED켜지기
    Serial.println("SIA  student card"); //시리얼 모니터에 "hellow~~~"출력
    for (byte i = 0; i<4; i++)
    {
      Serial.print(mfrc.uid.uidByte[i]);

      Serial.print(" ");
    }
    Serial.println();
    for(int i = 0;i<6;i++){
    bool is_match = true;
    for(int j = 0;j<4;j++){
      if(mycard[i][j] != mfrc.uid.uidByte[j]){
        is_match = false;
        break;
      }
    }

    if(is_match){
      String line = text[i];
      while(line.length()<16) line+= " ";
      lcd.setCursor(0,2); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }
  }
    tone(6,523,100);
    delay(500);
        }
    
    else{
      digitalWrite(LED_Y, HIGH);
      digitalWrite(LED_B, LOW);
      Serial.println("Check card?");
      lcd.setCursor(0,0); //LCD 1번째 줄에
      lcd.print("This is not a"); //제목을 출력
      lcd.setCursor(0,1); //LCD 2번째 줄에
      lcd.print("Registered card"); //이걸 출력
      lcd.setCursor(0,2); //LCD 3번째 줄에
      lcd.print("Register Card please!"); //이걸 출력
      tone(6,523,100);
      delay(300);
      tone(6,523,100);
    }
}
