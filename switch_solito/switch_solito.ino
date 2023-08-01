#include <Servo.h>

int Pin1 = 2;
int Pin2 = 3;
int Pin3 = 4;
int Pin4 = 5;
int FlagPin = 6;
int contador;
int bit1,bit2,bit3,bit4;
int leeFlag;
int var=0; //incremento apara el switch.
String combinacion="";
String contrasenaBinaria = "";
const int pinTRUE = A0;
const int pinFALSE = A1;
Servo servoMotor;


void setup() {
  pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  pinMode(Pin3, INPUT);
  pinMode(Pin4, INPUT);
  pinMode(FlagPin, INPUT);
 pinMode(pinTRUE, OUTPUT);
 pinMode(pinFALSE, OUTPUT);
  Serial.begin(9600);
  servoMotor.attach(7);
  
  // Número de 5 dígitos
  String contrasena = "44444";

  // Convertir cada dígito a binario y concatenarlos
  for (int i = 0; i < 5; i++) {
    int digitoContrasena = contrasena[i] - '0';  // Convertir el dígito de char a entero

    // Convertir el dígito a binario de 4 dígitos
    String binario = "";
    for (int j = 3; j >= 0; j--) {
      if (digitoContrasena & (1 << j)) {
        binario += "1";
      } else {
        binario += "0";
      }
    }

    contrasenaBinaria += binario;  // Concatenar el binario al contrasenaBinaria
  }
  Serial.println("contra="+contrasenaBinaria);  // Mostrar el contrasenaBinaria en el Monitor Serie
  
}

void loop() {
  String a="", b="", c="", d="",e="";//acumuladores de datos enteros para la contrseña.
  
  // Comprobar si se ha completado una combinación
  leeFlag=digitalRead(FlagPin) ;
  Serial.print(leeFlag);
  if (leeFlag== HIGH) {
    
  // Leer los valores de las 4 entradas digitales
  bit1 = digitalRead(Pin1);
  bit2 = digitalRead(Pin2);
  bit3 = digitalRead(Pin3);
  bit4 = digitalRead(Pin4);
  // Concatenar los bits en el orden deseado
  String digito = String (bit1) + String(bit2) + String (bit3) + String(bit4);

  var++; //var se incrementa para los case1,case2,case3,case4.
   switch(var){
    case 1:
    a=digito; //almacenamos primer dígito para la contraseña que seria el 1
    break;
    case 2:
    b=digito; //almacenamos segundo dígito para la contraseña que seria el 2
    break;
    case 3:
    c=digito; //almacenamos tercer dígito para la contraseña que seria el 3
    break;
    case 4:
    d=digito; //almacenamos cuarto dígito para la contraseña que seria el 4
    break;
    case 5:
    e=digito; //almacenamos tercer dígito para la contraseña que seria el 5
    
   
  }delay(50);
   Serial.println("a= "+a);
   Serial.println("b= "+b);
   Serial.println("c= "+c);
   Serial.println("d= "+d);
   Serial.println("e= "+e);
   combinacion=combinacion+a+b+c+d+e;
   Serial.println("comb= "+combinacion);
}
  if(combinacion==contrasenaBinaria){
    digitalWrite(pinTRUE, HIGH); // Encender el TRUE            
    digitalWrite(pinFALSE, LOW); // Apagar el FALSE
    // Desplazamos a la posición horizontalº
    servoMotor.write(55);
    delay(100);
    }
    else{
      
    // Desplazamos a la posición vertical
    servoMotor.write(160);
    digitalWrite(pinFALSE, HIGH); // Encender el FALSE
    digitalWrite(pinTRUE, LOW); // Apagar el TRUE
    delay(100);
    }
  delay(100);
}
