# BiPelea - Versión Básica para Implementar

## Estado Actual

He restaurado el código a una versión básica y limpia. Todo compila correctamente y tienes la estructura fundamental para implementar tu lógica paso a paso.

## Lo que está disponible:

### 📁 **def.h** - Constantes y estructuras
- ✅ Todas las constantes necesarias (VIDA_INICIAL, GOLPE_MIN/MAX, etc.)
- ✅ Estructura Mensaje para comunicación
- ✅ Estructura Luchador 
- ✅ Enums para Destinos (MSG_RING, MSG_LUCHADOR) y Eventos (EVT_INICIO, EVT_GOLPE, EVT_FIN)

### 📁 **ring.c** - Proceso coordinador
- ✅ Inicialización de cola de mensajes
- ✅ Creación del archivo flag
- ✅ Memoria compartida con vida inicial
- ✅ Bucle principal básico que recibe mensajes
- 🔧 **AQUI IMPLEMENTAS**: Lógica de turnos, aciertos/fallos, control de juego

### 📁 **equipos.c** - Proceso de equipos
- ✅ Verificación del archivo flag
- ✅ Conexión a memoria compartida
- ✅ Solicitud de nombres de luchadores
- ✅ Creación de 4 threads luchadores
- 🔧 **AQUI IMPLEMENTAS**: Manejo de vida de luchadores, procesamiento de aciertos

### 📁 **thread.c** - Threads luchadores
- ✅ Estructura básica del thread
- ✅ Recepción de mensajes
- ✅ Switch básico para eventos
- 🔧 **AQUI IMPLEMENTAS**: Lógica de ataque, cálculo de daño, envío al ring

## Compilación y Ejecución

```bash
# Compilar
make

# Ejecutar (en terminales separadas)
./ring      # Terminal 1
./equipos   # Terminal 2
```

## Próximos Pasos Sugeridos

1. **Implementar envío de turnos en ring.c**
   - Enviar EVT_GOLPE al luchador correspondiente
   - Manejar rotación de turnos

2. **Implementar ataque en thread.c**
   - Calcular daño (base + arma)
   - Enviar golpe al ring

3. **Implementar procesamiento en ring.c**
   - Recibir ataques
   - Determinar acierto/fallo
   - Enviar resultado a equipos

4. **Implementar manejo de vida en equipos.c**
   - Procesar aciertos
   - Actualizar vida de luchadores
   - Detectar eliminaciones

## Estructura de Mensajes Sugerida

- **EVT_INICIO**: Ring → Luchadores (inicio de combate)
- **EVT_GOLPE**: Ring → Luchador (tu turno) / Luchador → Ring (mi ataque)
- **EVT_FIN**: Equipos → Ring (juego terminado)

¡Ahora tienes una base limpia para implementar tu lógica paso a paso!
