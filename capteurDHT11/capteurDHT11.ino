#include <Wire.h>

#include "DHT.h"
#include "rgb_lcd.h"

#define DHTPIN 12
#define DHTTYPE DHT11 

#define BUTTON 8

DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;

const int red = 255;
const int green = 255;
const int blue = 255;

int color = 0;
int state = 0;
int buttonState = 0;

unsigned long long previousMillis = 0;
const unsigned long long interval = 1000;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setRGB(red, green, blue);
  dht.begin();  
  lcd.print("Here we go !");

  pinMode(BUTTON, INPUT);
}

void loop() {
  unsigned long long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();

    Serial.print("Humidité : ");
    Serial.println(humidity);

    Serial.print("Temperature : ");
    Serial.println(temperature);

    Serial.println();

    lcd.clear();
    lcd.print("Humidite : ");
    lcd.print(humidity);
    lcd.print("%");
  
    lcd.setCursor(0,1);
  
    lcd.print("Temp : ");
    lcd.print(temperature);
    lcd.print(" C");
    
  }
  
  buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH) {
    state = 1;
  }

  if (buttonState == LOW && state == 1) {
    state = 0;
    if (color == 0) {
      lcd.setRGB(255, 0, 0);
      color = 1;
    }
  
    else if (color == 1) {
      lcd.setRGB(0, 255, 0);
      color = 2;
    }
  
    else if (color == 2) {
      lcd.setRGB(0, 0, 255);
      color = 3;
    }
  
    else {
      lcd.setRGB(255, 255, 255);
      color = 0;
    }
  }
}
