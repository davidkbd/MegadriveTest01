#include <genesis.h>

//
// Estructura de data de u16 data:
// F          FFF
// 0000       000 000 000 000
// 4 switches 4 slots de 8 estados
//

/*
void onShow(u8 *digits, u8 length);

int main() {
	//4 switches | 4 slots de 8 estados
	//F          | FFF
	//0000       | 000 000 000 000
	u16 prueba1 = 000032;
	u16 prueba2 = 000172;
	u16 prueba3 = 07777;
	u16 prueba4 = 0xFFFF;

	printf("%X ", prueba1);
	numbers_toBaseX(onShow, 8, prueba1);
	numbers_toBaseX(onShow, 2, prueba1);
	printf("%X ", prueba2);
	numbers_toBaseX(onShow, 8, prueba2);
	numbers_toBaseX(onShow, 2, prueba2);
	printf("%X ", prueba3);
	numbers_toBaseX(onShow, 8, prueba3);
	numbers_toBaseX(onShow, 2, prueba3);
	printf("%X ", prueba4);
	numbers_toBaseX(onShow, 8, prueba4);
	numbers_toBaseX(onShow, 2, prueba4);
	
	printf("----\n");
	numbers_toBaseX(onShow, 8, 000172);
	printf("%d\n", container4U16_getSlotValue(000172, 1));
	printf("%d\n", container4U16_getSlotValue(000172, 2));
	printf("%d\n", container4U16_getSlotValue(000172, 3));
	printf("%d\n", container4U16_getSlotValue(000172, 4));
	
	printf("----\n");
	printf("%d\n", container4U16_getSwitchState(0b111100000000000, 1));
	printf("%d\n", container4U16_getSwitchState(0b111100000000000, 2));
	printf("%d\n", container4U16_getSwitchState(0b111100000000000, 3));
	printf("%d\n", container4U16_getSwitchState(0b111100000000000, 4));
	printf("%d\n", container4U16_getSwitchState(0b011100000000000, 1));
	printf("%d\n", container4U16_getSwitchState(0b011100000000000, 2));
	printf("%d\n", container4U16_getSwitchState(0b011100000000000, 3));
	printf("%d\n", container4U16_getSwitchState(0b011100000000000, 4));
	printf("%d\n", container4U16_getSwitchState(0b001100000000000, 1));
	printf("%d\n", container4U16_getSwitchState(0b001100000000000, 2));
	printf("%d\n", container4U16_getSwitchState(0b001100000000000, 3));
	printf("%d\n", container4U16_getSwitchState(0b001100000000000, 4));
	
	int prueba5 = 0;
	
	container4U16_setSlotValue(&prueba5, 1, 7);
	container4U16_setSlotValue(&prueba5, 2, 7);
	container4U16_setSlotValue(&prueba5, 3, 7);
	container4U16_setSlotValue(&prueba5, 4, 7);
	
	container4U16_enableSwitch(&prueba5, 1);
	numbers_toBaseX(onShow, 2, prueba5);
	container4U16_enableSwitch(&prueba5, 2);
	numbers_toBaseX(onShow, 2, prueba5);
	container4U16_enableSwitch(&prueba5, 3);
	numbers_toBaseX(onShow, 2, prueba5);
	container4U16_enableSwitch(&prueba5, 4);
	numbers_toBaseX(onShow, 2, prueba5);
	container4U16_disableSwitch(&prueba5, 3);
	numbers_toBaseX(onShow, 2, prueba5);
	container4U16_disableSwitch(&prueba5, 4);
	numbers_toBaseX(onShow, 2, prueba5);
	
	container4U16_setSlotValue(&prueba5, 1, 1);
	container4U16_setSlotValue(&prueba5, 2, 0);
	container4U16_setSlotValue(&prueba5, 3, 0);
	container4U16_setSlotValue(&prueba5, 4, 1);
	numbers_toBaseX(onShow, 2, prueba5);
	numbers_toBaseX(onShow, 8, prueba5);
	container4U16_setSlotValue(&prueba5, 4, 2);
	numbers_toBaseX(onShow, 2, prueba5);
	numbers_toBaseX(onShow, 8, prueba5);

	return 0;
}

void onShow(u8 *digits, u8 length) {
	if (length == 0) {
		printf("0");
	} else {
		u8 iBuffer = length;
		for (u8 i = 0; i < length; ++i) {
			--iBuffer;
			printf("%d", digits[iBuffer]);
			
		}
	}
	printf("\n");
}
*/

/**
 * Obtiene el valor de uno de los slots que contiene data
 */
u16  container4U16_getSlotValue(u16 data, u8 slot);

/**
 * Establece el valor de uno de los slots de data
 */
void container4U16_setSlotValue(u16 *data, u8 slot, u16 value);

/**
 * Comprueba el estado de uno de los switches de data
 */
u8   container4U16_getSwitchState(u16 data, u8 slot);

/**
 * Activa uno de los switches de data
 */
void container4U16_enableSwitch(u16 *data, u8 slot);

/*
 * Desactiva uno de los switches de data
 */
void container4U16_disableSwitch(u16 *data, u8 slot);

