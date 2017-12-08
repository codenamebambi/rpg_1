#include "general.h"
#include "colors.h"
#include "entity.h"
#include "board.h"
#include "print.h"
#include "save.h"
using namespace std;


void startup() {
	int x, y;
	string user_input;
	cout << "Please enter a mode, either Game or Editor" << endl;
	cin >> user_input;
	while (true) {
		for (size_t i = 0; i < user_input.size(); i++) {
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
			for (size_t i = 0; i < user_input.size(); i++) {
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
				cin >> x >> y;

				while (true) {
					if (size_t (y) < Y_MIN  or  size_t(x) < X_MIN or !cin) {
						string s;
						cin.clear();
						getline(cin, s);
						cout << "Please Enter Valid maxes (X_MIN=" + to_string(X_MIN) + "," + " Y_MIN=" + to_string(Y_MIN) + "):"   << endl;
						cin >> x >> y;

					} else if (size_t(x) > X_MAX or  size_t(y) > Y_MAX) {
						if (size_t(x) > X_MAX) {
							cout << "Over max x length, setting to X_max to max possible" << endl;
							x = X_MAX;
						}
						if (size_t(y) > Y_MAX) {
							cout << "Over max y length, setting to Y_max to max possible" << endl;
							y = Y_MAX;
						}
						break;
					} else {
						break;
					}
				}
				SIZE_X = x;
				SIZE_Y = y;
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
}



int main() {

	Map current_map;
	srand(time(0));
	board.resize(SIZE_X * SIZE_Y);
	mid.resize(SIZE_X * SIZE_Y);
	ground.resize(SIZE_X * SIZE_Y);
	weather.resize(SIZE_X * SIZE_Y);
	initialize_arrays();


	system("clear");
	fixed_splash();
	startup();

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
		board_set();
		always_print();
		if (mode == EDITOR_MODE) {
			print_editor_controls();
		}



		int ch = getch();
		/*else*/ if (ch == KEY_RIGHT) {
			c_y++;
			if (c_y >= SIZE_Y) c_y --; //Clamp value
		} else if (ch == KEY_LEFT or ch == KEY_SLEFT) {
			if (!(c_y == 0))
				c_y--;
		} else if (ch == KEY_UP) {
			if (!(c_x == 0))
				c_x--;
		} else if (ch == KEY_DOWN) {
			c_x++;
			if (c_x >= SIZE_X) c_x --;
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
				for (auto && i : level_entities) {
					i.move(i.astar(current_player.x, current_player.y, 1));
					//i.move_rand();
				}



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
					if (current_map.name.size() < 1)print_console_out("Please enter a valid map name");
					current_map.Map_set();
					Save(current_map);
				} else if (ch == '1') {
					entity_push(entity(c_x, c_y)); //needs to be entity_push(entity(c_x,c_y))
				} else if (ch == 'Q') {
					current_player.x = c_x;
					current_player.y = c_y;
				} else if (ch == 'C') {
					mid.at(index(c_x, c_y)) = 0;
					ground.at(index(c_x, c_y)) = Void;
					weather.at(index(c_x, c_y)) = 0;
					clear_lists_at_cursor();
				} else if (ch == 'c') {
					mid.at(index(c_x, c_y)) = 0;
					clear_lists_at_cursor();
				} else if (ch == '`') {
					modify_map_links();
				} else if (ch == '~') {
					modify_back_link();
				} else if (ch == 'N') {
					modify_map_name();
				} else if (ch == KEY_BACKSPACE) {
					remove_link();
				} else if (ch == 'H') {
					print_editor_help_menu();
				} else if (ch == '2') {
					entity_push(eyeball(c_x, c_y));
				} else if (ch == '?') {
					clear_board();
				} else if (ch == 'm') {
					modify_entity(c_x, c_y);
				} else if (ch == '[') {
					string temp =  back_link;
					if (!Load(temp)) {
						print_console_out("Failed to load back link");
					}
				} else if (ch == ']') {
					print_console_out("Please enter a link index");
					string temp = type();
					print_console_in("");
					string temp2;
					bool check = true;
					for (auto i : temp)
						if (! isdigit(i)) {
							print_console_out("Not a valid index");
							check = false;
						}
					try {
						int index = stoi(temp);
						temp2 = linked.at(index);
					} catch (out_of_range e) {
						print_console_out("Not a valid index");
						check = false;
						debug_window(e.what(), 5);
					}
					if (check) {
						for (size_t i = 0 ; i < temp2.size(); i++)
							if (temp2.at(i) == ' ') {
								temp2.resize(i);
								break;
							}

						if (!Load(temp2)) {
							debug_window(temp2, 1);
							print_console_out("Not a valid link, check details");
						}
					}
				}
			}
		}
	}
	endwin();
}

