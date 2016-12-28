// LCD libs
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 

// Inputs
int fart_sensor = A1; 
// Outputs
int yellow_led = 2; 
int green_led = 3; 
int red_led = 4; 
int buzzer = 5; 
// Aux
int value = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(fart_sensor, INPUT);
  pinMode(yellow_led, OUTPUT); 
  pinMode(green_led, OUTPUT); 
  pinMode(red_led, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
  
  lcd.init(); 
  lcd.backlight(); 
  lcd.print("0"); 
}

void level_ok() {
  digitalWrite(green_led, HIGH); 
  digitalWrite(yellow_led, LOW);
  digitalWrite(red_led, LOW); 
  noTone(buzzer); 
}
void level_not_ok() {
  digitalWrite(green_led, LOW); 
  digitalWrite(yellow_led, HIGH); 
  digitalWrite(red_led, LOW); 
  noTone(buzzer); 
}
void level_danger() {
  digitalWrite(green_led, LOW); 
  digitalWrite(yellow_led, LOW); 
  digitalWrite(red_led, HIGH); 
  noTone(buzzer); 
}
void level_real_danger() {
  digitalWrite(green_led, LOW); 
  digitalWrite(yellow_led, LOW); 
  digitalWrite(red_led, HIGH); 
  tone(buzzer, 1000); 
}
void level_mortal() {
  digitalWrite(green_led, LOW); 
  digitalWrite(yellow_led, LOW); 
  digitalWrite(red_led, HIGH); 
  tone(buzzer, 2000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(fart_sensor); 
  Serial.println("Value: " + String(value)); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(value));
  lcd.setCursor(0,1); 
  if (value < 500) {
    lcd.print("Fresh air :)");
    level_ok();
  } else if (value < 550) {
    lcd.print("Somehow normal"); 
    level_ok();
  } else if (value < 600){
    lcd.print("Something fishy?"); 
    level_not_ok();
  } else if (value < 650) {
    lcd.print("That's gross"); 
    level_not_ok();
  } else if (value < 700) {
    lcd.print("Dead inside");
    level_danger(); 
  } else if (value < 750) {
    lcd.print("Ninja murder"); 
    level_real_danger();  
  } else if (value < 800) {
    lcd.print("Auschwitz"); 
    level_mortal(); 
  } else {
    lcd.print("Nuclear launch"); 
    level_mortal(); 
  }
  delay(500); 
}
