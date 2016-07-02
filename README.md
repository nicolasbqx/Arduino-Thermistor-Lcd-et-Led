# Arduino-Thermistor-Lcd-et-Led

##### Lecteur/Afficheur de température (thermistor) avec écran lcd (16x2) et led (RGB) indicatrice.
---

Pour l'écran j'utilise un controleur de bus i2c UC-146 qui est éxactement le même que sur le schéma (à la différence de la réf.) mais placé derrière l'écran.

L'écran est un SCM1602A-V2 (16x2)

Le thermistor est en 10k

Les connexions sont:

| Sur l'écran | Sur l'arduino |
|:-----------:|:-------------:|
| GND         | GND           |
| VCC         | 5V            |
| SDA         | A4            |
| SCL         | A5            |


| Sur la led*    | Sur l'arduino |
|:--------------:|:-------------:|
| Red            | 9             |
| Anode          | 5V            |
| Green          | 10            |
| Blue           | 11            |

*Pensez à bien mettre une résistance du niveau de votre led à chaque pattes (4) de la led.

![montage thermistor](http://playground.arduino.cc/uploads/ComponentLib/simple10ktherm_schem_new.png)

| Sur le module thermistor | Sur l'arduino |
|:------------------------:|:-------------:|
| +5V                      | 5V            |
| Analog In                | A0            |
| trois barres             | GND           |

Le montage:
![montage arduino](https://raw.githubusercontent.com/nicolasbqx/Arduino-Thermistor-Lcd-et-Led/master/Montage%20et%20tests/Arduino_Uno_i2C_LCD_bb.png)


Les tests (en plaçant deux doigts sur le thermistor):

Agréable:
![test 26,79](https://raw.githubusercontent.com/nicolasbqx/Arduino-Thermistor-Lcd-et-Led/master/Montage%20et%20tests/Arduino-Thermistor-Lcd-et-Led_agreable.jpg)

Chaud:
![test 33,3](https://raw.githubusercontent.com/nicolasbqx/Arduino-Thermistor-Lcd-et-Led/master/Montage%20et%20tests/Arduino-Thermistor-Lcd-et-Led_chaud.jpg)

