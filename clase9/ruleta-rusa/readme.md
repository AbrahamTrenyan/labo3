# Ruleta Rusa - Threads y Cola de Mensajes

Programa que simula un juego de ruleta rusa con dos procesos:
- **REVOLVER**: Proceso que controla el juego y determina qué jugador es eliminado
- **JUGADORES**: Proceso con 6 threads (uno por jugador) que participan en el juego

## Descripción del Juego

1. El revolver elige aleatoriamente una posición del 1 al 6 donde está la bala
2. Cada jugador (thread) elige secuencialmente una posición del tambor
3. Si la posición elegida coincide con la bala, el jugador es eliminado
4. Si no coincide, el jugador se salva y continúa el siguiente
5. El juego termina cuando un jugador es eliminado




