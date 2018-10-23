#include <genesis.h>

#include "menu_list.h"
#include "menu_list_private.h"

void menuList_initialize(u32* content, MenuList_EventCallback* acceptCallbacks, MenuList_EventCallback* cancelCallbacks, u32 info) {
	MenuList_DATA = MEM_alloc(sizeof(struct MenuList_DATA_st));
	MenuList_DATA->selected = 0;
	MenuList_DATA->info = info;

	int count = 0;
	while (content[count] != MenuList_ENDMENU) {
		++count;
	}
	MenuList_DATA->options = MEM_alloc(sizeof(u32) * count + 1);
	MenuList_DATA->acceptCallbacks = MEM_alloc(sizeof(MenuList_EventCallback) * count);
	MenuList_DATA->cancelCallbacks = MEM_alloc(sizeof(MenuList_EventCallback) * count);
	for (int i=0; i<count; ++i) {
		MenuList_DATA->options[i] = content[i];
		MenuList_DATA->acceptCallbacks[i] = acceptCallbacks[i];
		MenuList_DATA->cancelCallbacks[i] = cancelCallbacks[i];
	}
	MenuList_DATA->options[count] = MenuList_ENDMENU;
}

void menuList_destroy() {
	if (MenuList_DATA == NULL) {
		return;
	}
	MEM_free(MenuList_DATA->options);
	MEM_free(MenuList_DATA->acceptCallbacks);
	MEM_free(MenuList_DATA->cancelCallbacks);
	MEM_free(MenuList_DATA);
	MenuList_DATA = NULL;
}

void menuList_setOnRepaintFunction(MenuList_RefreshCallback function) {
	if (MenuList_DATA == NULL) {
		return;
	}
	MenuList_DATA->refreshCallback = function;
}

void menuList_refresh() {
	if (MenuList_DATA == NULL) {
		return;
	}
	MenuList_DATA->refreshCallback(MenuList_DATA->selected, MenuList_DATA->options, MenuList_DATA->info);
}

void menuList_up() {
	if (MenuList_DATA == NULL) {
		return;
	}
	if (MenuList_DATA->selected < 1) {
		MenuList_DATA->selected = 0;
	} else {
		MenuList_DATA->selected -= 1;
	}
}

void menuList_down() {
	if (MenuList_DATA == NULL) {
		return;
	}
	MenuList_DATA->selected += 1;
	if (MenuList_DATA->options[MenuList_DATA->selected] == MenuList_ENDMENU) {
		MenuList_DATA->selected -=1;
	}
}

void menuList_accept() {
	if (MenuList_DATA == NULL) {
		return;
	}
	executeEventCallback(MenuList_DATA->acceptCallbacks[MenuList_DATA->selected], MenuList_DATA->options[MenuList_DATA->selected]);
}

void menuList_cancel() {
	if (MenuList_DATA == NULL) {
		return;
	}
	executeEventCallback(MenuList_DATA->cancelCallbacks[MenuList_DATA->selected], MenuList_DATA->options[MenuList_DATA->selected]);
}

void executeEventCallback(MenuList_EventCallback f, u8 value) {
	if (MenuList_DATA == NULL) {
		return;
	}
	if (f) {
		f(value);
	}
}

