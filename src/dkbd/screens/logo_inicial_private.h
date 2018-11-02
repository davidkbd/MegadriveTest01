#include "../base/screens_global.h"

/**
 * Inicializacion de la interfaz
 */
void logoInicial_initUI();

/**
 * Reserva de memoria
 */
void logoInicial_initMemory();

/**
 * Inicializacion de los datos
 */
void logoInicial_initData();

/**
 * Inicializacion del sonido
 */
void logoInicial_initSound();

/**
 * Inicializacion de las paletas
 */
void logoInicial_initPalete();

/**
 * Inicializacion de pantalla
 */
void logoInicial_initBackgrounds();

/**
 * Inicializacion de elementos
 */
void logoInicial_initSprites();

/**
 * Finalizacion de pantalla
 */
void logoInicial_finalizeGraphics();

/**
 * Libera memoria
 */
void logoInicial_finalizeMemory();

/**
 * Desencadena el inicio (timer)
 */
void logoInicial_beginStart();

/**
 * Desencadena la salida (timer)
 */
void logoInicial_beginExit();

#define LogoInicial_NUM_SPRITES 1

/**
 * Datos de pantalla
 */
struct LogoInicial_Data_st {
	Sprite* sprites[LogoInicial_NUM_SPRITES];
} *LogoInicial_DATA;
