#include "globals.h"
#include "colors.h"
#include "entity.h"
#include "board.h"
#include "print.h"
#include "save.h"
#include "functions.h"
using namespace std;


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
				} else if (ch == '1') {
					entity_push(player(c_x, c_y)); //needs to be entity_push(entity(c_x,c_y))
				} else if (ch == 'Q') {
					current_player.x == c_x;
					current_player.y == c_y;
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
				}
			}
		}
	}
	endwin();
}

