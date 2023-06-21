// C++ code

int speed = 0; // Variable para controlar la velocidad del motor.
int Pos = 0; // Variable para almacenar la posición deseada de la mesa.

void setup()
{
  pinMode(13, INPUT); // Pin 13 = Botón de subir.
  pinMode(12, INPUT); // Pin 12 = Botón de bajar.
  pinMode(11, INPUT); // Pin 11 = Final de carrera superior.
  pinMode(10, INPUT); // Pin 10 = Final de carrera inferior.
  pinMode(4, OUTPUT); // Pin 4 = Control de dirección del motor.
  
  /*
  Si se establece en "+", la mesa se moverá hacia arriba.
  Si se establece en "-", la mesa se moverá hacia abajo.
  */
  
  pinMode(3, OUTPUT); // Pin PWM para controlar la velocidad del motor.
  Serial.begin(9600); // Inicialización de la comunicación serial.
}

void loop()
{
  if (digitalRead(12) == LOW && digitalRead(13) == LOW) {
    // Si ambos botones están en estado bajo, la mesa debe detenerse y reducir gradualmente la velocidad.
    
    if (speed >= 21) {
      speed -= 20; // Reducir gradualmente la velocidad hasta que sea menor que 21.
      analogWrite(3, speed); // Establecer el valor de velocidad en la salida PWM 3.
      delay(100); // Esperar 100 milisegundos para una desaceleración suave.
    } else {
      analogWrite(3, LOW); // Desactivar la salida del PWM.
      speed = 0; // Reiniciar la velocidad a 0.
    }
  } else {
    // Cuando se presiona uno de los botones de subir o bajar:
    
    if (digitalRead(12) != digitalRead(13)) {
      // Evitar que se presionen ambos botones simultáneamente para evitar problemas de cortocircuito o daños al motor.
      
      if (digitalRead(13) == HIGH && digitalRead(11) == LOW) {
        // Si se presiona el botón de subir y no se ha alcanzado el final de carrera superior:
        
        Serial.println("Subiendo");
        digitalWrite(4, HIGH); // Establecer la dirección del motor en sentido antihorario para subir la mesa.
        speed += 10; // Incrementar la velocidad en 10 en cada iteración.
        delay(100); // Esperar 100 milisegundos para una aceleración suave.
      }
      
      if (digitalRead(13) == LOW) {
        delay(100); // Esperar 100 milisegundos para una desaceleración suave.
      }
      
      if (digitalRead(12) == HIGH && digitalRead(10) == LOW) {
        // Si se presiona el botón de bajar y no se ha alcanzado el final de carrera inferior:
        
        digitalWrite(4, LOW); // Establecer la dirección del motor en sentido horario para bajar la mesa.
        Serial.println("Bajando");
        speed += 10; // Incrementar la velocidad en 10 en cada iteración.
        delay(100); // Esperar 100 milisegundos para una aceleración suave.
      }
      
      if (digitalRead(12) == LOW) {
        delay(100); // Esperar 100 milisegundos para una desaceleración suave.
      }
      
      if (speed <= 250) {
        // Si el valor de velocidad es menor o igual a 250:
        
        analogWrite(3, speed); // Establecer el valor de velocidad en la salida PWM 3.
      } else {
        // Si el valor de velocidad es mayor que 250:
        
        analogWrite(3, 255); // Establecer la salida del pin PWM al máximo voltaje que puede entregar.
        speed = 260; // Establecer la velocidad en 260 para evitar un crecimiento infinito y un uso excesivo de memoria.
      }
    }
  }
}
