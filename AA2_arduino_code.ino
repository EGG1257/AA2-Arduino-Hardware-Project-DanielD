#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servoX;
Servo servoY;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int joyX = A0;
const int joyY = A1;

const int trigPin = 2;
const int echoPin = 3;

long duration;
float distance;

int xPos = 90;
int yPos = 90;

const int deadzone = 50;

void setup() {
  Serial.begin(9600);

  servoX.attach(9);
  servoY.attach(10);

  servoX.write(xPos);
  servoY.write(yPos);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ultrasonic Ready");
  delay(1000);
  lcd.clear();
}

void loop() {

  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  int xCenter = 512;
  int yCenter = 512;

  if (xValue > xCenter + deadzone) {
    xPos++;
  }
  else if (xValue < xCenter - deadzone) {
    xPos--;
  }

  if (yValue > yCenter + deadzone) {
    yPos++;
  }
  else if (yValue < yCenter - deadzone) {
    yPos--;
  }

  xPos = constrain(xPos, 0, 180);
  yPos = constrain(yPos, 0, 180);

  servoX.write(xPos);
  servoY.write(yPos);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm   "); 

  if(digitalRead(4) == HIGH){
    delay(1);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }else{
    delay(50);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
}
