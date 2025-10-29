# BiPelea - Código Plantilla Básico

## Estado Actual

He restaurado el código a una versión plantilla básica y limpia. Todo compila correctamente y tienes la estructura fundamental para implementar tu lógica desde cero.

## Estructura Disponible:

### 📁 **def.h** - Definiciones básicas
- ✅ Constantes: VIDA_INICIAL, GOLPE_MIN/MAX, PUNTOS_CUCHILLO/MANOPLA, etc.
- ✅ Estructura Mensaje para comunicación
- ✅ Estructura DatosLuchador básica
- ✅ Enums: Destinos (MSG_RING, MSG_LUCHADOR) y Eventos (EVT_INICIO, EVT_GOLPE, EVT_FIN)

### 📁 **ring.c** - Proceso coordinador (PLANTILLA)
```c
/* PLANTILLA BÁSICA */
- ✅ Inicialización de cola de mensajes con borrar_mensajes()
- ✅ Creación del archivo flag
- ✅ Memoria compartida con vida inicial
- ✅ Bucle principal que recibe mensajes y los muestra
- 🔧 IMPLEMENTA AQUÍ: Tu lógica de combate
```

### 📁 **equipos.c** - Proceso de equipos (PLANTILLA)
```c
/* PLANTILLA BÁSICA */
- ✅ Verificación del archivo flag
- ✅ Conexión a memoria compartida
- ✅ Solicitud de nombres de luchadores (scanf simple)
- ✅ Creación de 4 threads luchadores
- ✅ Join de threads al final
- 🔧 IMPLEMENTA AQUÍ: Tu lógica de manejo de vida/mensajes
```

### 📁 **thread.c** - Threads luchadores (PLANTILLA)
```c
/* PLANTILLA BÁSICA */
- ✅ Estructura básica del thread
- ✅ Recepción de mensajes con debug
- ✅ Switch básico para EVT_INICIO y EVT_FIN
- 🔧 IMPLEMENTA AQUÍ: Tu lógica de ataque
```

## Compilación y Ejecución

```bash
# Compilar (funciona sin errores)
make

# Ejecutar (en terminales separadas)
./ring      # Terminal 1
./equipos   # Terminal 2
```

## Lo que tienes listo para usar:

1. **Comunicación básica**: Cola de mensajes funcionando
2. **Estructura de datos**: DatosLuchador con nombre, vida, equipo, etc.
3. **Threads**: 4 threads luchadores creados correctamente
4. **Memoria compartida**: Vida inicial compartida
5. **Eventos básicos**: EVT_INICIO, EVT_GOLPE, EVT_FIN
6. **Debug**: Prints para ver qué mensajes se reciben

## Puntos de implementación:

- **ring.c línea 38**: Implementa tu lógica de combate
- **equipos.c línea 55**: Implementa tu lógica de manejo de vida
- **thread.c línea 32**: Implementa tu lógica de ataque

¡Ahora tienes una base completamente limpia para implementar tu lógica paso a paso!
