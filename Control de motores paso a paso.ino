// C++ code

int speed = 0; // Definimos la variable speed para que el motor arranque controladamente.
int Pos = 0; // Definimos la variable pos para luego recorrer la varilla hasta la posicion deseada.

void setup()
{
  pinMode(13, INPUT); // Pin 13 = Subir.
  pinMode(12, INPUT); // Pin 12 = Bajar.
  pinMode(11, INPUT); // Pin 11 = Final de carrera superior.
  pinMode(10, INPUT); // Pin 10 = Final de carrera Inferior.
  pinMode(4, OUTPUT);
  /*
  Si es "+" la mesa subira.
  Si es "-" la mesa bajara.
  */
  pinMode(3, OUTPUT); // Pin PWM para controlar la velocidad del motor.
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(12) == LOW && digitalRead(13) == LOW) { // Establecemos una condicion para que cuando este subir y bajar sin presionarse descienda la velocidad lentamente.
    if (speed >= 21) {
      speed -= 20; // Disminuimos lentamente la velocidad hasta que sea menor que 21
      analogWrite(3, speed); // Definimos el valor de la velocidad a la salida PWM 3
      delay(100); // Esperamos 100 milisegundos para que la recta de desaceleracion no sea tan repentino
    } else { // En el caso de que sea menor que 20 definimos a la salida del PWM como 0 o desactivada.
      analogWrite(3, LOW);
      speed = 0;
    }
  } else {  // Cuando hay alguno de los botones de mando presionados:
    if (digitalRead(12) != digitalRead(13)) { // Primero establecemos una condicion para que no se pueda presionar subir y bajar simultaneamente mara evitar problemas de cortocircuitos o quemar el motor.
      if (digitalRead(13) == HIGH && digitalRead(11) == LOW) { // Cuando presionemos el boton para subir, el motor comenzara a incrementar su velocidad lentamente hasta llegar a las 700 rpm.
        Serial.println("Subiendo");
        digitalWrite(4, HIGH);  // Definimos la salida 4 como HIGH para que el motor gire en sentido antihorario, subiendo la mesa.
        speed += 10; // Incrementamos la velocidad en 10 cada vez que el codigo pase por esta seccion.
        delay(100); // Esperamos 100 milisegundos para que la recta de desaceleracion no sea tan repentino
      }
      if (digitalRead(13) == LOW) {
        delay(100); // Esperamos 100 milisegundos para que la recta de desaceleracion no sea tan repentino
      }
      // Pin 12 (Bajar)
      if (digitalRead(12) == HIGH && digitalRead(10) == LOW) {
        digitalWrite(4, LOW); // Definimos la salida 4 como LOW para que el motor gire en sentido horario, bajando la mesa.
        Serial.println("Bajando");
        speed += 10; // Incrementamos la velocidad en 10 cada vez que el Codigo pase por esta seccion.
        delay(100); // Esperamos 100 milisegundos para que la recta de desaceleracion no sea tan repentino
      }
      if (digitalRead(12) == LOW) {
        delay(100); // Esperamos 100 milisegundos para que la recta de desaceleracion no sea tan repentino
      }
      if (speed <= 250) { // Si el valor de velocidad es menor que 250:
        analogWrite(3, speed); // Definimos el valor de la velocidad a la salida PWM 3
      } else { // Si el valor de velocidad es mayor que 250:
        analogWrite(3, 255); // Definimos la salida del pin PWM al maximo voltaje que puede entregar
        speed = 260; // Definimos la variable speed como 260 para que no crezca hasta el infinito y ocupe demasiada memoria.
      }
    }
  }
}
