#include <Servo.h>

#define PAS 2


Servo servoTilt;
Servo servoPan;

int read;
int posx;
int posy;
int incx=0;
int incy=0;

char datax[1];

void setup() {

  Serial.begin(9600);

  read=0;
  posx=90;

  posy=95;

  /*************initialisation des servo_moteurs**********/
  servoTilt.attach(5);//servo_moteur tilt
  servoPan.attach(6);//servo_moteur pan

  /************position initiale****************/

  servoTilt.write(posx);
  servoPan.write(posy);

}

void loop() {
  int i = 0;

  // HAUT
  for(i=0; i<10 ; i++) {
    posx += PAS;
    servoTilt.write(posx);
    delay(300);
  }

  // BAS
  for(i=0; i<10 ; i++) {
    posx -= PAS;
    servoTilt.write(posx);
    delay(300);
  }

  // DROITE
  for(i=0; i<10 ; i++) {
    posy += PAS;
    servoPan.write(posy);
    delay(300);
  }

  // GAUCHE
  for(i=0; i<10 ; i++) {
    posy -= PAS;
    servoPan.write(posy);
    delay(300);
  }

}

