#pragma once
#include "general.h"
#include "entity.h"
using namespace std;


void clear_board() {
	initialize_arrays();
	level_loot.resize(0);
	level_entities.resize(0);
}

void clear_lists_at_cursor() {
	auto i = level_entities.begin();
	while (i != level_entities.end()) {
		if (size_t((*i).x) == c_x and size_t((*i).y) == c_y) {
			level_entities.erase(i++);
		} else ++i;
	}
	auto j = level_loot.begin();
	while (j != level_loot.end()) {
		if (size_t((*j).x) == c_x and size_t((*j).y) == c_y) {
			level_loot.erase(j++);
		} else ++j;
	}
}

void weather_check() {

}
bool is_open(int x, int y, int intellect) {
	if (x<0 or y<0 or size_t(y)>SIZE_Y or size_t(x)>SIZE_X) return false;
	if (mid.at(index(x, y)) == Wall)return false;
	if (mid.at(index(x, y)) == Door)return false;
	if (mid.at(index(x, y)) == Tree)return false;
	if (mid.at(index(x, y)) == Rock)return false;
	if (mid.at(index(x, y)) == Ooze and intellect > 1)return false;
	if (mid.at(index(x, y)) == Fire and intellect > 1)return false;
	if (mid.at(index(x, y)) == Caltrops and intellect > 1)return false;
	if (mid.at(index(x, y)) == Poison and intellect > 1)return false;
	if (ground.at(index(x, y)) == Lava and intellect > 0)return false;
	if (ground.at(index(x, y)) == Deep_water and intellect > 0)return false;
	if (ground.at(index(x, y)) == Void and intellect > 0)return false;
	for (auto i : level_entities)
		if (i.x == x and i.y == y)return false;
	for (auto i : level_loot)
		if (i.x == x and i.y == y)return false;

	if (ground.at(index(x, y)) == Ice and intellect > 2)return true;
	if (ground.at(index(x, y)) == Ice)return false;
	return true;
}

void explosion(int x, int y) {
	mid.at(index(x, y)) = Smoke;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0 ; j < 3 ; j++) {
			if (i != j and (i == 0 or j == 0)) {
				if (mid.at(index(x + (i - 1), y + (j - 1))) == Poison or mid.at(index(x + (i - 1), y + (j - 1))) == Ooze)
					explosion(x + (i - 1), y + (j - 1));
			}
		}
	}
}
//0 means do nothing, 1 means flamable, 2 means explosive, 3 means to steam, 4 means fast fire spread (oil)
int fire_reaction(int x , int y) {
	if (mid.at(index(x, y)) == Water or mid.at(index(x, y)) == Blood)
		return 3;
	else if (mid.at(index(x, y)) == Tree or ((mid.at(index(x, y)) == Smoke or mid.at(index(x, y)) == 0 or mid.at(index(x, y)) == Smoke or mid.at(index(x, y)) == Steam) and ground.at(index(x, y)) == Grass))
		return 1;
	else if (mid.at(index(x, y)) == Oil)
		return 4;
	else if (mid.at(index(x, y)) == Steam and ground.at(index(x, y)) != Grass) {
		return 0;
	} 	else if (mid.at(index(x, y)) == Poison or mid.at(index(x, y)) == Ooze)
		return 2;
	else if (ground.at(index(x, y)) == Void or ground.at(index(x, y)) == Lava or ground.at(index(x, y)) == Deep_water or (mid.at(index(x, y)) == 0 and ground.at(index(x, y)) != Grass)
	         or (mid.at(index(x, y)) == Smoke and ground.at(index(x, y)) != Grass)) {
		return 0;
	} else if (mid.at(index(x, y)) == Rock or mid.at(index(x, y)) == Wall or mid.at(index(x, y)) == Door or mid.at(index(x, y)) == Caltrops or mid.at(index(x, y)) == Fire
	           or mid.at(index(x, y)) == Perma_fire or mid.at(index(x, y)) == 0) {
		return 0;
	} else if (mid.at(index(x, y)) == Fire) {
		return 0;
	}
	string temp = "Missing fire_reaction possibility!   Mid: " + to_string(mid.at(index(x, y))) + " Ground: " + to_string(ground.at(index(x, y)));
	throw runtime_error(temp);
}
void fast_fire(int x , int y) {
	mid.at(index(x, y)) = Perma_fire;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0 ; j < 3 ; j++) {
			if (x >= 0 or y >= 0 or size_t(y) <= SIZE_Y or size_t(x) <= SIZE_X)
				if (diag_allowed || (i != j and (i == 1 or j == 1))) {
					if (mid.at(index(x + (i - 1), y + (j - 1))) == Oil)
						fast_fire(x + (i - 1), y + (j - 1));
				}
		}
	}
}
//only gets called on spots that has fire on it
void fire_spread(int x, int y) {
	if (ground.at(index(x, y)) == Grass) {
		ground.at(index(x, y)) = Dirt;
		mid.at(index(x, y)) = Smoke;
	} else {
		mid.at(index(x, y)) = Smoke;
	}
	try {
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0 ; j < 3 ; j++) {
				if (x >= 0 or y >= 0 or size_t(y) <= SIZE_Y or size_t(x) <= SIZE_X)
					if (diag_allowed || (i != j and (i == 1 or j == 1))) {
						int fire_react = fire_reaction(x + (i - 1), y + (j - 1));
						if (fire_react == 0) {
							;
						} else if (fire_react == 1) {
							mid.at(index(x + (i - 1), y + (j - 1))) = Fire;
						} else if (fire_react == 2) {
							explosion(x + (i - 1), y + (j - 1));
						} else if (fire_react == 3) {
							mid.at(index(x + (i - 1), y + (j - 1))) = Steam;
						} else if (fire_react == 4) {
							fast_fire(x + (i - 1), y + (j - 1));
						}
					}
			}
		}
	} catch (runtime_error e) {
		string temp = e.what();
		temp += "                        ";
		debug_window(temp, 10);
		return;
	}

	for (auto i : level_entities) {
		if (i.x == x and i.y == y) {
			i.temp_burn();
			break;
		}
	}
	if (current_player.x == x and current_player.y == y)
		current_player.temp_burn();
}
void perma_fire_iterate();//same but perma fire so it doesnt go away
void fire_iterate() { //used to make sure the same spot doesnt have the spread pushed onto it multiple times/doesnt call the function on new fire
	set<pair<int, int>> tbd;
	for (size_t j = 0; j < SIZE_Y; j++)
		for (size_t i = 0; i < SIZE_X; i++)
			if (mid.at(index(i, j)) == Fire)
				tbd.insert(pair<int, int>(i, j));
	for (auto i : tbd) {
		fire_spread(i.first, i.second);
	}
}
void place_doors(int x, int y) {
	if (size_t(x + 1) < SIZE_X and x - 1 > 0 and mid.at(index(x + 1, y)) == Wall and mid.at(index(x - 1, y)) == Wall)
		board.at(index(x, y)) = '|';
	else
		board.at(index(x, y)) = '-';
}


//populates board with the correct chars
void board_set() {
	for (size_t i = 0; i < SIZE_X; i++) {
		for (size_t j = 0; j < SIZE_Y; j++) {
			if (mid.at(index(i, j)) ==  Poison) {
				board.at(index(i, j)) =  Poison_char;
			} else if (mid.at(index(i, j)) == Smoke) {
				board.at(index(i, j)) = Smoke_char;
			} else if (mid.at(index(i, j)) == Rock) {
				board.at(index(i, j)) =  Rock_char;
			} else if (mid.at(index(i, j)) == Steam) {
				board.at(index(i, j)) =  Steam_char;
			} else if (mid.at(index(i, j)) == Caltrops) {
				board.at(index(i, j)) =  Caltrops_char;
			} else if (mid.at(index(i, j)) == Door) {
				place_doors(i, j);
			} else if (mid.at(index(i, j)) == Water) {
				board.at(index(i, j)) =  Water_char;
			} else if (mid.at(index(i, j)) == Wall) {
				board.at(index(i, j)) =  Wall_char;
			} else if (mid.at(index(i, j)) == Tree) {
				board.at(index(i, j)) =  Tree_char;
			} else if (mid.at(index(i, j)) == Ooze) {
				board.at(index(i, j)) =  Ooze_char;
			} else if (mid.at(index(i, j)) == Blood) {
				board.at(index(i, j)) = Blood_char;
			} else if (mid.at(index(i, j)) == Oil) {
				board.at(index(i, j)) = Oil_char;
			} else if (mid.at(index(i, j)) == Fire) {
				board.at(index(i, j)) =  Fire_char;
			} else if (mid.at(index(i, j)) == 0) {
				board.at(index(i, j)) = ' ';
			} else if (mid.at(index(i, j)) == Perma_fire) {
				board.at(index(i, j)) = Fire_char;
			}
		}
	}
	for (auto i : level_entities) {
		board.at(index(i.x, i.y)) = i.visual;
	}
	board.at(index(current_player.x, current_player.y)) = current_player.visual;
}




void terrain_on_terrain_check() {
	fire_iterate();
	/*
	 for (size_t y = 0; y < SIZE_Y; y++) {
		for (size_t x = 0; x < SIZE_X; x++) {
			if (mid.at(index(x, y)) == Fire) {
				fire_spread(x, y);
			} else if (ground.at(index(x, y)) == Lava  and (mid.at(index(x, y)) == Poison)) {
				fire_spread(x, y);
			} else if (ground.at(index(x, y)) == Lava  and (mid.at(index(x, y)) == Ooze)) {
				fire_spread(x, y);
			}	else if (ground.at(index(x, y)) == Lava  and (mid.at(index(x, y)) == Tree)) {
				fire_spread(x, y);
			}		else if (ground.at(index(x, y)) == Lava  and (mid.at(index(x, y)) == Oil)) {
				fire_spread(x, y);
			}
			if (ground.at(index(x, y)) == Lava  and (mid.at(index(x, y)) == Water or mid.at(index(x, y)) == Blood)) {
				mid.at(index(x, y)) = Steam;
			}
			if (ground.at(index(x, y)) == Deep_water and mid.at(index(x, y)) == Water) {
				mid.at(index(x, y)) = 0;
			}
		}
	}
	*/
}

void global_entity_checks() {//also checks loot
	auto i = level_entities.begin();
	while (i != level_entities.end()) {
		(*i).status_check();
		(*i).statcheck();
		if ((*i).dead == true) {
			level_entities.erase(i++);
		} else ++i;
	}
	auto j = level_loot.begin();
	while (j != level_loot.end()) {
		if ((*j).is_empty()) {
			level_loot.erase(j++);
		} else ++j;
	}
	if (current_player.hp <= 0)
		;//do something
}



