#include <genesis.h>

#ifndef MAP_ONTOP_
#define MAP_ONTOP_

const u8 map_ontop[128] = {
0,//Hueco
//  Suelo
0,0,
// LDRU (paredes)
0,0,0,0,0,0,0,0,
// LDRU (esquinas exteriores)
0,0,0,0,0,0,0,0,
// LDRU (esquinas interiores)
0,0,0,0,0,0,0,0,
// Extra
0,0,0,0,0,0,
// Flower TopTop BottomBottom
6,6,7,7,
0,0,0,0,
0,0,0,0,
0,0,0,0,
// Palmtree TopTop MidMidMid BottomBottom
4,4,5,5,5,6,6,7,7,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
//wall
20,20,20,20,20,20,20,20,
20,20,20,20,20,20,20,20,
20,20,20,20,20,20,20,20,20
};

#endif

