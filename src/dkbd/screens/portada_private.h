#include "../base/screens_global.h"

/**
 * Inicializacion de la interfaz
 */
void portada_initUI();

/**
 * Reserva de memoria
 */
void portada_initMemory();

/**
 * Inicializacion de los datos
 */
void portada_initData();

/**
 * Inicializacion del sonido
 */
void portada_initSound();

/**
 * Inicializacion de las paletas
 */
void portada_initPalete();

/**
 * Inicializacion de pantalla
 */
void portada_initBackgrounds();

/**
 * Inicializacion de elementos
 */
void portada_initSprites();

/**
 * Finalizacion de pantalla
 */
void portada_finalizeGraphics();

/**
 * Libera memoria
 */
void portada_finalizeMemory();

/**
 * Actualiza el menu en pantalla
 */
void portada_onRepaintMenu(u8 selected, u32 *content, u32 info);

/**
 * Muestra literal
 */
void portada_showPressStart();

/**
 * Oculta literal
 */
void portada_hidePressStart();

/**
 * Desencadena el inicio (timer)
 */
void portada_beginStart();

/**
 * Desencadena la salida (timer)
 */
void portada_beginExit();

/**
 * Activa control para manejar el menu
 */
void portada_configureControlsMenu();

/**
 * Activa control para pantalla de titulo
 */
void portada_configureControlsPortada();

/**
 * Controlador
 */
void portada_onKeyNoneFunction(u16 joy);

/**
 * Controlador
 */
void portada_onKeyUpPressFunction(u16 joy);

/**
 * Controlador
 */
void portada_onKeyDownPressFunction(u16 joy);

/**
 * Controlador
 */
void portada_onKeyAcceptPressFunction(u16 joy);

/**
 * Controlador
 */
void portada_onKeyCancelPressFunction(u16 joy);

/**
 * Muestra menu
 */
void portada_showMenu();

#define Portada_NUM_SPRITES 2

/**
 * Datos de pantalla
 */
struct Portada_Data_st {
	Sprite* sprites[Portada_NUM_SPRITES];
	u32 tileUserIndex;
	u32 tileMenuIndex;
	u32 tileYesNoIndex;
	u32 tileDifficultyIndex;

	u32 tileMenuPlayIndex;
	u32 tileMenuOptionsIndex;
	u32 tileMenuMusicIndex;
	u32 tileMenuSfxIndex;
	u32 tileMenuDifficultIndex;
	u32 tileMenuBackIndex;
} *Portada_DATA;
