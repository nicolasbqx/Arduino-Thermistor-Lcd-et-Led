// Les librairies
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <avr/pgmspace.h>

// Définition des pins et des variables
int thermistorPin = A0;

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
 
const int redPotPin = 0;
const int greenPotPin = 1;
const int bluePotPin = 2;
 
int currentColorValueRed;
int currentColorValueGreen;
int currentColorValueBlue;

#define I2C_ADDR 0x27 // Addresse de l'écran en i2c (le votre n'est peut être pas pareil)
#define BACKLIGHT_PIN 3 // pin du rétro éclairage du lcd

// pins de l'écran ver l'i2c
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

// redirection des pin de l'écran au module i2c (UC-146)
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); 

void initPin() {
  // Pin de la led RGB
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void initLed() {
  // Allumage de la led avec un petit jeu de lumière
  currentColorValueRed = (50 - map( analogRead(redPotPin), 0, 1024, 0, 255 ) );
  currentColorValueBlue = (50 - map( analogRead(bluePotPin), 0, 1024, 0, 255 ) );
  currentColorValueGreen = (50 - map( analogRead(greenPotPin), 0, 1024, 0, 255 ) );
  analogWrite(bluePin, currentColorValueBlue);
  delay(500);
  analogWrite(redPin, currentColorValueRed);
  delay(500);
  analogWrite(greenPin, currentColorValueGreen);
}

void initLcd() {
  // Initiation du lcd (rétro-éclairage et taille 16/2)
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
}

void initPrgm() {
  // Affiche "Termometre by Nicolas" sur le lcd
  lcd.print("   Termometre   ");
  lcd.setCursor(0, 1);
  lcd.print(" by Nicolasbqx ");
  delay(1000);
}

double Thermister(int RawADC) {
  // calcul de l'info du thermistor en degrés Celsius
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp;
}

void ledOff() {
  // Extinction de la led (on définit tout à 0s)
  currentColorValueRed = (0 - map( analogRead(redPotPin), 0, 1024, 0, 0 ) );
  currentColorValueBlue = (0 - map( analogRead(bluePotPin), 0, 1024, 0, 0 ) );
  currentColorValueGreen = (0 - map( analogRead(greenPotPin), 0, 1024, 0, 0 ) );
  analogWrite(bluePin, currentColorValueBlue);
  analogWrite(redPin, currentColorValueRed);
  analogWrite(greenPin, currentColorValueGreen);
}
void ledBleu() {
  // La led s'allume en bleu
  currentColorValueRed = (0 - map( analogRead(redPotPin), 0, 1024, 0, 0 ) );
  currentColorValueBlue = (50 - map( analogRead(bluePotPin), 0, 1024, 0, 255 ) );
  currentColorValueGreen = (0 - map( analogRead(greenPotPin), 0, 1024, 0, 0 ) );
  analogWrite(bluePin, currentColorValueBlue);
  analogWrite(redPin, currentColorValueRed);
  analogWrite(greenPin, currentColorValueGreen);
}
void ledVerte() {
  // La led s'allume en vert
  currentColorValueRed = (0 - map( analogRead(redPotPin), 0, 1024, 0, 0 ) );
  currentColorValueBlue = (0 - map( analogRead(bluePotPin), 0, 1024, 0, 0 ) );
  currentColorValueGreen = (50 - map( analogRead(greenPotPin), 0, 1024, 0, 255 ) );
  analogWrite(bluePin, currentColorValueBlue);
  analogWrite(redPin, currentColorValueRed);
  analogWrite(greenPin, currentColorValueGreen);
}
void ledRouge() {
  // La led s'allume en rouge
  currentColorValueRed = (50 - map( analogRead(redPotPin), 0, 1024, 0, 255 ) );
  currentColorValueBlue = (0 - map( analogRead(bluePotPin), 0, 1024, 0, 0 ) );
  currentColorValueGreen = (0 - map( analogRead(greenPotPin), 0, 1024, 0, 0 ) );
  analogWrite(bluePin, currentColorValueBlue);
  analogWrite(redPin, currentColorValueRed);
  analogWrite(greenPin, currentColorValueGreen);
}

void setup() {
  // Execution des fonctions précédentes
  initPin();
  initLed();
  initLcd();
  initPrgm();
  ledOff();
}

void loop() {
  delay(1000); //rafraichissement toutes les 1 secondes pour éviter les scintillements du lcd

  // Affichage de la température
  lcd.clear();
  lcd.print("Temp. : ");
  double fTemp;
  double temp = Thermister(analogRead(0));
  lcd.print(temp);
  lcd.print(" C");

  // Si la température est en dessous de 10 °C..
  if (temp<10) {
    ledBleu();
    lcd.setCursor(0, 1);
    lcd.print("Glacial"); // ..afficher un temps "Glacial" sur le lcd
  }
  
  // Si la température est entre 10 et 20 °C..
  if (temp<20 && temp>10) {
    ledBleu();
    lcd.setCursor(0, 1);
    lcd.print("Frais"); // ..afficher un temps "Frais" sur le lcd
  }

  // Si la température est entre 20 et 30 °C..
  else if (temp<30 && temp>20) {
    ledVerte();
    lcd.setCursor(0, 1);
    lcd.print("Agreable"); // ..afficher un temps "Agreable" sur le lcd
  }

  // Si la température est entre 30 et 40 °C..
  else if (temp<40 && temp>30) {
    ledRouge();
    lcd.setCursor(0, 1);
    lcd.print("Chaud"); // ..afficher un temps "Chaud" sur le lcd
  }

  // Si la température est au dessus de 40 °C
  else if (temp<40) {
    ledRouge();
    lcd.setCursor(0, 1);
    lcd.print("Canicule"); // ..afficher un temps "Canicule" sur le lcd
  }

}



