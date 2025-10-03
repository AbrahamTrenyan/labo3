#include "def.h"
#include "global.h"

int id_semaforo;
int contador_lotes[CANTIDAD_CAJEROS] = {0, 0, 0};
int total_efectivo = 0;
int total_cheque = 0;
int total_importe_efectivo = 0;
int total_importe_cheque = 0;
int cajeros_efectivo[CANTIDAD_CAJEROS] = {0, 0, 0};
int cajeros_cheque[CANTIDAD_CAJEROS] = {0, 0, 0};
int cajeros_importe_efectivo[CANTIDAD_CAJEROS] = {0, 0, 0};
int cajeros_importe_cheque[CANTIDAD_CAJEROS] = {0, 0, 0};
