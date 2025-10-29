# BiPelea - Sistema de Combate por Turnos

## Descripción

BiPelea es un sistema de combate por turnos entre dos equipos de luchadores implementado con procesos y threads en C. Cada equipo tiene 2 luchadores y el combate continúa hasta que todos los luchadores de un equipo sean eliminados.

## Compilación

```bash
make
```

## Ejecución

**IMPORTANTE**: Debes ejecutar en DOS terminales distintas

### Terminal 1 - Ring (coordinador)
```bash
./ring
```
Ingresa los nombres de los 4 luchadores (uno por línea)

### Terminal 2 - Equipos (after ring starts)
```bash
./equipos
```

## Ejemplo de Ejecución

**Terminal 1:**
```
./ring
Ingrese nombres (4 luchadores):
[1] Luthor
[2] Superman
[3] Batman
[4] Robin

=== COMBATE INICIADO ===

Luthor ataca con manopla, daño: 32
Superman ataca con cuchillo, daño: 28
Batman ataca con manopla, daño: 31
Robin ataca con cuchillo, daño: 26
Luthor ataca con cuchillo, daño: 30
Superman ataca con manopla, daño: 27
...
=== EQUIPO 1 GANA ===
```

**Terminal 2:**
```
./equipos
Jugador1 iniciado
Jugador2 iniciado
Jugador3 iniciado
Jugador4 iniciado
Jugador1 ataca con manopla, daño: 32
Jugador2 ataca con cuchillo, daño: 28
Jugador3 ataca con manopla, daño: 31
Jugador4 ataca con cuchillo, daño: 26
Jugador1 ataca con cuchillo, daño: 30
Jugador2 ataca con manopla, daño: 27
...
Jugador1 finalizado
Jugador2 finalizado
Jugador3 finalizado
Jugador4 finalizado
```

## Componentes

### Ring (Coordinador)
- Gestiona la vida de todos los luchadores
- Coordina los turnos de combate en orden: 0 → 1 → 2 → 3
- Calcula el daño de cada ataque
- Actualiza la vida de ambos luchadores del equipo contrario
- Determina al ganador
- Comunica por mensajes IPC

### Equipos (Proceso de threads)
- Contiene 4 threads (uno por luchador)
- Cada thread calcula su daño base aleatorio
- Elige arma aleatoria (cuchillo +6 o manopla +8)
- Envía el golpe al ring por mensajes
- Muestra información de preparación de ataques

## Comunicación IPC

### Cola de mensajes
- **MSG_RING**: Recibe ataques del ring
- **MSG_LUCHADOR + i**: Threads reciben turno de ataque
- Los nombres viajan en el campo de mensaje

### Memoria compartida
- **CLAVE_BASE**: Solo almacena VIDA_INICIAL (1200 puntos)
- No se usa para nombres (viajan en mensajes)

## Reglas del Combate

- **Vida inicial**: 1200 HP por luchador
- **Equipos**: 
  - Equipo 1: Luchadores 0 y 1
  - Equipo 2: Luchadores 2 y 3
- **Daño base**: 8-27 puntos
- **Armas**:
  - Cuchillo: +6 puntos
  - Manopla: +8 puntos
- **Turno**: Siempre en orden 0 → 1 → 2 → 3 → 0 ...
- **Defensa**: Cada golpe daña a AMBOS luchadores del equipo contrario
- **Victoria**: Cuando un equipo completo es derrotado

## Arquitectura

### Comunicación IPC
- **Cola de mensajes**: Para envío de comandos y ataques
- **Memoria compartida**: Almacena la vida inicial

### Flujo de Mensaje
1. Thread luchador recibe turno (EVT_GOLPE o EVT_INICIO)
2. Thread calcula daño y prepara ataque
3. Thread envía golpe al ring
4. Ring recibe golpe y elige defensor
5. Ring actualiza vida del defensor
6. Ring envía próximo turno
