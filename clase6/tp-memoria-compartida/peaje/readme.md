PEAJE
- COMPILACION
    - make (hace tambien clean borrando archivos .dat)
- EJECUCION
    - ./peaje <cantidad_de_vias> (Terminal 1 - ejecutar PRIMERO)
    - ./autos (Terminal 2 - ejecutar despues)

- FUNCIONAMIENTO:
    - peaje: Inicializa el semaforo y la memoria compartida con un vector de 
vehiculos en cola por via. Atiende las vias en orden secuencial restando un auto 
por ciclo. Libera vias con mas de 10 autos (pone en 0). Registra liberaciones en 
archivo. 
        - Me tome la libertad de elegir que el programa termine al alcanzar 10 liberaciones, si se quiere que corra infinitamente se puede cambiar la condicion del while a 1, y sacar la logica de eliminar el archivo vias.
    - autos: Busca la via con menos vehiculos y agrega un auto. Muestra la via 
seleccionada. Termina cuando peaje finaliza.
    - Usan memoria compartida y semaforos para sincronizacion

- El proceso autos verifica que peaje  haya inicializado el semaforo antes de empezar

