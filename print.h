#pragma once
#include "general.h"
#include "entity.h"
#include "board.h"
#include "colors.h"
using namespace std;


void fixed_splash() {
	cout << " _____ _             ____                          ____" << endl;
	cout << "|_   _| |__   ___   / ___| __ _ _ __ ___   ___    / ___|  ___  _ __" << endl;
	cout << "  | | | '_ \\ / _ \\ | |  _ / _` | '_ ` _ \\ / _ \\   \\___ \\ / _ \\| '_ \\" << endl;
	cout << "  | | | | | |  __/ | |_| | (_| | | | | | |  __/_   ___) | (_) | | | |_" << endl;
	cout << "  |_| |_| |_|\\___|  \\____|\\__,_|_| |_| |_|\\___( ) |____/ \\___/|_| |_(_)" << endl;
	cout << "                                              |/" << endl;

}


void clear_screen() {
	for (size_t i = 0; i < 70; i++) {
		for (size_t j = 0; j < 370; j++) {
			mvaddch(i, j, ' ');
		}
	}
	refresh();
}

//2d to 1d indexing
void print_board() {
	for (size_t i = 0; i < SIZE_X; i++) {
		for (size_t j = 0; j < SIZE_Y; j++) {
			if (c_x == i  and  c_y == j)
				attron(A_UNDERLINE | A_BOLD);
			int color;
			//Npcs and player will have to have their own unique if's most likely

			color =  mid.at(index(i, j)) | ground.at(index(i, j));
			attron(COLOR_PAIR(cpair(color)));
			mvaddch(i, j, board.at(index(i, j)));
			if (weather.at(index(i, j)) != 0) {
				//TBD handle weather and loot printing
			}
			for (auto k : level_entities) {
				if (size_t(k.x) == i  and  size_t(k.y) == j) {
					attron(COLOR_PAIR(cpair(Steam | ground.at(index(i, j))))); //steam is used to get white fore b/c i repurposed the value of 'Entity' to 'Perma_Fire'
					attron(A_BOLD);
					mvaddch(i, j, k.visual);
				}
			}
			if (size_t(current_player.x) == i and size_t(current_player.y) == j) {
				attron(COLOR_PAIR(cpair(Steam | ground.at(index(i, j)))));//steam is used to get white fore b/c i repurposed the value of 'Entity' to 'Perma_Fire'
				attron(A_BOLD);
				mvaddch(i, j, current_player.visual);
			}

			attroff(COLOR_PAIR(cpair(color)));
			attroff(A_UNDERLINE | A_BOLD);
		}

	}
	refresh();
}
void print_console_in(string);
void print_console_out(string);
void at_cursor(string & n_g, string & n_m, string & n_w, string & n_e, string & n_l, int n_c_x, int n_c_y) {
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
	n_e += "None";
	if (current_player.x == n_c_x and current_player.y == n_c_y) {
		n_e = "Entity: " + current_player.type;
	} else {
		for (auto i : level_entities) {
			if (i.x == n_c_x and i.y == n_c_y) {
				n_e = "Entity: " + i.type;
				hp = i.hp;
				break;
			}
		}
	}
	n_l += "False";
	for (auto i : level_loot) {
		if (i.x == n_c_x and i.y == n_c_y) {
			n_l = "Loot: True";
			hp = "";
			break;
		}
	}
	while (n_e.size() < 19)
		n_e += " ";
	while (n_l.size() < 19)
		n_l += " ";
	while (n_w.size() < 19)
		n_w += " ";
	while (n_m.size() < 19)
		n_m += " ";
	while (n_g.size() < 19)
		n_g += " ";
	while (hp .size() < 19)
		hp += " ";


}
void print_editor_help_menu() {


}




void print_editor_controls() {
	attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
	mvprintw(10, SIZE_Y + 2, "**Editor Mode Enabled**");
	mvprintw(13, SIZE_Y + 2, "Enter H to bring up help menu");
	mvprintw(14, SIZE_Y + 2, "The following keys will set the spot the cursor is on to that type");
	mvprintw(15, SIZE_Y + 2, "Ground types: d = Dirt | g = Grass | R = Stone | L = Lava | V = Void | W = Deep Water");
	string printer = "Mid types: " + string(1, Wall_char) + " = Wall | " + string(1, Smoke_char) + " = Smoke | S = Steam | p = Poison | ^ = Fire | + = Tree";
	mvprintw(16, SIZE_Y + 2, printer.c_str());
	printer = "           o = Oil | O = Ooze | b = Blood | w = Water | x = Caltrops | r = Rock | - = Door";
	mvprintw(17, SIZE_Y + 2, printer.c_str());
	printer = "Weather types:";
	mvprintw(18, SIZE_Y + 2, printer.c_str());
	mvprintw(19, SIZE_Y + 2, "Adding entities: ");
	mvprintw(20, SIZE_Y + 2, "Q = Player(1 recomended) | 1 = EyeBall");
	mvprintw(22, SIZE_Y + 2, "Enter c to clear mid, C to clear all, and ? to clear entire board");
	mvprintw(23, SIZE_Y + 2, "Enter \"`\" to link maps, formatted: \"name adjacent_x adjacent_y\"");
	mvprintw(24, SIZE_Y + 2, "Enter ~ to enter a back link (the previous map) | Enter ] to load a forward link and [ for back");
	mvprintw(25, SIZE_Y + 2, "Enter N to name the map,  \"|\" to save the map, \"m\" to modify an entity");
	printer = "Debug info: " + to_string(level_entities.size());
	mvprintw(27, SIZE_Y + 2, printer.c_str());
	printer = "                                                            ";
	if (linked.size() == 0)
		printer = "Back link: " + back_link;
	mvprintw(28 + linked.size() , SIZE_Y + 2, printer.c_str());
	for (size_t i = 0; i < linked.size(); i++) {
		printer = "Link " + to_string(i) + ": " + linked.at(i);
		if (i == 0)
			printer += " | Back link: " + back_link;
		mvprintw(28 + i, SIZE_Y + 2, printer.c_str());
	}
	attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

}
void debug_window(string message, int x) {

	attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
	string printer = "Debug info: " + message;
	mvprintw(30 + x, SIZE_Y + 2, printer.c_str());
	attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

}
void always_print() {
	print_board();
	attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
	mvprintw(0, SIZE_Y + 2, "Use arrow keys to move the cursor around");
	mvprintw(3, SIZE_Y + 2, "s = Steam |");
	mvprintw(9, SIZE_Y + 2, "Some ground colors may be changed if the item on it is assigned the same color so be concious of it");
	string temp = "Map: " + current_map_name + " |  X: " + to_string(c_x) + " Y: " + to_string(c_y);
	string hp_text;
	while (hp_text.size() < SIZE_Y)
		hp_text += " ";
	while (temp.size() < SIZE_Y)
		temp += " ";
	mvprintw(SIZE_X + 1, 1, temp.c_str());
	mvprintw(SIZE_X + 2, 1, g.c_str());
	mvprintw(SIZE_X + 3, 1, m.c_str());
	mvprintw(SIZE_X + 4, 1, w.c_str());
	mvprintw(SIZE_X + 5, 1, e.c_str());
	mvprintw(SIZE_X + 6, 1, l.c_str());

	mvprintw(12, SIZE_Y + 2, "Controls:");
	attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

	attron(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));
	mvprintw(1, SIZE_Y + 2, "# = Wall | s = Smoke | x = Caltrops |   = Stone");
	attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));

	attron(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_WHITE)));
	mvprintw(1, SIZE_Y + 40, " ");
	attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_WHITE)));

	attron(COLOR_PAIR(cpair(COLOR_MAGENTA, COLOR_BLACK)));
	mvprintw(2, SIZE_Y + 2, "s = Poison | ~ = Ooze | ");
	attroff(COLOR_PAIR(cpair(COLOR_MAGENTA, COLOR_BLACK)));

	attron(COLOR_PAIR(cpair(COLOR_RED, COLOR_BLACK)));
	mvprintw(4, SIZE_Y + 2, "^ = Fire | ~ = Blood |  = Lava");
	attroff(COLOR_PAIR(cpair(COLOR_RED, COLOR_BLACK)));

	attron(COLOR_PAIR(cpair(COLOR_BLUE, COLOR_BLACK)));
	mvprintw(5, SIZE_Y + 2, "- or \"|\" = Door | + = Tree | r = Rock");
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
	for (size_t  i = 0; i <= SIZE_X; i++) {
		mvprintw(i, SIZE_Y, "*");
	}
	for (size_t i = 0; i < SIZE_Y; i++) {
		mvprintw(SIZE_X, i, "*");
	}
	attroff(COLOR_PAIR(cpair(COLOR_YELLOW, COLOR_BLACK)));
	print_console_in(console_input);
	print_console_out(console_output);
	refresh();
}
//returns 1 when continuing to work and 3 if '\n' is read and 2 if the esc key is pressed
int typing(int input) {
	if (isalnum(input) || input == ' ' || input == '_') {
		console_input.push_back(char(input));
		if (console_input.size() > SIZE_Y)
			console_input.pop_back();
		return 1;
	} else if (input == KEY_BACKSPACE) {
		if (console_input.size() > 0) {
			console_input.pop_back();
			console_input.push_back(' ');
			print_console_in(console_input);
			console_input.pop_back();
		}
		return 1;
	} else if (input == '\n') {
		return 2;
	} else if (input == ERR)
		return 1;
	return 0;
}

// should have print_console_in(""); following the call
string type() {
	int c_in = 0;
	while (true) {
		int break_check = false;
		int ch = getch();
		c_in = typing(ch);
		if (c_in == 1)
			;
		else if (c_in == 2) {
			for (auto i : console_input) {
				if (!isalnum(i) || i == ' ') {
					print_console_out("Invalid input");
					print_console_in("");
					break_check = true;
					break;
				}
			}
			if (break_check)break;
			return console_input;
		} else
			break;
		print_console_in(console_input);
		refresh();
	}
	return "";
}
void print_console_in(string input) {
	attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
	for (size_t i = 0; i < console_input.size(); i++)
		console_input.at(i) = ' ';
	mvprintw(SIZE_X + 10 , 1, console_input.c_str());
	console_input = input;
	mvprintw(SIZE_X + 10 , 1, console_input.c_str());
	attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
}



void print_console_out(string output) {
	attron(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));
	for (size_t i = 0; i < console_output.size(); i++) {
		console_output.at(i) = ' ';
	}
	mvprintw(SIZE_X + 9 , 1, console_output.c_str());
	console_output = output;
	mvprintw(SIZE_X + 9 , 1, console_output.c_str());
	attroff(COLOR_PAIR(cpair(COLOR_BLACK, COLOR_WHITE)));
}
