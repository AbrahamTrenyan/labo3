# Laboratorio III 
Este repositorio contiene los ejercicios, trabajos prácticos y desarrollos realizados en el marco de la materia **Laboratorio III**, correspondiente a la carrera de Ingeniería Informática.

## 📖  Descripción de la materia

Esta asignatura desarrolla la práctica para las materias teóricas de sistemas operativos.  
Se abarcan las interfaces del sistema operativo al programador, para acceder a todos los servicios de comunicación y a la gestión de los recursos de sistemas UNIX.

El conocimiento y las habilidades desarrolladas en esta materia son requeridas por asignaturas de desarrollo orientadas a:
- Sistemas de comunicaciones
- Sistemas distribuidos
- Procesamiento de alta performance

## 💻  Contenido del repositorio

Este repositorio se irá completando progresivamente con:

- Ejercicios de clase
- Trabajos prácticos 
- Parciales y modelos de parcial
- Documentación y enunciados

## 🛠️  Herramientas y tecnologías

- Lenguaje: C (ANSI C)
- Sistema operativo: **Ubuntu Gutsy Gibbon 7.10**
- Compilador: `gcc-4.1`
- Herramientas: `make`, `gdb`, `ps`, entre otras

Comando para enviar mediante NFS los archivos a Ubuntu:
`sync_labo3`

##Comandos para comprimir y descomprimir carpetas(entregas tp y parciales)📦 

    ###Comprimir una carpeta en .tar.gz

    Parado en el directorio donde está la carpeta:

    `tar -czf nombre-archivo.tar.gz nombre-carpeta`


    👉 Ejemplo:

    `tar -czf Trenyan-tp-memoria-compartida.tar.gz tp-memoria-compartida`

    ####Ver el contenido sin descomprimir 👀 

    `tar -tzf nombre-archivo.tar.gz`

    ### 📂 Descomprimir en una carpeta destino

    Crear la carpeta destino:

    `mkdir nombre-destino`


    Extraer ahí el contenido:

    `tar -xzf nombre-archivo.tar.gz -C nombre-destino`


    👉 Ejemplo:

    `mkdir descomprimirTP`

    `tar -xzf Trenyan-tp-memoria-compartida.tar.gz -C descomprimirTP`