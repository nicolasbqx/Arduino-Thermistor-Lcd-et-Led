# Arduino-Thermistor-Lcd-et-Led

##### Lecteur/Afficheur de température (thermistor) avec écran lcd (16x2) et led (RGB) indicatrice.
---

Pour l'écran j'utilise un controleur de bus i2c UC-146 qui est éxactement le même que sur le schéma (à la différence de la réf.).

L'écran est un SCM1602A-V2 (16 par 2)

Le thermistor est en 10k

Les connexions sont:

| Sur l'écran | Sur l'arduino |
|:-----------:|:-------------:|
| GND         | GND           |
| VCC         | 5V            |
| SDA         | A4            |
| SCL         | A5            |

Le montage:
![montage](https://raw.githubusercontent.com/nicolasbqx/Arduino-Thermistor-Lcd-et-Led/master/Montage%20et%20tests/Arduino_Uno_i2C_LCD_bb.png)


Les tests (en plaçant deux doigts sur le thermistor):
  // pics
