#define BLYNK_TEMPLATE_ID "TMPL3qSB0CfS9"
#define BLYNK_TEMPLATE_NAME "New Template"
#define BLYNK_AUTH_TOKEN "BeH6_BrWxqiz3tf63LopuaoCsy_syBMh"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "Galaxyz";     
char pass[] = "anand2347"; 

#define MQ5_PIN 32  

LiquidCrystal_I2C lcd(0x27, 16, 2); 
BlynkTimer timer;

int baseline = 3000;     
int threshold = 300;     

void readGasSensor() {
  int gasValue = analogRead(MQ5_PIN);
  String status;

  if (gasValue > baseline + threshold) {
    status = "Spoiled?";
  } else {
    status = "Fresh";
  }

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.print(status);

  
  Serial.print("Gas Value: ");
  Serial.print(gasValue);
  Serial.print(" | Status: ");
  Serial.println(status);

  
  Blynk.virtualWrite(V3, gasValue);
  Blynk.virtualWrite(V1, status);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  delay(1000);
  lcd.clear();
  lcd.print("Connecting Blynk");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  lcd.print("System Ready");

  
  timer.setInterval(2000L, readGasSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}