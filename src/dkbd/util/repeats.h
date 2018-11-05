#include <genesis.h>

//
// Esta libreria sirve para utilizar en un manejador de eventos
//
// Por defecto devuelve todo 0, pero teniendo en cuenta el tiempo
// dado y los delays especificados devuelve 1 cuando se cumplan las
// condiciones.
//



#define TRUE 1
#define FALSE 0

typedef u8 (*repeats_mode)(u32 time);

/**
 * Devuelve 1 en los tiempos que coincida con firstDelay y secondDelay
 * a partir de ahi, devuelve 1 dependiendo del modo especificado.
 */
u8 repeats_delayed(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode);

/**
 * Devuelve 1 en los tiempos que coincida con firstDelay y secondDelay
 * a partir de ahi, devuelve 1 dependiendo de los modos especificado.
 * Se combinan ambos modos, es decir, devuelve 1 si cualquiera de los
 * dos modos indica que hay que devolver un 1.
 */
u8 repeats_delayed_combine(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode1, repeats_mode mode2);

/**
 * Devuelve 1 en los tiempos que coincida con firstDelay y secondDelay
 * a partir de ahi, devuelve 1 dependiendo de los modos especificado.
 * Se excluyen los modos, es decir, devuelve 1 si ambos modos indica
 * al mismo tiempo que hay que devolver un 1.
 */
u8 repeats_delayed_exclude(u32 time, u32 firstDelay, u32 secondDelay, repeats_mode mode1, repeats_mode mode2);

/**
 * Modo que devuelve siempre 1.
 */
u8 repeats_all_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 2.
 */
u8 repeats_1_each_2_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 3.
 */
u8 repeats_1_each_3_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 4.
 */
u8 repeats_1_each_4_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 5.
 */
u8 repeats_1_each_5_mode(u32 time);

/**
 * Modo que devuelve 2 de cada 3.
 */
u8 repeats_2_each_3_mode(u32 time);

/**
 * Modo que devuelve 2 de cada 4.
 */
u8 repeats_2_each_4_mode(u32 time);

/**
 * Modo que devuelve 2 de cada 5.
 */
u8 repeats_2_each_5_mode(u32 time);

/**
 * Modo que devuelve 3 de cada 4.
 */
u8 repeats_3_each_4_mode(u32 time);


/**
 * Modo que devuelve 3 de cada 5.
 */
u8 repeats_3_each_5_mode(u32 time);

/**
 * Modo que devuelve 4 de cada 5.
 */
u8 repeats_4_each_5_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 10.
 */
u8 repeats_1_each_10_mode(u32 time);

/**
 * Modo que devuelve 3 de cada 10.
 */
u8 repeats_3_each_10_mode(u32 time);

/**
 * Modo que devuelve 7 de cada 10.
 */
u8 repeats_7_each_10_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 20.
 */
u8 repeats_1_each_20_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 30.
 */
u8 repeats_1_each_30_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 40.
 */
u8 repeats_1_each_40_mode(u32 time);

/**
 * Modo que devuelve 1 de cada 50.
 */
u8 repeats_1_each_50_mode(u32 time);
