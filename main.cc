#include "globals.h"
#include "colors.h"
#include "entity.h"
#include "board.h"
#include "print.h"
#include "save.h"
using namespace std;

const int GAME_MODE = 0;
const int EDITOR_MODE = 1;

void wait_ticks(int ticks) {
	clock_t start = clock();
	while ((clock() - start) < ticks)
		; //Do nothing
}


void initialize_arrays() {
	for (int i = 0; i < SIZE_Y * SIZE_X; i++) {
		board.at(i) = ' ';
		mid.at(i) = 0;
		ground.at(i) = Dirt;
		weather.at(i) = 0;
	}
}

int main() {
	system("clear");
	Map current_map;
	fixed_splash();
	//game mode see consts for modes
	unsigned int mode = 0;

	srand(time(0));
	board.resize(SIZE_X * SIZE_Y);
	mid.resize(SIZE_X * SIZE_Y);
	ground.resize(SIZE_X * SIZE_Y);
	weather.resize(SIZE_X * SIZE_Y);
	initialize_arrays();

	int x, y;
	string user_input;
	cout << "Please enter a mode, either Game or Editor" << endl;
	cin >> user_input;
	while (true) {
		for (int i = 0; i < user_input.size(); i++) {
			user_input.at(i) = toupper(user_input.at(i));
		}
		if (user_input == "GAME") {
			cout << "The game is still in development try again later" << endl;
//			mode=GAME_MODE;
//			break;
		}
		if (user_input == "EDITOR") {
			mode = EDITOR_MODE;
			break;
		} else {
			cout << "Please enter a valid mode" << endl;
			cin >> user_input;
		}
	}
	if (mode == EDITOR_MODE) {
		cout << "Type Load if you are loading an existing map, type New if you are making one from scratch" << endl;
		cin >> user_input;
		while (true) {
			for (int i = 0; i < user_input.size(); i++) {
				user_input.at(i) = toupper(user_input.at(i));
			}
loop_start:
			if (user_input == "LOAD") {
				cout << "Please enter the name of the level you wish to load" << endl;
				cin >> user_input;
				while (true) {
					bool L = false;
					if (user_input == "n" || user_input == "N") {
						user_input = "NEW";
						goto loop_start;
					} else if (user_input == "q" || user_input == "Q") {
						exit(1);
					} else L = Load(user_input);
					if (!L) {
						cout << "Please enter a valid level name, n to make a new level, or type q to quit" << endl;
						cin >> user_input;
					} else {
						break;
					}
				}
				break;
			} else if (user_input == "NEW") {

				cout << "Please enter the board size formatted like so: X_max  Y_Max " << endl;
				cin >> y >> x;

				while (true) {
					if (x < 10  or  y < 25 or !cin) {
						string s;
						cin.clear();
						getline(cin, s);
						cout << "Please Enter Valid maxes (X_min=25, Y_min=10): " << endl;
						cin >> y >> x;

					} else if (x > X_MAX or y > Y_MAX) {
						if (x > Y_MAX) {
							cout << "Over max x length, setting to X_max to max possible" << endl;
							SIZE_X = X_MAX;
						}
						if (y > Y_MAX) {
							cout << "Over max y length, setting to Y_max to max possible" << endl;
							SIZE_Y = Y_MAX;
						}
						break;
					} else {
						SIZE_X = x;
						SIZE_Y = y;
						break;
					}
				}
				board.resize(SIZE_X * SIZE_Y);
				mid.resize(SIZE_X * SIZE_Y);
				ground.resize(SIZE_X * SIZE_Y);
				weather.resize(SIZE_X * SIZE_Y);
				initialize_arrays();
				break;
			} else {
				cout << "Please enter a valid option" << endl;
				cin >> user_input;
			}
		}
	}


	c_x = SIZE_X / 2, c_y = SIZE_Y / 2;

	cout << "Loading..." << endl;
	wait_ticks(2000000);
	initscr();
	start_color();
	initialize_colors();

	noecho();
	cbreak();
	keypad(stdscr, true);
	timeout(TIMEOUT);


//main loop and controls
	while (true) {

		at_cursor(g, m, w, e, l, c_x, c_y);
		always_print();
		if (mode == EDITOR_MODE) {
			print_editor_controls();
		}



		int ch = getch();
		/*else*/ if (ch == KEY_RIGHT) {
			c_y++;
			if (c_y >= SIZE_Y) c_y = SIZE_Y - 1; //Clamp value
		} else if (ch == KEY_LEFT or ch == KEY_SLEFT) {
			c_y--;
			if (c_y < 0) c_y = 0;
		} else if (ch == KEY_UP) {  //Should be KEY_UP, grr
			c_x--;
			if (c_x < 0) c_x = 0;
		} else if (ch == KEY_DOWN) {
			c_x++;
			if (c_x >= SIZE_X) c_x = SIZE_X - 1; //Clamp value
		} else if (ch == ERR) { //No keystroke
			; //Do nothing
		} else if (ch == '\n') {
			game_on = !game_on; //Pause or unpause the game
		}
		if (mode == EDITOR_MODE) {
			if (game_on) {

				attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
				mvprintw(11, SIZE_Y + 2, "**Simulating**");
				attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
				terrain_on_terrain_check();
				wait_ticks(300000);




			} else {
				attron(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));
				mvprintw(11, SIZE_Y + 2, "                     ");
				attroff(COLOR_PAIR(cpair(COLOR_WHITE, COLOR_BLACK)));

				if (ch == Wall_char) {
					mid.at(index(c_x, c_y)) = Wall;
				} else if (ch == Smoke_char) {
					mid.at(index(c_x, c_y)) = Smoke;
				} else if (ch == 'S') {
					mid.at(index(c_x, c_y)) = Steam;
				} else if (ch == 'p') {
					mid.at(index(c_x, c_y)) = Poison;
				} else if (ch == Rock_char) {
					mid.at(index(c_x, c_y)) = Rock;
				} else if (ch == Caltrops_char) {
					mid.at(index(c_x, c_y)) = Caltrops;
				} else if (ch == '-') {
					mid.at(index(c_x, c_y)) = Door;
				} else if (ch == 'w') {
					mid.at(index(c_x, c_y)) = Water;
				} else if (ch == 'W') {
					ground.at(index(c_x, c_y)) = Deep_water;
				} else if (ch == Tree_char) {
					mid.at(index(c_x, c_y)) = Tree;
				} else if (ch == 'O') {
					mid.at(index(c_x, c_y)) = Ooze;
				} else if (ch == 'o') {
					mid.at(index(c_x, c_y)) = Oil;
				} else if (ch == 'b') {
					mid.at(index(c_x, c_y)) = Blood;
				} else if (ch == Fire_char) {
					mid.at(index(c_x, c_y)) = Fire;
				} else if (ch == 'd') {
					ground.at(index(c_x, c_y)) = Dirt;
				} else if (ch == 'g') {
					ground.at(index(c_x, c_y)) = Grass;
				} else if (ch == 'R') {
					ground.at(index(c_x, c_y)) = Stone;
				} else if (ch == 'L') {
					ground.at(index(c_x, c_y)) = Lava;
				} else if (ch == 'V') {
					ground.at(index(c_x, c_y)) = Void;
				} else if (ch == 'v') {
					mid.at(index(c_x, c_y)) = 0;
				} else if (ch == '|') {
					endwin();
					system("clear");
					current_map.Map_set();
					Save(current_map);
					return 0;
				} else if (ch == 'Q') {
					bool check = false;
					for (auto i : level_entities) {
						if (i.x == c_x and i.y == c_y) {
							check = true;
							break;
						}
					}
					if (!check and ground.at(index(c_x, c_y)) < Rock)
						level_entities.push_back(player(c_x, c_y));
				} else if (ch == 'c') {
					mid.at(index(c_x, c_y)) = 0;
					ground.at(index(c_x, c_y)) = Void;
					weather.at(index(c_x, c_y)) = 0;
					auto i = level_entities.begin();
					while (i != level_entities.end()) {
						if ((*i).x == c_x and (*i).y == c_y) {
							level_entities.erase(i++);
						} else ++i;
					}
					auto j = level_loot.begin();
					while (j != level_loot.end()) {
						if ((*j).x == c_x and (*j).y == c_y) {
							level_loot.erase(j++);
						} else ++j;
					}
				}
			}
			board_set();
			print_board();
			refresh();

		}
	}
	endwin();
}

