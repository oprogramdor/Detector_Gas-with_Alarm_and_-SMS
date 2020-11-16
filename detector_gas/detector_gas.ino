#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(9, 10);
unsigned long timerSetup = millis();
unsigned long timerSom = millis();

void setup() {
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(6, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Voce esta");
  delay(1000); 
  lcd.setCursor(3,1);
  lcd.print(" usando:");
  delay(500);
  lcd.clear();
  
  lcd.setCursor(2,0);
  lcd.print(" Sensor de");
  delay(1000);
  lcd.setCursor(5,1);
  lcd.print(" Gas");
  delay(500);
  lcd.clear();
  
  lcd.setCursor(3,0);
  lcd.print("Feito por:");
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print(" Wallace");
  lcd.setCursor(3,1);
  lcd.print(" Willian");
  delay(1000);
  lcd.setCursor(3,0);
  lcd.print(" Nicolly");
  lcd.setCursor(3,1);
  lcd.print(" Lorenna");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print(" Kaua");
  lcd.setCursor(4,1);
  lcd.print(" Costa");
  delay(1000);
  lcd.setCursor(3,0);
  lcd.print(" Nicolly");
  lcd.setCursor(3,1);
  lcd.print(" Nogueira");
  delay(1000);
  lcd.clear();
}

void loop() {
  int c_fumaca = analogRead(A1);
  c_fumaca = map(c_fumaca, 0, 1023, 0, 100);
  if(c_fumaca < 40) {
    verdeON();
    lcd.setCursor(0,0);
    if((millis() - timerSetup) <= 1300) {
      lcd.clear();
      lcdQualidade();
    }else if((millis() - timerSetup) > 1300 && (millis() - timerSetup) <= 2600) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("      BOM!");
    }else {
      timerSetup = millis();
    }
  }else if(c_fumaca >= 40 && c_fumaca < 60) {   
    amareloON();
    //
    for(int i = 0; i < 2; i++) {
    if((millis() - timerSom) <= 500) {
        tone(6, 700, 500);
      }else if((millis() - timerSom) > 500 && (millis() - timerSom) < 5000){
        noTone(6);
      }else {
        timerSom = millis();
      }
    }
    //
    if((millis() - timerSetup) <= 1300) {
      lcdConcentracao();      
    }else if((millis() - timerSetup) > 1300 && (millis() - timerSetup) <=  2600) { 
      lcd.clear();
      lcdFumaca();
    }else if((millis() - timerSetup) > 2600 && (millis() - timerSetup) <= 3900) {
      lcd.clear();
      lcdQualidade();
    }else if((millis() - timerSetup) > 3900 && (millis() - timerSetup) <= 5200) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    REGULAR!    ");
      SendTextMessage();
      lcd.setCursor(1,1);
      lcd.print("Alerta de Gas!");
      delay(500);
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("SMS enviado!");
      delay(500);
      lcd.clear();
    } else {
      timerSetup = millis();
    }
  }else {
    vermelhoON();

    for(int i = 0; i < 2; i++) {
      if((millis() - timerSom) <= 1500) {
        tone(6, 1290, 500);
      }else if((millis() - timerSom) > 1500 && (millis() - timerSom) <= 3500) {
        noTone(6);
      }else {
        timerSom = millis();
      }
    }
    
    if ((millis() - timerSetup) <= 1300) {
      lcd.clear();
      lcdConcentracao();
    }else if((millis() - timerSetup) > 1300 && (millis() - timerSetup) <= 2600) {
      lcd.clear();
      lcdFumaca();
    }else if((millis() - timerSetup) > 2600 && (millis() - timerSetup) <= 3900) {
      lcd.clear();
      lcdQualidade();
    }else if((millis() - timerSetup) > 3900 && (millis() - timerSetup) <= 5200) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PESSIMA!    ");
      SendTextMessage();
      lcd.setCursor(1,1);
      lcd.print("Alerta de Gas!");
      delay(500);
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("SMS enviado!");
      delay(500);
      lcd.clear();
    }else {
      timerSetup = millis();
    }
  }
}

void verdeON() {
  analogWrite(4, 255);
  analogWrite(3, 500);
  analogWrite(2, 0);
  delay(200);
}
void amareloON() {
  analogWrite(4, 255);
  analogWrite(3, 100);
  analogWrite(2, 0);
  delay(180);
}
void vermelhoON() {
  analogWrite(4, 255);
  analogWrite(3, 0);
  analogWrite(2, 300);
  delay(180);
}
void lcdFumaca() {
  int c_fumaca = analogRead(A1);
  c_fumaca = map(c_fumaca, 0, 1023, 0, 100);
  lcd.setCursor(0,0);
  lcd.print("       ");
  lcd.print(c_fumaca);
  lcd.print("%");
}
void lcdConcentracao() {
  lcd.setCursor(0,0);
  lcd.print("Concentracao De ");
  lcd.setCursor(0,1);
  lcd.print(" Fumaca ou Gas  ");
}
void lcdQualidade() {
  lcd.setCursor(0,0);
  lcd.print("   Qualidade");
  lcd.setCursor(0,1);
  lcd.print("     Do Ar  ");
}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+5521965492013\"\r");  // change to the phone number you using
  delay(1000);
  mySerial.println("Gas Leaking!");    //the content of the message
  delay(200);
  mySerial.println((char)26);    //the stopping character
  delay(1000);
 
}
