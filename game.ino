#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo1;
Servo servo2;
int joyX = 0;
int joyY = 1; 

const int redLED = 12;
const int greenLed = 13;

int servoVal;
unsigned long previousMillis = 0;
const long interval = 500;       

bool gameRunning = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

const unsigned long gameDuration = 30;  

const int centerMin = 480;
const int centerMax = 540;

bool prevJoystickMoved = false;

const unsigned long centerHoldTime = 300;

unsigned long joystickCenterStart = 0;

unsigned long gameEndTime = 0;

void setup() 
{
  lcd.init();        
  lcd.backlight();   
  lcd.clear();
  Serial.begin(9600);

  servo1.attach(5);   
  servo2.attach(6);

  pinMode(redLED, OUTPUT);
  pinMode(greenLed, OUTPUT);

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello (^__^)");
  lcd.setCursor(0, 1);
  lcd.print("Move Joystick!");
}

void loop()
{
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);

  bool joystickMoved = (xVal < centerMin || xVal > centerMax || yVal < centerMin || yVal > centerMax);


  if (joystickMoved && !prevJoystickMoved && !gameRunning && (millis() - gameEndTime > 2000))
  {

    gameRunning = true;
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLED, LOW);

    startTime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Started!");
    lcd.setCursor(0, 1);
    lcd.print("Good Luck!     "); 
  }

  if (gameRunning)
  {
   
    servoVal = analogRead(joyX);
    int servo1Pos = map(servoVal, 0, 1023, 180, 130);
    servo1.write(servo1Pos);

    servoVal = analogRead(joyY);
    int servo2Pos = map(servoVal, 0, 1023, 130, 180);
    servo2.write(servo2Pos);

    unsigned long currentMillis = millis();
    elapsedTime = (currentMillis - startTime) / 1000;

    if (currentMillis - previousMillis >= interval) 
    {
      previousMillis = currentMillis;

      Serial.print("Joystick X: ");
      Serial.print(xVal);
      Serial.print(" -> Servo1: ");
      Serial.println(servo1Pos);

      Serial.print("Joystick Y: ");
      Serial.print(yVal);
      Serial.print(" -> Servo2: ");
      Serial.println(servo2Pos);

      
      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(elapsedTime);
      lcd.print("s   "); 
    }

    
    if (elapsedTime >= gameDuration)
    {
      
      gameRunning = false;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLED, HIGH);

      gameEndTime = millis();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over!");
      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(gameDuration);
      lcd.print("s   ");
    }

    
    if (!joystickMoved && elapsedTime < gameDuration)
    {
      if (joystickCenterStart == 0) {
        
        joystickCenterStart = millis();
      } else if (millis() - joystickCenterStart >= centerHoldTime) {
       
        gameRunning = false;
        digitalWrite(greenLed, LOW);
        digitalWrite(redLED, HIGH);

        gameEndTime = millis();

        unsigned long finalTime = (millis() - startTime) / 1000;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Game Over!");
        lcd.setCursor(0, 1);
        lcd.print("Time: ");
        lcd.print(finalTime);
        lcd.print("s   ");
        joystickCenterStart = 0;
      }
    }
    else
    {
      
      joystickCenterStart = 0;
    }
  }
  prevJoystickMoved = joystickMoved;

  delay(50); 
}
