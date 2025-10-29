#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "archivos.h"
#include "clave.h"
#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "memoria.h"

int numero_aleatorio(int min, int max)
{
  return min + rand() % (max - min + 1);
}

void inicializar_vida_base(int vida)
{
  int *vida_base;
  int id_vida_base;
  vida_base = (int *)memoria_crear(sizeof(int), &id_vida_base, CLAVE_BASE);
  *vida_base = vida;
}

void obtener_vida_base(int *vida)
{
  int *vida_base;
  int id_vida_base;
  vida_base = (int *)memoria_crear(sizeof(int), &id_vida_base, CLAVE_BASE);
  *vida = *vida_base;
}

char *obtener_nombre_luchador(int id)
{
  if (id == 0)
  {
    return "[0] Steve";
  }
  else if (id == 1)
  {
    return "[1] John";
  }
  else if (id == 2)
  {
    return "[2] Jim";
  }
  else if (id == 3)
  {
    return "[3] Jack";
  }
  else
  {
    return "[?] Luchador desconocido";
  }
}
void esperar_inicio(int inicia)
{
  FILE *archivo;

  if (inicia == 1)
  {
    archivo = archivo_abrir(ARCHIVO_INICIO, "w");
    archivo_cerrar(archivo);
  }
  else
  {

    archivo = archivo_abrir(ARCHIVO_INICIO, "r");
    while (archivo == NULL)
    {
      printf("Esperando inicio de la arena...\n");
      usleep(500000);
      archivo = archivo_abrir(ARCHIVO_INICIO, "r");
    }
    archivo_cerrar(archivo);
  }
}

int calcular_danio(int objetivo_id, char *danio_str)
{
  int danio, indice_arma, multiplicador_arma;

  danio = numero_aleatorio(GOLPE_MIN, GOLPE_MAX);
  indice_arma = numero_aleatorio(1, 2);
  multiplicador_arma = numero_aleatorio(1, 4);

  if (indice_arma == 1)
  {
    danio += GOLPE_BONUS_CUCHILLO * multiplicador_arma;
  }
  else if (indice_arma == 2)
  {
    danio += GOLPE_BONUS_MANOPLA * multiplicador_arma;
  }

  memset(danio_str, 0, 10);
  sprintf(danio_str, "%d|%d", objetivo_id, danio);
  return danio;
}

void obtener_objetivo_danio(char *danio_str, int *objetivo_id, int *danio)
{
  if (sscanf(danio_str, "%d|%d", objetivo_id, danio) != 2)
  {
    printf("Error al obtener el objetivo y el danio. Formato incorrecto: %s\n", danio_str);
  }
}

int procesar_ataque(int *vida_luchadores, int cola_id, int remitente_id, int objetivo_id, int danio)
{
  int danio_real;

  if (vida_luchadores[objetivo_id] <= 0)
  {
    return 0;
  }

  if (numero_aleatorio(1, 2) == 1)
  {
    danio_real = danio;
  }
  else
  {
    danio_real = 0;
  }

  vida_luchadores[objetivo_id] -= danio;
  if (vida_luchadores[objetivo_id] <= 0)
  {
    printf("%s ha muerto\n", obtener_nombre_luchador(objetivo_id));
    return 0;
  }

  printf("%s ha sido atacado por %s con %d puntos de daño (%d restantes)\n", obtener_nombre_luchador(objetivo_id), obtener_nombre_luchador(remitente_id), danio_real, vida_luchadores[objetivo_id]);
  return 1;
}

int verificar_fin_juego(int *vida_luchadores)
{
  /* 0: gana equipo 0, 1: gana equipo 1, 2: sigue el juego */
  if (vida_luchadores[0] <= 0 && vida_luchadores[1] <= 0)
  {
    return GANA_EQUIPO_1;
  }

  if (vida_luchadores[2] <= 0 && vida_luchadores[3] <= 0)
  {
    return GANA_EQUIPO_0;
  }

  return SIGUE_EL_JUEGO;
}

void luchador_inicializar(luchador_t *luchador, int id, int vida)
{
  luchador->id = id;
  luchador->vida = vida;
  memset(luchador->nombre, 0, LONGITUD_NOMBRE);
  strcpy(luchador->nombre, obtener_nombre_luchador(id));
}

int luchador_atacar(luchador_t *luchador, int cola_id)
{
  int id_destino_1, id_destino_2, danio;
  char danio_str[10];

  if (luchador->id == 0 || luchador->id == 1) /* equipo 0 ataca a los luchadores 2 y 3 */
  {
    id_destino_1 = 2;
    id_destino_2 = 3;
  }
  else /* equipo 1 ataca a los luchadores 0 y 1 */
  {
    id_destino_1 = 0;
    id_destino_2 = 1;
  }

  danio = calcular_danio(id_destino_1, danio_str);
  cola_enviar(cola_id, DEST_ARENA, DEST_LUCHADOR + luchador->id, EVT_ATAQUE, danio_str);
  printf("[%s]: intento atacar al luchador %d con %d puntos de daño\n", luchador->nombre, id_destino_1, danio);

  danio = calcular_danio(id_destino_2, danio_str);
  cola_enviar(cola_id, DEST_ARENA, DEST_LUCHADOR + luchador->id, EVT_ATAQUE, danio_str);
  printf("[%s]: intento atacar al luchador %d con %d puntos de daño\n", obtener_nombre_luchador(luchador->id), id_destino_2, danio);

  return 0;
}
