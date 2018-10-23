#include <genesis.h>

/**
 * Dado un numero, si excede del rango lo deja al valor del limite
 */
s8 limits_s8(s8 number, s8 min, s8 max);

/**
 * Dado un numero, si excede del rango lo deja al valor del limite
 */
s16 limits_s16(s16 number, s16 min, s16 max);

/**
 * Dado un numero, si excede del rango lo deja al valor del limite
 */
s32 limits_s32(s32 number, s32 min, s32 max);

/**
 * Suma pero si excede los limites obtiene el valor del limite superado
 */
s8 limits_incr_s8(s8 number, s8 incr, s8 min, s8 max);

/**
 * Suma pero si excede los limites obtiene el valor del limite superado
 */
s16 limits_incr_s16(s16 number, s16 incr, s16 min, s16 max);

/**
 * Suma pero si excede los limites obtiene el valor del limite superado
 */
s32 limits_incr_s32(s32 number, s32 incr, s32 min, s32 max);

/**
 * Suma pero si excede los limites "da la vuelta"
 */
s8 limits_cycle_s8(s8 number, s8 incr, s8 min, s8 max);

/**
 * Suma pero si excede los limites "da la vuelta"
 */
s16 limits_cycle_s16(s16 number, s16 incr, s16 min, s16 max);

/**
 * Suma pero si excede los limites "da la vuelta"
 */
s32 limits_cycle_s32(s32 number, s32 incr, s32 min, s32 max);
