Pienso un numero

- COMPILACION
    - make(hace tambien clean borrando el archivo semaforoInicializado)
- EJECUCION
    - ./pienso (Terminal 1 - ejecutar PRIMERO)

    - ./jugador (Terminal 2 - ejecutar despues)

- FUNCIONAMIENTO:
    - pienso: Piensa un numero aleatorio del 1 al 99, espera a que el jugador
lo adivine verificando cada intento. Muestra el nombre del ganador cuando acierta.
    - jugador: Solicita el nombre del jugador y prueba numeros aleatorios no 
repetitivos hasta acertar. Muestra cada intento y el total al ganar.
    - Usan memoria compartida y semaforos para sincronizacion

- Semaforo: Lo inicializa pienso con valor 1
- El proceso jugador verifica que el semaforo se haya inicializado antes de empezar
- La memoria compartida almacena: nombre del jugador, numero pensado y estado de acierto

