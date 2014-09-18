#include <stdio.h>
#include <wiringPi.h>

int main() {

  // Starte die WiringPi-Api (wichtig)
  if (wiringPiSetupGpio() == -1)
    return 1;

  // Schalte GPIO 17 (=WiringPi Pin 0) auf Ausgang
  // Wichtig: Hier wird das WiringPi Layout verwendet (Tabelle oben)
  pinMode(0, OUTPUT);

  // Dauerschleife
  while(1) {
    // LED an
    digitalWrite(0, 1);

    // Warte 100 ms
    delay(100);

    // LED aus
    digitalWrite(0, 0);

    // Warte 100 ms
    delay(100);
  }
}