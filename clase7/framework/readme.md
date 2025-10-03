Colchoneria

- COMPILACION
    - make (hace tambien clean borrando el archivo semaforoInicializado)
- EJECUCION
    - ./colchoneria (Terminal 1 - ejecutar PRIMERO)

    - ./vendedor (Terminal 2 - ejecutar despues)

- FUNCIONAMIENTO:
    - colchoneria: Inicializa el semaforo y el stock con 
5 marcas con 10 colchones c/u, repone automaticamente de a un colchon.
    - vendedor: Permite vender colchones, reduce stock disponible
    - Usan memoria compartida y semaforos para sincronizacion

- Semaforo: Lo inicializa colchoneria con valor 1
- El proceso vendedor verifica que el semaforo se haya inicializado antes de empezar
- La memoria compartida almacena: stock de colchones por marca

