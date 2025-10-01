Primer examen parcial 
Consignas 
El aeropuerto 
En el nuevo aeropuerto MDQ, se solicita realizar un panel que muestre los aviones que llegan para mostrar por pantalla en el panel, junto con su vuelo y su tipo de avión. 
Se contará con un proceso panel y con 3 procesos aviones. 
Cada proceso avión recibirá el número de proceso por parámetro al ejecutar el programa. 
Para comunicar los procesos se implementa ARCHIVOS y SEMÁFOROS: 
Proceso Aviones (ejecutar 3 veces con el mismo código fuente)
- Realizar un menú para ingreso por teclado, donde se informe de donde proviene (ciudad).
- Luego debe escribir en archivo el número de avión y su ciudad de donde provino.  
- Sería recomendable usar un único archivo, por más que puede utilizar tres.
Proceso PANEL 
- Cada 500 ms chequea el archivo y muestra por pantalla el/los mensajes que fueron cargados por los aviones 
- Espera semáforo. 
- Lee el mensaje y lo muestra por pantalla
- Levanta semáforo 
- Espera 500 ms y vuelve al punto 1. 
Sería bueno cada tanto limpiar mensajes del archivo. 
Realizar la solución utilizando ARCHIVOS y SEMÁFOROS. En total son 4 procesos corriendo en forma simultánea. Se debe mostrar la actividad de cada proceso. El panel debería ser quien inicializa el semáforo y los datos de inicio.
