#ifndef _FUNCIONES_H
#define _FUNCIONES_H

#include "define.h"

int numero_aleatorio(int min, int max);

void inicializar_vida_base(int vida);

void obtener_vida_base(int *vida);

void esperar_inicio(int inicia);

int calcular_danio(int objetivo_id, char *danio_str);

void obtener_objetivo_danio(char *danio_str, int *objetivo_id, int *danio);

char *obtener_nombre_luchador(int id);

void luchador_inicializar(luchador_t *luchador, int id, int vida);

int luchador_atacar(luchador_t *luchador, int cola_id);

int procesar_ataque(int *vida_luchadores, int cola_id, int remitente_id, int objetivo_id, int danio);

int verificar_fin_juego(int *vida_luchadores);

#endif
