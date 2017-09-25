#include <Wire.h>
#include <SoftwareSerial.h>
#include "rgb_lcd.h"

#define BLUETOOTH_SPEED 9600

#define segA 2
#define segB 3
#define segC 4
#define segD 5
#define segE 6
#define segF 12
#define segG 8

SoftwareSerial BTSerial(10, 11); // RX | TX

rgb_lcd lcd;

const int BLUETOOTH = 9;

const String title = " Welcome To  ";
const String title2 = " Yogurt 4 All ";
const String message = "Hello! What would you like today?";
const String total = "Total:  RM ";
const String thankYouText1 = "Thank you!";
const String thankYouText2 = "Enjoy your drink!";
const String askPaymentText = "Pay with Paywave";
const String askPaymentText2 = "To Proceed";
const String paymentText = "Payment Accepted!";
const String dispenseText = "Dispensing your drink......";

int COUNT = 0;

void initiateLCD();
void reset();
void setCursorRow1(String message);
void setCursorRow2(String message);
void initiateBluetooth();
void bluetoothHelper();
void askForPayment();
void dispenseProduct();
void thankYou();
void buttonHelper();
void releaseKey();
void segDisplay();

void setup()
{
  Serial.begin(9600);

  pinMode(BLUETOOTH, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  
  initiateLCD();
  initiateBluetooth();
  
  delay(200);
}

void loop()
{
  bluetoothHelper();
//  buttonHelper();
  segDisplay();
  lcd.setCursor(11, 1);
  lcd.print(COUNT*3);
}

void initiateLCD() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  reset();
}

void reset() {
  lcd.clear();
  lcd.setRGB(0, 0, 150);
  setCursorRow1(title);
  setCursorRow2(title2);
  
  lcd.blinkLED();
  delay(4000);
  lcd.noBlinkLED();

  lcd.setRGB(255, 255, 255);

  setCursorRow1(message);
  setCursorRow2("                ");
  delay(1500);

  for (int i = 0; i < message.length()-14; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  delay(1000);

  lcd.clear();

  setCursorRow1("Select a drink");
  lcd.setCursor(0, 1);
  lcd.print(total);
  lcd.setCursor(11, 1);
  lcd.print(COUNT);
}

void setCursorRow1(String message) {
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void setCursorRow2(String message) {
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void initiateBluetooth() {
  digitalWrite(BLUETOOTH, HIGH);
  Serial.println("Enter AT commands:");
  BTSerial.begin(BLUETOOTH_SPEED);
}

void bluetoothHelper() {
  if (BTSerial.available() || Serial.available()) {
    byte r = BTSerial.read();
    byte s = Serial.read();
    BTSerial.flush();
    Serial.println(r);
    Serial.println(s);
    
    if (r == 51) {
      dispenseProduct();
    } else if (r == 65 || s == 65) {
      
    } else if (r == 68 || s == 68) {
      COUNT++;
    } else if (r == 69 || s == 69) {
      COUNT--;
    } else if (r == 70 || s == 70) {
      askForPayment();
    } else if (r == 71 || s == 71) {
      COUNT = 0;
      reset();
    }
  }

//  if (Serial.available()) {
//    BTSerial.write(Serial.read());
//    delay(300);
//  }
}

void askForPayment() {
  lcd.clear();
  lcd.setRGB(0, 150, 0);
  setCursorRow1(askPaymentText);
  lcd.setCursor(0, 1);
  lcd.print(total);
  lcd.setCursor(11, 1);
  lcd.print(COUNT*3);
}

void dispenseProduct() { //planned to build a real motor to dispense drink, but whatever
  lcd.clear();
  COUNT = 0;
  setCursorRow1(paymentText);
  setCursorRow2(dispenseText);
  delay(2000);
  
  for (int i = 0; i < dispenseText.length()-3; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  
  delay(2000);
  thankYou();
}

void thankYou() {
  lcd.clear();
  lcd.blinkLED();
  setCursorRow1(thankYouText1);
  setCursorRow2(thankYouText2);
  delay(5000);
  lcd.noBlinkLED();
  
  reset();
}

//void buttonHelper() {
//  
//  if (digitalRead(BUTTON) == HIGH) {
//    Serial.println('A');
//  }
//  
//  delay(100);
//}

void releaseKey() {
  Serial.println('Z');
}

void segDisplay() {
  switch(COUNT) {
    case 0:// when count value is 0 show”0” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;
      
    case 1:// when count value is 1 show”1” on disp
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 2:// when count value is 2 show”2” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 3:// when count value is 3 show”3” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 4:// when count value is 4 show”4” on disp
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 5:// when count value is 5 show”5” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 6:// when count value is 6 show”6” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 7:// when count value is 7 show”7” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 8:// when count value is 8 show”8” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 9:// when count value is 9 show”9” on disp
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
      
    default:
     break;
  }

}


