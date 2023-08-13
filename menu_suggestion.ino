#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <RTClib.h> // RTC 라이브러리 추가

SoftwareSerial bluetoothSerial(2, 3);

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc; // RTC 객체 생성

String beverages[] = {"Americano", "Cafe Latte", "Vanilla Latte", "Milk Tea Latte", "Grapefruit Ade", "Citron Ade", "YujuPeachGreenTea", "Chamomile Medley", "English BlackFirst", "Pistachio Latte", "PassionFruit&Peach"};
String desserts[] = {"Cookie", "Carrot Cake", "Bagel"};
int drinkPrices[] = {4000, 4500, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5500, 5700};
int dessertPrices[] = {3800, 5500, 5500};

// String menu[] = {"drink", "dessert"}
// String category[] = {"mbti", "age", "animal", "random"}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Welcome!");

  // Serial 통신 초기화
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  // RTC 초기화
  rtc.begin();

  // RTC가 초기화되지 않은 경우 현재 날짜 및 시간 설정
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // 컴파일한 날짜와 시간으로 설정
  }
}

void loop() {
  // 사용자 입력 받기

  while (!bluetoothSerial.available()) {}
  char firstData = bluetoothSerial.read();
  Serial.print("Received: ");
  Serial.println(firstData);

  while (!bluetoothSerial.available()) {}
  char secondData = bluetoothSerial.read();
  Serial.print("Received: ");
  Serial.println(secondData);

  while (!bluetoothSerial.available()) {}
  char thirdData = bluetoothSerial.read();
  Serial.print("Received: ");
  Serial.println(thirdData);

  String totalData = String(firstData) + String(secondData) + String(thirdData);
  Serial.print("totalData: ");
  Serial.println(totalData);

  // 날짜 정보 가져오기
  DateTime now = rtc.now();

  // totalData와 날짜 정보를 합쳐서 랜덤 시드값으로 사용
  unsigned long seedValue = totalData.toInt() + millis();
  randomSeed(seedValue);

  // 랜덤으로 음료와 디저트 선택
  int beverageChoice = random(sizeof(beverages) / sizeof(beverages[0]));
  int dessertChoice = random(sizeof(desserts) / sizeof(desserts[0]));

  lcd.clear();
  if (firstData == 'a') {
    lcd.print(beverages[beverageChoice]);
    lcd.setCursor(0, 1);
    lcd.print("Price: " + String(drinkPrices[beverageChoice]) + " KRW");
  } else {
    lcd.print(desserts[dessertChoice]);
    lcd.setCursor(0, 1);
    lcd.print("Price: " + String(dessertPrices[dessertChoice]) + " KRW");
  }

  // // 사용자가 "yes" 입력할 때까지 대기
  // while (true) {
  //   if (Serial.available()) {
  //     String input = Serial.readStringUntil('\n');
  //     input.toLowerCase();
  //     if (input == "yes") {
  //       break;
  //     }
  //   }
  // }

  // 잠시 기다림
  delay(1000); // 조정 가능한 딜레이
}
