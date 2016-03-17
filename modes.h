#ifndef _MODES
#define _MODES

#include <allegro.h>
#include <string>
#include "selectscreen.h"
#include "inventory.h"

void ModeA(Inventory& it); //Provides user keyboard options for Mode A
void ModeB(Inventory& it); //Provides user keyboard options for Mode B
void ModeC(Inventory& it); //Provides user keyboard options for Mode C
void ModeD(Inventory& it); //Provides user keyboard options for Mode D
void ModeE(Inventory& it, bool& keydown); //Provides user keyboard options for Mode E

#endif