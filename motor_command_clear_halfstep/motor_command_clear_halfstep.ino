/*
R-Teta Tarayıcı Komut Kontrollü
Mesut KILIÇ
01.11.2017
Motor1 Teta
cw --> geri
ccw --> ileri
Motor2 R
*/

#define MOTORTEST 0

//Motor Pinleri             A     B     C    D
uint8_t motorpins[3][4]={ {0,    0,    0,    0   },
                          {PA_6, PA_5, PB_4, PE_5}, 
                          {PE_4, PB_1, PB_0, PA_7} };

int motor_hiz=4000;

uint8_t buton_A=PD_7;
uint8_t buton_B=PD_6;
uint8_t buton_C=PC_6;
uint8_t buton_D=PC_7;

char seri_gelen[10];
int incomingByte = 0;
int byte_count=0;

int buttonPin = PUSH2;
int ledPin=GREEN_LED;
int ledPin1=RED_LED;

//int motor_hiz[3]={0,2000,2000}
void setup()
{
  for(int i=0; i<4; ++i){
    pinMode(motorpins[1][i],OUTPUT);
  }
  for(int i=0; i<4; ++i){
    pinMode(motorpins[2][i],OUTPUT);
  }
  pinMode(buton_A, INPUT_PULLUP);
  pinMode(buton_B, INPUT_PULLUP);
  pinMode(buton_C, INPUT_PULLUP);
  pinMode(buton_D, INPUT_PULLUP);
  
  pinMode(ledPin,OUTPUT);
  pinMode(ledPin1,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  delay(100);
  goHome();
  
  //Serial.println("System initialize complete");
  
  attachInterrupt(buttonPin,e_stop,FALLING);
  
}

void loop()
{
  while(MOTORTEST)
    motor_test();
    
  digitalWrite(ledPin,HIGH);
  while(Serial.available()){
    digitalWrite(ledPin,LOW);
    //delay(1);
    // read the incoming byte:
    incomingByte = Serial.read();
    if(incomingByte!='\n' && byte_count<10){
      seri_gelen[byte_count]=char(incomingByte);
      ++byte_count; 
    }else{
      switch(seri_gelen[0]){
        case 'w': if(digitalRead(buton_B)){
                  //Serial.println("Ileri");
                  motor_ileri(2,motor_hiz);}
                  byte_count=0; break;
        case 's': if(digitalRead(buton_A)){
                  //Serial.println("Geri");
                  motor_geri(2,motor_hiz);
                }
                  byte_count=0; break;
        case 'a': if(digitalRead(buton_C)){
                  //Serial.println("ccw");
                  motor_ileri(1,motor_hiz);}
                  byte_count=0; break;
        case 'd': if(digitalRead(buton_D)){
                  //Serial.println("cw");
                  motor_geri(1,motor_hiz);
                  //motor_geri(1,motor_hiz);
                  }
                  byte_count=0; break;
        
        case '0': /*Serial.println("Orjin");*/ byte_count=0; goHome(); break;
        case '1': /*Serial.println("Stop");*/ byte_count=0; break;
        case '2': /*Serial.println("Start");*/ byte_count=0; break;

        case 'm': //Serial.println("Motor Test"); 
                  while(!Serial.available())
                    motor_test();
                  byte_count=0; break;
                  
         case 'x': //Serial.println("Teta Home"); 
                  while(digitalRead(buton_C))
                    motor_ileri(1,motor_hiz);
                  while(!digitalRead(buton_C))
                    motor_geri(1,motor_hiz);
                  byte_count=0; break;
        
      }
      
    }
  }
  
  sifirla();
  
}

void e_stop(){
  sifirla();
  digitalWrite(ledPin,LOW);
  Serial.println("Emergency Stop");
  while(1){
    digitalWrite(ledPin1,HIGH);
    delay(200);
    digitalWrite(ledPin1,LOW);
    delay(200);
  }
  
}

void goHome(){
  //R
  while(digitalRead(buton_A))
    motor_geri(2,motor_hiz);
  while(!digitalRead(buton_A))
    motor_ileri(2,motor_hiz);
  
  //Teta
  while(digitalRead(buton_C))
    motor_ileri(1,motor_hiz);
  while(!digitalRead(buton_C))
    motor_geri(1,motor_hiz);
}


void motor_ileri(int motor_no, int hiz){
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
}

void motor_geri(int motor_no, int hiz){
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], HIGH);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], LOW);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], HIGH);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], LOW);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
  digitalWrite(motorpins[motor_no][0], HIGH);
  digitalWrite(motorpins[motor_no][1], LOW);
  digitalWrite(motorpins[motor_no][2], LOW);
  digitalWrite(motorpins[motor_no][3], HIGH);
  delayMicroseconds(hiz);
}

void sifirla(){
  digitalWrite(motorpins[1][0], LOW);
  digitalWrite(motorpins[1][1], LOW);
  digitalWrite(motorpins[1][2], LOW);
  digitalWrite(motorpins[1][3], LOW);
  
  digitalWrite(motorpins[2][0], LOW);
  digitalWrite(motorpins[2][1], LOW);
  digitalWrite(motorpins[2][2], LOW);
  digitalWrite(motorpins[2][3], LOW);
}

void motor_test()
{
  //Motor2 A ya gelene kadar geri B ye gelene kdar ileri
  while(digitalRead(buton_B)){
    motor_ileri(2,motor_hiz);
  }
  sifirla();
  delay(500);
  
  while(digitalRead(buton_A)){
    motor_geri(2,motor_hiz);
  }
  sifirla();
  delay(500);
  
  //Motor1 D ya gelene kadar geri C ye gelene kadar ileri
  while(digitalRead(buton_D)){
    motor_geri(1,motor_hiz);
  }
  sifirla();
  delay(500);
  
  while(digitalRead(buton_C)){
    motor_ileri(1,motor_hiz);
  }
  sifirla();
  delay(10);
  for(int i=0; i<10; ++i)
    motor_geri(1,motor_hiz);
  sifirla();
  delay(500);
  
}
