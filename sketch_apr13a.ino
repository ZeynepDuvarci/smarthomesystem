#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h>
Password password = Password( "1234" );  // ŞİFRE BELİRLEME...
const int yesilled=45;    // YEŞİL LED PİN ADLANDIRMA...
const int kirmiziled=46;  // KIRMIZI LED PİN ADLANDIRMA...

const byte satir = 4;   
const byte sutun = 3;

char tus_takimi[satir][sutun] = {   
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte satirPin[satir] = { 53,52,51,50 }; // SATIR PİNLERİ TANIMLAMA...
byte sutunPin[sutun] = { 49,48,47,};    // SUTUN PİNLERİ TANIMLAMA...


Keypad keypad = Keypad( makeKeymap(tus_takimi), satirPin, sutunPin, satir, sutun );  // KEYPAD HARİTA OLUŞTURMA...       
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd2(44, 43, 42, 41, 40, 39);

#define FlamePin A1
#define buzzer 1
LiquidCrystal lcd1(rs, en, d4, d5, d6, d7);
float temp;         
#define INTERNAL 2

int sensor1=8;//sensor
int sensor2=3;//tetik
boolean sensorValue=0;

void setup() {
  Serial.begin(9600);
  pinMode(yesilled,OUTPUT);
  pinMode(kirmiziled,OUTPUT);
  keypad.addEventListener(keypadEvent); 
  Serial.print("4 Haneli Şifrenizi Giriniz\nŞifreyi Onaylamak İçin Yıldız '*' Tuşuna Basın\n");
   lcd2.begin(16, 2);
   pinMode(FlamePin, INPUT_PULLUP);
   pinMode(buzzer, OUTPUT);
    lcd2.setCursor(5, 0);
    lcd2.print("FLAME");
    lcd2.setCursor(3, 1);
    lcd2.print("DETECTOR");
    delay(1000);
    lcd2.clear();
  Serial.begin(9600);
  
  analogReference(INTERNAL);
  lcd1.begin (16,2);                                   
  lcd1.setCursor(0, 0);
  lcd1.clear();   

  
  
  pinMode(sensor1,INPUT);
  pinMode(sensor2,OUTPUT);
  delay(10);                                       
}


void loop() {
  keypad.getKey();
int Flame = digitalRead(FlamePin);

if(Flame==HIGH)
{
  digitalWrite(buzzer, HIGH);
  lcd2.setCursor(5, 0);
  lcd2.print("FLAME");
   lcd2.setCursor(3, 1);
  lcd2.print("DETECTED");
  delay(200);
  lcd2.clear();
  delay(200);
  
}
else
{
 digitalWrite(buzzer, LOW); 
}
  sensorValue=digitalRead(sensor1);
  
  if(sensorValue==1)
  {
    digitalWrite(sensor2,HIGH);
  }
  else
  {
    digitalWrite(sensor2,LOW);
  }

  
  temp = analogRead(A0);                                                   
  temp=temp*1100/(1024*10);
  lcd1.print("sicaklik : ");
  temp=(int)temp;
  lcd1.print(temp);
  delay(100);
  
  
  if(temp<20)
  {
      lcd1.setCursor(0, 1);
      lcd1.print("sicaklik dusuk");
      delay(100);
  }
  else if(temp>30)
  {
      lcd1.setCursor(0, 1);
      lcd1.print("sicaklik yuksek");
      delay(100);
  }
  lcd1.clear();  

  
  
}
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState())
     {
    case PRESSED:
  Serial.print("*");
  switch (eKey){
    case '*': checkPassword();  break;  // PAROLA KONTROLÜ...  
    case '#': password.reset(); break;  // PAROLA RESET...
    default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("\nBaşarılı\n");
    Serial.print("4 Haneli Şifrenizi Giriniz\nŞifreyi Onaylamak İçin Yıldız '*' Tuşuna Basın\n");
    digitalWrite(yesilled,HIGH);
    digitalWrite(kirmiziled,LOW);
                          }
  else
  {
    Serial.println("\nYanlış Şifre Girdiniz\n");
    Serial.print("4 Haneli Şifrenizi Giriniz\nŞifreyi Onaylamak İçin Yıldız '*' Tuşuna Basın\n");
    digitalWrite(kirmiziled,HIGH);
    digitalWrite(yesilled,LOW);
  }
}
