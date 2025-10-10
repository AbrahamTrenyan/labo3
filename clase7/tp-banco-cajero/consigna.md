Consigna 


BANCO:
Lleva el saldo de 100 clientes en memoria local. Recibe depósitos, consultas y extracciones.

CAJERO_AUTOMATICO:
Permite a un cliente realizar consultas, depósitos, extracciones. Tiene un menú con las tres opciones.

Eventos disponibles:

[01]  EVT_CONSULTA_SALDO 
Permite consultar el saldo de un cliente, como parámetro lleva COD_CLIENTE (código del cliente)

[02] EVT_DEPOSITO
Permite realizar un depósito, como parámetros lleva |COD_CLIENTE|IMPORTE (código del cliente, importe a depositar).

[03] EVT_EXTRACCION 
Permite realizar una extracción, como parámetros lleva |COD_CLIENTE|IMPORTE (código del cliente, importe a extraer).

[04] EVT_RTA_SALDO
Responde con el saldo del cliente “|COD_CLIENTE|SALDO”

[05] EVT_RTA_SALDO_NOK
Responde con el saldo del cliente “|COD_CLIENTE|ERROR”, donde ERROR es un texto con el error (por ejemplo: cliente no encontrado).

[06] EVT_RTA_DEPOSITO_OK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|SALDO”

[07] EVT_RTA_DEPOSITO_NOK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|ERROR”, ” donde ERROR es un texto con el error (por ejemplo: cliente no encontrado).

[08] EVT_RTA_EXTRACCION_OK
Responde con el saldo del cliente después de la extracción “|COD_CLIENTE|SALDO”

[09] EVT_RTA_EXTRACCION_NOK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|ERROR”, donde ERROR es un texto con el error (por ejemplo: cliente no encontrado).

CASOS DE USO:

CU-001: Consulta de saldo:
El módulocajero_automatico solicita por teclado código de cliente. Se envía por una cola de mensajes el evento EVT_CONSULTA_SALDO, con el código de cliente COD_CLIENTE.
El módulo banco responde con el evento EVT_RTA_SALDO con código cliente y el saldo. En caso de error se envía el evento EVT_RTA_SALDO_NOK indicando el error.

CU-002: Depósitos
El módulocajero_automatico solicita por teclado código de cliente y el importe. Se envía por cola de mensajes el evento EVT_DEPOSITO, con los datos solicitados.
El módulo banco responde con el evento EVT_RTA_DEPOSITO_OK con código cliente y el saldo. En caso de error se envía el evento EVT_RTA_DEPOSITO_NOK indicando el error.

CU-003: Extracciones
El módulo cajero_automatico solicita por teclado código de cliente y el importe. Se envía por cola de mensajes el evento EVT_EXTRACCION con los datos solicitados.
El módulo banco responde con el evento EVT_EXTRACCION_OK con código cliente y el saldo. En caso de error se envía el evento EVT_EXTRACCION_NOK indicando el error.

Realizar los siguientes puntos: 

	1.	Se pide realizar la solución con dos procesos por separado utilizando una cola de mensajes.
	2.	Mostrar los mensajes por pantalla en ambos procesos.
	3.	Buscar la forma que puede haber más de un cajero_automatico.
