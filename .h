#pragma once
#include "globals.h"
#include "entity.h"
#include "board.h"
using namespace std;

//2d to 1d indexing
void print_board() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (c_x == i  and  c_y == j)
				attron(A_UNDERLINE | A_BOLD);
			int color;
			//Npcs and player will have to have their own unique if's most likely
			color =  mid.at(index(i, j)) | ground.at(index(i, j));
			if (weather.at(index(i, j)) != 0) {
//TBD handle weather and loot printing
			}
			/*for (auto k : level_entities) {
				if (k.x == i  and  k.y == j) {
					color = k.color | ground.at(index(i, j));
					attron(COLOR_PAIR(color));
					mvaddch(i, j, k.visual);

				} else {
				}
			}*/
			attron(COLOR_PAIR(cpair(color)));
			mvaddch(i, j, board.at(index(i, j)));

			attroff(COLOR_PAIR(cpair(color)));
			attroff(A_UNDERLINE | A_BOLD);
		}

	}
}
void at_cursor(string &n_g, string &n_m, string &n_w, string &n_e, string &n_l, int n_c_x, int n_c_y) {
	n_g = "Ground: ";
	n_m = "Mid: ";
	n_w = "Weather: ";
	n_e = "Entity: ";
	n_l = "Loot: ";
	if (ground.at(index(n_c_x, n_c_y)) == Void) {
		n_g += "Void";
	} else if (ground.at(index(n_c_x, n_c_y)) == Dirt) {
		n_g += "Dirt";
	} else if (ground.at(index(n_c_x, n_c_y)) == Grass) {
		n_g += "Grass";
	} else if (ground.at(index(n_c_x, n_c_y)) == Stone) {
		n_g += "Stone";
	} else if (ground.at(index(n_c_x, n_c_y)) == Deep_water) {
		n_g += "Deep water";
	} else if (ground.at(index(n_c_x, n_c_y)) == Lava) {
		n_g += "Lava";
	}
	if (mid.at(index(n_c_x, n_c_y)) == Poison) {
		n_m += "Poison";
	} else if (mid.at(index(n_c_x, n_c_y)) == Rock) {
		n_m += "Rock";
	} else if (mid.at(index(n_c_x, n_c_y)) == Steam) {
		n_m += "Steam";
	} else if (mid.at(index(n_c_x, n_c_y)) == Caltrops) {
		n_m += "Caltrops";
	} else if (mid.at(index(n_c_x, n_c_y)) == Door) {
		n_m += "Door";
	} else if (mid.at(index(n_c_x, n_c_y)) == Water) {
		n_m += "Water";
	} else if (mid.at(index(n_c_x, n_c_y)) == Wall) {
		n_m += "Wall";
	} else if (mid.at(index(n_c_x, n_c_y)) == Tree) {
		n_m += "Tree";
	} else if (mid.at(index(n_c_x, n_c_y)) == Ooze) {
		n_m += "Ooze";
	} else if (mid.at(index(n_c_x, n_c_y)) == Blood) {
		n_m += "Blood";
	} else if (mid.at(index(n_c_x, n_c_y)) == Oil) {
		n_m += "Oil";
	} else if (mid.at(index(n_c_x, n_c_y)) == Fire) {
		n_m += "Fire";
	} else if (mid.at(index(n_c_x, n_c_y)) == 0) {
		n_m += "Empty";
	} else if (mid.at(index(n_c_x, n_c_y)) == Smoke) {
		n_m += "Smoke";
	}
	if (weather.at(index(n_c_x, n_c_y)) == Rain) {
		n_w += "Rain";
	} else if (weather.at(index(n_c_x, n_c_y)) == Sandstorm) {
		n_w += "Sandstorm";
	} else if (weather.at(index(n_c_x, n_c_y)) == Winter_wonderland) {
		n_w += "Snowing";
	} else if (weather.at(index(n_c_x, n_c_y)) == Ash_fall) {
		n_w += "Falling ash";
	} else if (weather.at(index(n_c_x, n_c_y)) == Fog_of_war) {
		n_w += "Fog of war";
	} else {
		n_w += "Clear";
	}
	for (auto i : level_entities) {
		if (i.x == n_c_x and i.y == n_c_y) {
			n_e += i.type;
			break;
		}
	}
	if (n_e.size() <= 18)
		n_e += "None";
	for (auto i : level_loot) {
		if (i.x == n_c_x and i.y == n_c_y) {
			n_l += "True";
			break;
		}
	}
	if (n_l.size() <= 10) {
		n_l += "False";
	}

	//these while loops make sure to put extra spaces to overwrite leftover characters if the string is shorter than a previous one
	while (n_g.size() < 18) {
		n_g += " ";
	}
	while (n_m.size() < 13) {
		n_m += " ";
	}
	while (n_w.size() < 20) {
		n_w += " ";
	}

	//will need to add while loops for space for loot and entities once entities are decided and we have a max length
}

void print_editor_controls(){
			attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
			mvprintw(10, SIZE_Y + 2, "**Editor Mode Enabled**");
			mvprintw(13, SIZE_Y + 2, "The following keys will set the spot the cursor is on to that type");
			mvprintw(15, SIZE_Y + 2, "Ground types: d = Dirt | g = Grass | R = Stone | L = Lava | V = Void | W = Deep Water");
			string printer = "Mid types: " + string(1, Wall_char) + " = Wall | " + string(1, Smoke_char) + " = Smoke | S = Steam | p = Poison | ^ = Fire | + = Tree";
			mvprintw(16, SIZE_Y + 2, printer.c_str());
			printer = "           o = Oil | O = Ooze | b = Blood | w = Water | x = Caltrops | r = Rock | - = Door";
			mvprintw(17, SIZE_Y + 2, printer.c_str());
			mvprintw(19, SIZE_Y + 2, "Enter \"|\" to save the level");
			attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

}


void always_print(){


		attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
		mvprintw(0, SIZE_Y + 2, "Use arrow keys to move the cursor around");
		mvprintw(3, SIZE_Y + 2, "s = Steam |");
		mvprintw(9, SIZE_Y + 2, "Some ground colors may be changed if the item on it is assigned the same color so be concious of it");
		mvprintw(SIZE_X + 1, 1, g.c_str());
		mvprintw(SIZE_X + 2, 1, m.c_str());
		mvprintw(SIZE_X + 3, 1, w.c_str());
		mvprintw(SIZE_X + 4, 1, e.c_str());
		mvprintw(SIZE_X + 5, 1, l.c_str());
		mvprintw(12, SIZE_Y + 2, "Controls:");
		attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));
		mvprintw(1, SIZE_Y + 2, "# = Wall | r  = Rock | s = Smoke | x = Caltrops");
		attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_MAGENTA, COLOR_BLACK)));
		mvprintw(2, SIZE_Y + 2, "s = Poison | ~ = Ooze | ");
		attroff(COLOR_PAIR(cpair(COLOR_MAGENTA, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_RED, COLOR_BLACK)));
		mvprintw(4, SIZE_Y + 2, "^ = Fire | ~ = Blood |  = Lava");
		attroff(COLOR_PAIR(cpair(COLOR_RED, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_BLUE, COLOR_BLACK)));
		mvprintw(5, SIZE_Y + 2, "- or \"|\" = Door | + = Tree");
		attroff(COLOR_PAIR(cpair(COLOR_BLUE, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_CYAN, COLOR_BLACK)));
		mvprintw(6, SIZE_Y + 2, "~ = Water (Puddle) |  = Deep Water (Lake,Ocean,etc)");
		attroff(COLOR_PAIR(cpair(COLOR_CYAN, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));
		mvprintw(7, SIZE_Y + 2, "~ = Oil | ");
		attroff(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));

		attron(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_YELLOW)));
		mvprintw(2, SIZE_Y + 26, " ");
		attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_YELLOW)));

		attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
		mvprintw(2, SIZE_Y + 27, "= Dirt ground");
		attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));
		mvprintw(3, SIZE_Y + 13, "  = Void (Bottemless hole)");
		attroff(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));

		attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
		mvprintw(3, SIZE_Y + 14, " ");
		attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

		attron(COLOR_PAIR(cpair(COLOR_GREEN, COLOR_GREEN)));
		mvprintw(7, SIZE_Y + 12, " ");
		attroff(COLOR_PAIR(cpair(COLOR_GREEN, COLOR_GREEN)));

		attron(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));
		mvprintw(7, SIZE_Y + 13, "= Grass ground");
		attroff(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));

		attron(COLOR_PAIR(cpair(COLOR_CYAN, COLOR_CYAN)));
		mvprintw(6, SIZE_Y + 23, " ");
		attroff(COLOR_PAIR(cpair(COLOR_CYAN, COLOR_CYAN)));

		attron(COLOR_PAIR(cpair(COLOR_RED, COLOR_RED)));
		mvprintw(4, SIZE_Y + 25, " ");
		attroff(COLOR_PAIR(cpair(COLOR_RED, COLOR_RED)));
		attron(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));
		for (int i = 0; i <= SIZE_X; i++) {
			mvprintw(i, SIZE_Y, "*");
		}
		for (int i = 0; i < SIZE_Y; i++) {
			mvprintw(SIZE_X, i, "*");
		}
		attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));
}
