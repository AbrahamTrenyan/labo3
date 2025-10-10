# Framework Genérico de Cola de Mensajes

Este es un framework genérico para el uso de **colas de mensajes** en sistemas operativos basados en POSIX.

## COMPILACIÓN
```bash
make
```
Esto compila dos programas de prueba: `cola1` y `cola2`.

## EJECUCIÓN

Los programas deben ejecutarse en **DOS TERMINALES DIFERENTES** en el siguiente orden:

### Terminal 1 - Proceso 2 (cola2) - EJECUTAR PRIMERO:
```bash
./cola2
```
**IMPORTANTE:** Este proceso debe ejecutarse PRIMERO porque espera recibir mensajes.

### Terminal 2 - Proceso 1 (cola1) - EJECUTAR SEGUNDO:
```bash
./cola1
```

## FUNCIONAMIENTO

- **cola2** (ejecutar primero): Borra mensajes pendientes, luego espera recibir el mensaje del proceso 1, responde, y finalmente borra la cola.
- **cola1** (ejecutar segundo): Envía un mensaje al proceso 2 y luego espera recibir una respuesta.
- Ambos procesos se comunican mediante **colas de mensajes** usando una clave común (`CLAVE_BASE`).
- La cola de mensajes es borrada por **cola2** al finalizar.

## ESTRUCTURA DEL MENSAJE

Cada mensaje contiene:
- `long_dest`: Identificador del destinatario
- `int_rte`: Identificador del remitente
- `int_evento`: Número de evento
- `char_mensaje[150]`: Contenido del mensaje

## MÓDULOS DEL FRAMEWORK

- **mensajes.c/h**: Funciones para crear, enviar, recibir y borrar colas de mensajes
- **clave.c/h**: Generación de claves IPC
- **def.h**: Definiciones y constantes globales
- **archivos.c/h**: Manejo de archivos (heredado del framework)
- **semaforos.c/h**: Manejo de semáforos (heredado del framework)
- **memoria.c/h**: Manejo de memoria compartida (heredado del framework)

## USO DEL FRAMEWORK

Para usar este framework en tu propio proyecto:

1. Incluir `mensajes.h` y `def.h` en tu código
2. Crear una cola de mensajes con `creo_id_cola_mensajes(CLAVE_BASE)`
3. Enviar mensajes con `enviar_mensaje()`
4. Recibir mensajes con `recibir_mensaje()`
5. Borrar la cola al finalizar con `borrar_cola_de_mensajes()`

## NOTA
Al finalizar la ejecución, `cola2` borra la cola de mensajes automáticamente.
