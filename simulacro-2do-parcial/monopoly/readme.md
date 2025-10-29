# MonoNopoly - Simulacro Segundo Parcial

## Descripción

Juego de MonoNopoly donde los jugadores avanzan por un tablero de 60 posiciones, ganando o perdiendo dinero según donde caigan. Los jugadores que pierden todo su dinero quedan eliminados. El juego termina cuando un jugador llega a la meta o solo queda un jugador activo.

## Arquitectura

**Proceso tablero**: Maneja los turnos de cada jugador e informa el estado del juego. Lleva un array de struct con la información de cada jugador (posición, dinero, activo, turno_perdido). Conoce el tablero completo con todas las posiciones y sus efectos. Espera recibir la cantidad de jugadores por mensaje antes de iniciar.

**Proceso jugadores**: Recibe la cantidad de jugadores por parámetro, la envía al tablero por mensaje, y luego lanza threads (uno por jugador) que se comunican con el tablero por cola de mensajes. Cada thread genera un número aleatorio (0-3) indicando cuántos pasos avanza, y lo envía al tablero como string en el mensaje.

El tablero recibe el mensaje con los pasos, actualiza la posición del jugador, aplica los efectos de la casilla (gana/pierde dinero, pierde turno) y verifica si alguien llegó a la meta o quedó eliminado.

**Sincronización**: Los threads usan mutex para proteger la generación de números aleatorios. La comunicación entre procesos es por cola de mensajes.

**Memoria compartida**: El tablero escribe la plata inicial ($1000) en memoria compartida. Los threads leen este valor.

## Flujo de comunicación

1. `tablero` inicia y espera mensaje
2. `jugadores` envía cantidad de jugadores → `tablero` (por cola de mensajes)
3. `tablero` inicializa jugadores y escribe plata_inicial en memoria compartida
4. `jugadores` lee plata_inicial de memoria compartida
5. `jugadores` crea threads
6. Comienza el juego con turnos por cola de mensajes
7. El juego termina cuando:
   - Un jugador llega a la posición 60, O
   - Solo queda 1 jugador activo (los demás perdieron todo su dinero)
8. Gana el jugador activo con más dinero

## Instrucciones de Ejecución

1. Compilar: `make`
2. Ejecutar primero el tablero: `./tablero`
3. En otra terminal ejecutar: `./jugadores <cantidad_jugadores>`

Ejemplo con 3 jugadores:
```
Terminal 1: ./tablero
Terminal 2: ./jugadores 3
```

**NOTA**: El archivo `flag.dat` indica si se corrió el proceso tablero. Al hacer `make` se borra este archivo.

## Reglas del Juego

- Cada jugador empieza en posición 0 con $1000
- Por turno avanzan de 0 a 3 pasos (aleatorio)
- El tablero tiene 60 posiciones con diferentes eventos
- Si un jugador llega a $0 o menos, queda **eliminado** del juego
- Los jugadores eliminados no juegan más turnos
- El juego termina cuando alguien llega a la posición 60 o solo queda 1 jugador
- Gana el jugador activo con más dinero al finalizar el juego
