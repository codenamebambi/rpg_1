#pragma once
#include <ncurses.h>
#include "globals.h"
using namespace std;


int pair_count = 0;


void initialize_colors() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			init_pair(pair_count++, j, i);
		}
	}
}
short cpair(short wanted_fore, short wanted_back) {
	short fore, back;
	for (int i = 0; i < pair_count; i++) {
		pair_content(i, &fore, &back);
		if (fore == wanted_fore and back == wanted_back) {
			return i;
		}
	}
}
short cpair(int x) {
	short fore, back;

	if (Void == x) {
		fore = COLOR_BLACK;
		back = COLOR_BLACK;
	} else if (Grass == x) {
		fore = COLOR_GREEN;
		back = COLOR_GREEN;
	} else if (Dirt == x) {
		fore = COLOR_YELLOW;
		back = COLOR_YELLOW;
	} else if (Lava == x) {
		fore = COLOR_RED;
		back = COLOR_RED;
	} else if (Stone == x) {
		fore = COLOR_BLUE;
		back = COLOR_WHITE;
	} else if (Deep_water == x) {
		fore = COLOR_CYAN;
		back = COLOR_CYAN;
	} else if ((Poison |  Grass) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_GREEN;
	} else if ((Rock |  Grass) == x) {
		fore = COLOR_BLUE;
		back = COLOR_GREEN;
	} else if ((Smoke |  Grass) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_GREEN;
	} else if ((Caltrops |  Grass) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_GREEN;
	} else if ((Steam |  Grass) == x) {
		fore = COLOR_WHITE;
		back = COLOR_GREEN;
	} else if ((Door |  Grass) == x) {
		fore = COLOR_BLUE;
		back = COLOR_GREEN;
	} else if ((Water |  Grass) == x) {
		fore = COLOR_BLUE;
		back = COLOR_GREEN;
	} else if ((Wall |  Grass) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_GREEN;
	} else if ((Tree |  Grass) == x) {
		fore = COLOR_BLUE;
		back = COLOR_GREEN;
	} else if ((Ooze |  Grass) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_GREEN;
	} else if ((Blood |  Grass) == x) {
		fore = COLOR_RED;
		back = COLOR_GREEN;
	} else if ((Oil |  Grass) == x) {
		fore = COLOR_BLACK;
		back = COLOR_GREEN;
	} else if ((Fire |  Grass) == x) {
		fore = COLOR_RED;
		back = COLOR_GREEN;
	} else if ((Entity |  Grass) == x) {
		fore = COLOR_WHITE;
		back = COLOR_GREEN;
	} else if ((Poison |  Dirt) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_YELLOW;
	} else if ((Rock |  Dirt) == x) {
		fore = COLOR_BLUE;
		back = COLOR_YELLOW;
	} else if ((Smoke |  Dirt) == x) {
		fore = COLOR_BLUE;
		back = COLOR_YELLOW;
	} else if ((Caltrops |  Dirt) == x) {
		fore = COLOR_BLUE;
		back = COLOR_YELLOW;
	} else if ((Steam |  Dirt) == x) {
		fore = COLOR_WHITE;
		back = COLOR_YELLOW;
	} else if ((Door |  Dirt) == x) {
		fore = COLOR_BLUE;
		back = COLOR_YELLOW;
	} else if ((Water |  Dirt) == x) {
		fore = COLOR_CYAN;
		back = COLOR_YELLOW;
	} else if ((Wall |  Dirt) == x) {
		fore = COLOR_BLUE;
		back = COLOR_YELLOW;
	} else if ((Tree |  Dirt) == x) {
		fore = COLOR_GREEN;
		back = COLOR_YELLOW;
	} else if ((Ooze |  Dirt) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_YELLOW;
	} else if ((Blood |  Dirt) == x) {
		fore = COLOR_RED;
		back = COLOR_YELLOW;
	} else if ((Oil |  Dirt) == x) {
		fore = COLOR_BLACK;
		back = COLOR_YELLOW;
	} else if ((Fire |  Dirt) == x) {
		fore = COLOR_RED;
		back = COLOR_YELLOW;
	} else if ((Entity |  Dirt) == x) {
		fore = COLOR_WHITE;
		back = COLOR_YELLOW;
	} else if ((Poison |  Stone) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_WHITE;
	} else if ((Rock |  Stone) == x) {
		fore = COLOR_BLUE;
		back = COLOR_WHITE;
	} else if ((Smoke |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Caltrops |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Steam |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Door |  Stone) == x) {
		fore = COLOR_BLUE;
		back = COLOR_WHITE;
	} else if ((Water |  Stone) == x) {
		fore = COLOR_CYAN;
		back = COLOR_WHITE;
	} else if ((Wall |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Tree |  Stone) == x) {
		fore = COLOR_BLUE;
		back = COLOR_WHITE;
	} else if ((Ooze |  Stone) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_WHITE;
	} else if ((Blood |  Stone) == x) {
		fore = COLOR_RED;
		back = COLOR_WHITE;
	} else if ((Oil |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Fire |  Stone) == x) {
		fore = COLOR_RED;
		back = COLOR_WHITE;
	} else if ((Entity |  Stone) == x) {
		fore = COLOR_BLACK;
		back = COLOR_WHITE;
	} else if ((Poison |  Deep_water) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_CYAN;
	} else if ((Rock |  Deep_water) == x) {
		fore = COLOR_BLUE;
		back = COLOR_CYAN;
	} else if ((Smoke |  Deep_water) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_CYAN;
	} else if ((Caltrops |  Deep_water) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_CYAN;
	} else if ((Steam |  Deep_water) == x) {
		fore = COLOR_WHITE;
		back = COLOR_CYAN;
	} else if ((Door |  Deep_water) == x) {
		fore = COLOR_BLUE;
		back = COLOR_CYAN;
	} else if ((Water |  Deep_water) == x) {
		fore = COLOR_CYAN;
		back = COLOR_CYAN;
	} else if ((Wall |  Deep_water) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_CYAN;
	} else if ((Tree |  Deep_water) == x) {
		fore = COLOR_BLUE;
		back = COLOR_CYAN;
	} else if ((Ooze |  Deep_water) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_CYAN;
	} else if ((Blood |  Deep_water) == x) {
		fore = COLOR_RED;
		back = COLOR_CYAN;
	} else if ((Oil |  Deep_water) == x) {
		fore = COLOR_BLACK;
		back = COLOR_CYAN;
	} else if ((Fire |  Deep_water) == x) {
		fore = COLOR_RED;
		back = COLOR_CYAN;
	} else if ((Entity |  Deep_water) == x) {
		fore = COLOR_WHITE;
		back = COLOR_RED;
	} else if ((Poison |  Lava) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_RED;
	} else if ((Rock |  Lava) == x) {
		fore = COLOR_BLUE;
		back = COLOR_RED;
	} else if ((Smoke |  Lava) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_RED;
	} else if ((Caltrops |  Lava) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_RED;
	} else if ((Steam |  Lava) == x) {
		fore = COLOR_WHITE;
		back = COLOR_RED;
	} else if ((Door |  Lava) == x) {
		fore = COLOR_BLUE;
		back = COLOR_RED;
	} else if ((Water |  Lava) == x) {
		fore = COLOR_CYAN;
		back = COLOR_RED;
	} else if ((Wall |  Lava) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_RED;
	} else if ((Tree |  Lava) == x) {
		fore = COLOR_BLUE;
		back = COLOR_RED;
	} else if ((Ooze |  Lava) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_RED;
	} else if ((Blood |  Lava) == x) {
		fore = COLOR_RED;
		back = COLOR_RED;
	} else if ((Oil |  Lava) == x) {
		fore = COLOR_BLACK;
		back = COLOR_RED;
	} else if ((Fire |  Lava) == x) {
		fore = COLOR_RED;
		back = COLOR_RED;
	} else if ((Entity |  Lava) == x) {
		fore = COLOR_WHITE;
		back = COLOR_RED;
	} else if ((Poison |  Void) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_BLACK;
	} else if ((Rock |  Void) == x) {
		fore = COLOR_BLUE;
		back = COLOR_BLACK;
	} else if ((Smoke |  Void) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_BLACK;
	} else if ((Caltrops |  Void) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_BLACK;
	} else if ((Steam |  Void) == x) {
		fore = COLOR_WHITE;
		back = COLOR_BLACK;
	} else if ((Door |  Void) == x) {
		fore = COLOR_BLUE;
		back = COLOR_BLACK;
	} else if ((Water |  Void) == x) {
		fore = COLOR_CYAN;
		back = COLOR_BLACK;
	} else if ((Wall |  Void) == x) {
		fore = COLOR_YELLOW;
		back = COLOR_BLACK;
	} else if ((Tree |  Void) == x) {
		fore = COLOR_BLUE;
		back = COLOR_BLACK;
	} else if ((Ooze |  Void) == x) {
		fore = COLOR_MAGENTA;
		back = COLOR_BLACK;
	} else if ((Blood |  Void) == x) {
		fore = COLOR_RED;
		back = COLOR_BLACK;
	} else if ((Oil |  Void) == x) {
		fore = COLOR_BLACK;
		back = COLOR_BLACK;
	} else if ((Fire |  Void) == x) {
		fore = COLOR_RED;
		back = COLOR_BLACK;
	} else if ((Entity |  Void) == x) {
		fore = COLOR_WHITE;
		back = COLOR_BLACK;
	}
	cpair(fore, back);
}


