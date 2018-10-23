#include <genesis.h>

#ifndef MAP_RESTRICTION_
#define MAP_RESTRICTION_

const u8 map_restrictions[27] = {
0,//Hueco
0,//Suelo
0,//Suelo
//    LDRU (paredes)
0b00000001, //U1
0b00000001, //U2
0b00000010, //R1
0b00000010, //R2
0b00000100, //D1
0b00000100, //D2
0b00001000, //L1
0b00001000, //L2
//    LDRU (esquinas exteriores)
0, //UL1
0, //UL2
0, //UR1
0, //UR2
0, //DR1
0, //DR2
0, //DL1
0, //DL2
//    LDRU (esquinas interiores)
0b00000110, //UL1
0b00000110, //UL2
0b00001100, //UR1
0b00001100, //UR2
0b00001001, //DR1
0b00001001, //DR2
0b00000011, //DL1
0b00000011  //DL2
};

#endif

