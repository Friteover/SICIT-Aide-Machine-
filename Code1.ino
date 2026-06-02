#include <DHT.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define LIGHTPIN A0

DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;

void setup() {

  dht.begin();

  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);

  Serial.begin(9600);
}

// Le programme mesure la temperature, l'humidite et la lumiere.
// Les valeurs sont affichees sur l'ecran LCD.
// Des messages indiquent si les conditions sont bonnes pour les plantes.

void loop() {

  float temperature = dht.readTemperature();
  float humidite = dht.readHumidity();
  int lumiere = analogRead(LIGHTPIN);

  // Si le capteur ne repond pas
  if (isnan(temperature) || isnan(humidite)) {
    lcd.clear();
    lcd.print("Erreur capteur");
    delay(2000);
    return;
  }

  // Affichage des valeurs mesurees

  lcd.clear();
  lcd.setRGB(255, 255, 255);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidite);
  lcd.print("%");

  delay(3000);

  // Temperature trop basse : la serre est trop froide.

  lcd.clear();

  if (temperature < 18) {

    lcd.setRGB(0, 0, 255);

    lcd.print("Temp trop basse");

    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
  }

  // Temperature ideale : les plantes peuvent pousser correctement.

  else if (temperature <= 30) {

    lcd.setRGB(0, 255, 0);

    lcd.print("Temp ideale");

    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
  }

  // Temperature trop haute : il fait trop chaud dans la serre.

  else {

    lcd.setRGB(255, 0, 0);

    lcd.print("Temp trop haute");

    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
  }

  delay(3000);

  // Verification de l'humidite

  lcd.clear();

  // L'air est trop sec.

  if (humidite < 40) {

    lcd.setRGB(255, 165, 0);

    lcd.print("Pas assez H");

    lcd.setCursor(0, 1);
    lcd.print(humidite);
    lcd.print("%");
  }

  // Humidite correcte.

  else if (humidite <= 70) {

    lcd.setRGB(0, 255, 0);

    lcd.print("H correcte");

    lcd.setCursor(0, 1);
    lcd.print(humidite);
    lcd.print("%");
  }

  // Trop d'humidite dans la serre.

  else {

    lcd.setRGB(255, 0, 255);

    lcd.print("Trop humide");

    lcd.setCursor(0, 1);
    lcd.print(humidite);
    lcd.print("%");
  }

  delay(3000);

  // Verification de la lumiere

  lcd.clear();

  if (lumiere < 300) {

    lcd.setRGB(255, 255, 0);

    lcd.print("Lum faible");

    lcd.setCursor(0, 1);
    lcd.print("Val:");
    lcd.print(lumiere);
  }

  else {

    lcd.setRGB(255, 255, 255);

    lcd.print("Lum forte");

    lcd.setCursor(0, 1);
    lcd.print("Val:");
    lcd.print(lumiere);
  }

  delay(3000);

  // Affichage dans le moniteur serie

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidite : ");
  Serial.print(humidite);
  Serial.println(" %");

  Serial.print("Lumiere : ");
  Serial.println(lumiere);
}
