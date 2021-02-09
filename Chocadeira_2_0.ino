#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //lib liquidCrystal I2C


#include "DHT.h"

byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};
 
#define DHTPIN A0 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
#define led A2
#define ledDanger 4 
#define vcc A1
#define gnd 13



#define up 5
#define menu 4
#define down 3
#define upAdrr 0
#define upFloatAdrr 1
#define downAdrr 2
#define downFloatAdrr 3

unsigned long tim = 0;

int option = 0;

bool flagUp,flagMenu,flagDown;

float  tempDown, tempUp;

float maxConfig, maxConfigFloat, minConfig, minConfigFloat;

DHT dht(DHTPIN, DHTTYPE);

  


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(up, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(A0, OUTPUT);

  pinMode(led, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vcc, HIGH);
  digitalWrite(gnd, LOW);
  dht.begin();

  digitalWrite(A0, HIGH);
  lcd.setCursor(0,0);
  lcd.print("CHOCADEIRA");
  lcd.setCursor(0,1);
  lcd.print("");
//  delay(2000);
  lcd.clear();

  lcd.createChar(0, grau);

// **********************************
//  EEPROM.write(upAdrr, 37);
//  EEPROM.write(upFloatAdrr, 5);
//  EEPROM.write(downAdrr, 35);
//  EEPROM.write(downFloatAdrr, 7);
// **********************************

tempDown = (EEPROM.read(downAdrr) *10) + EEPROM.read(downFloatAdrr) ;
tempUp = (EEPROM.read(upAdrr) *10) + EEPROM.read(upFloatAdrr);

maxConfig = EEPROM.read(upAdrr);
maxConfigFloat = EEPROM.read(upFloatAdrr);
minConfig = EEPROM.read(downAdrr);
minConfigFloat = EEPROM.read(downFloatAdrr);

tempDown = tempDown /10;
tempUp = tempUp / 10;
Serial.begin(9600);

lcd.setCursor(0,0);
lcd.print("CONFIGURADO COMO");
delay(2000);
lcd.clear();
lcd.setCursor(6,0);
lcd.print("MINIMA");
lcd.setCursor(7,1);
lcd.print((int) minConfig);
lcd.print(".");
lcd.print((int) minConfigFloat);
delay(3000);
lcd.setCursor(6,0);
lcd.print("MAXIMA");
lcd.setCursor(7,1);
lcd.print((int) maxConfig);
lcd.print(".");
lcd.print((int) maxConfigFloat);
delay(3000);
lcd.clear();
}

void loop() {

  float temperature = dht.readTemperature();
  if(!digitalRead(menu)) flagMenu = true;

  if(digitalRead(menu) && flagMenu){
      flagMenu = false;
      option ++;
      lcd.clear();
   }

   if(option > 2){
      option = 0;
    }

  switch(option){
     case 0: 
       if (isnan(temperature))  {
          Serial.println("Failed to read from DHT");
      } 
      else{
       lcd.setCursor(3,0);
       lcd.print("TEMPERATURA");
       lcd.setCursor(5,1);
       lcd.print(temperature);
       lcd.write((byte)0);
       lcd.print("C");
        
        
          if(temperature < tempDown){
              digitalWrite(led, HIGH);   
          }
          
          if(temperature > tempUp){
              digitalWrite(led ,  LOW);
          }
        }
     break;

     case 1: 
        lcd.setCursor(6,0);
        lcd.print("MINIMA");
        lcd.setCursor(7,1);
        lcd.print((int) minConfig);
        lcd.print(".");
        lcd.print((int) minConfigFloat);
        

        if(!digitalRead(down)) flagDown = true;

        if(digitalRead(down) && flagDown) {
          minConfigFloat --;
          flagDown = false; 
         }


         if(!digitalRead(up)) flagUp = true;

        if(digitalRead(up) && flagUp) {
          minConfigFloat ++;
          flagUp = false; 
         }

        if(minConfigFloat > 9){
            minConfigFloat = 0;
            minConfig ++;
         }
        if(minConfigFloat < 0){
          minConfigFloat = 9;
          minConfig --;
        }
        
        if(!digitalRead(menu)) flagMenu = true;
  
        if(digitalRead(menu) && flagMenu){
            flagMenu = false;
            option ++;
            lcd.clear();
            EEPROM.write(downAdrr, minConfig);
            EEPROM.write(downFloatAdrr,minConfigFloat);
            tempDown = (minConfig * 10) + minConfigFloat;
            tempDown = tempDown / 10;
         }
     break;

     case 2: 
       lcd.setCursor(6,0);
        lcd.print("MAXIMA");
        lcd.setCursor(7,1);
        lcd.print((int) maxConfig);
        lcd.print(".");
        lcd.print((int) maxConfigFloat);
        

        if(!digitalRead(down)) flagDown = true;

        if(digitalRead(down) && flagDown) {
          maxConfigFloat --;
          flagDown = false; 
         }


         if(!digitalRead(up)) flagUp = true;

        if(digitalRead(up) && flagUp) {
          maxConfigFloat ++;
          flagUp = false; 
         }

        if(maxConfigFloat > 9){
            maxConfigFloat = 0;
            maxConfig ++;
         }
        if(maxConfigFloat < 0){
          maxConfigFloat = 9;
          maxConfig --;
        }
        
        if(!digitalRead(menu)) flagMenu = true;
  
        if(digitalRead(menu) && flagMenu){
            flagMenu = false;
            option ++;
            lcd.clear();
            EEPROM.write(upAdrr, maxConfig);
            EEPROM.write(upFloatAdrr,maxConfigFloat);

            tempUp = (maxConfig * 10) + maxConfigFloat;
            tempUp = tempUp / 10;
         }
     break;
    
   }
}
