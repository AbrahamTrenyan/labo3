Proceso CCI (Centro de Control Inteligente) 
Realizar un menú para controlar y modificar los 3 paneles (PMV). 
Opción 1 – Leer Panel
Se solicita por teclado el número de panel, y se muestra el mensaje que está mostrando en ese momento. 
Opción 2 – Escribir Panel
Se solicita por teclado el número de panel y el mensaje a enviar. 
Proceso PANEL (ejecutar 3 veces con el mismo código fuente) 
Recibe por parámetro el número de panel (de 1 a 3). Carga al panel el mensaje inicial “default”. 
Cada 100 ms chequea el mensaje que debe mostrar; sólo actualiza la pantalla cuando hay cambios. Es decir: 
Espera semáforo. 
Lee el mensaje que le corresponde. 
Verifica si es diferente al último leído. 
Si es diferente, borra la pantalla y muestra el mensaje. 
PANEL NR1 (o el que fuera) 
“MENSAJE” 
Levanta semáforo. 
Espera 100 ms y vuelve al punto 1. 
Realizar la solución utilizando ARCHIVOS y SEMÁFOROS. En total son 4 procesos corriendo en forma simultánea. Se debe mostrar la actividad de cada proceso. El CCI es quien inicializa el semáforo y los datos de inicio. 


