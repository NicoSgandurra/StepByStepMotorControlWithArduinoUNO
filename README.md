# Control de motor paso a paso con Arduino UNO

Control de un motor que sube y baja una mesa con dos pulsadores, con finales de carrera arriba y abajo. El arranque y la detención son graduales.

![Esquema de conexión](Conexi%C3%B3n.png)

## Cómo funciona

- Un pulsador sube la mesa y el otro la baja. Si se presionan los dos a la vez, no hace nada.
- Cada final de carrera corta el movimiento en su sentido, aunque el pulsador siga apretado.
- Al presionar, la señal de velocidad sube de a poco hasta el máximo. Al soltar, baja de a poco hasta detenerse.
- El monitor serie informa "Subiendo" o "Bajando".

## Conexiones

| Pin | Función |
| --- | --- |
| 13 | Pulsador de subida |
| 12 | Pulsador de bajada |
| 11 | Final de carrera superior |
| 10 | Final de carrera inferior |
| 4 | Dirección del motor |
| 3 | Velocidad (salida PWM) |

## Archivos

- `Control de motores paso a paso.ino`: el programa, comentado.
- `Conexión.png`: el esquema de conexión.
- `Programación Visual.png`: la versión del programa en bloques.

![Programa en bloques](Programaci%C3%B3n%20Visual.png)

## Hecho con

Arduino UNO y C++. Proyecto de 2022 y 2023.
