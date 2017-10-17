#pragma once
#include "globals.h"
#include "entity.h"
#include "functions.h"
using namespace std;



void weather_check() {

}

void fire_spread(int x, int y) {
	if (mid.at(index(x, y)) == Fire and ground.at(index(x, y)) == Grass) {
		ground.at(index(x, y)) = Dirt;
	}
	if (weather.at(index(x, y)) == Rain and mid.at(index(x, y)) == Fire) {
		mid.at(index(x, y)) = Water;
		return;
	} else {
		if (x + 1 <= SIZE_X) {
			if (mid.at(index(x + 1, y)) == Poison) {
				mid.at(index(x + 1, y)) = 0;
				fire_spread(x + 1, y);
			}

			else if (mid.at(index(x + 1, y)) == Tree) {
				mid.at(index(x, y)) = Fire;
				fire_spread(x + 1, y);
			} else if (mid.at(index(x + 1, y)) == Ooze) {
				mid.at(index(x + 1, y)) = 0;
				fire_spread(x + 1, y);
			} else if ((mid.at(index(x + 1, y)) == Water or mid.at(index(x + 1, y)) == Blood) and ground.at(index(x + 1, y)) != Deep_water) {
				mid.at(index(x + 1, y)) = Steam;
			} else if (mid.at(index(x + 1, y)) == Oil) {
				mid.at(index(x + 1, y)) = Fire;
				fire_spread(x + 1, y);
			}
			if (ground.at(index(x + 1, y)) == Grass  and mid.at(index(x + 1, y)) == 0) {
				mid.at(index(x + 1, y)) = Smoke;
				ground.at(index(x + 1, y)) = Dirt;
				fire_spread(x + 1, y);
			}

			else if (ground.at(index(x + 1, y)) == Grass and mid.at(index(x + 1, y)) != Wall and mid.at(index(x + 1, y)) != Door and mid.at(index(x + 1, y)) != Water) {
				ground.at(index(x + 1, y)) = Dirt;
				//fire_spread(x + 1, y);
			}

			else if (ground.at(index(x + 1, y)) == Grass and mid.at(index(x - 1, y)) == Water) {
				mid.at(index(x + 1, y)) = Steam;
			}


		}


		if (x - 1 >= 0) {
			if (mid.at(index(x - 1, y)) == Poison) {
				mid.at(index(x - 1, y)) = 0;
				fire_spread(x - 1, y);
			}

			else if (mid.at(index(x - 1, y)) == Tree) {
				mid.at(index(x, y)) = Fire;
				fire_spread(x - 1, y);
			} else if (mid.at(index(x - 1, y)) == Ooze) {
				mid.at(index(x - 1, y)) = 0;
				fire_spread(x - 1, y);
			} else if ((mid.at(index(x - 1, y)) == Water or mid.at(index(x - 1, y)) == Blood) and ground.at(index(x - 1, y)) != Deep_water) {
				mid.at(index(x - 1, y)) = Steam;
			} else if (mid.at(index(x - 1, y)) == Oil) {
				mid.at(index(x - 1, y)) = Fire;
				fire_spread(x - 1, y);
			}
			if (ground.at(index(x - 1, y)) == Grass  and mid.at(index(x - 1, y)) == 0) {
				mid.at(index(x - 1, y)) = Smoke;
				ground.at(index(x - 1, y)) = Dirt;
				fire_spread(x - 1, y);
			}

			else if (ground.at(index(x - 1, y)) == Grass and mid.at(index(x - 1, y)) != Wall and mid.at(index(x - 1, y)) != Door and mid.at(index(x - 1, y)) != Water) {
				ground.at(index(x - 1, y)) = Dirt;
				//fire_spread(x - 1, y);
			} else if (ground.at(index(x - 1, y)) == Grass and mid.at(index(x - 1, y)) == Water) {
				mid.at(index(x - 1, y)) = Steam;
			}



		}


		if (y + 1 <= SIZE_Y) {
			if (mid.at(index(x, y + 1)) == Poison) {
				mid.at(index(x, y + 1)) = 0;
				fire_spread(x, y + 1);
			}

			else if (mid.at(index(x, y + 1)) == Tree) {
				mid.at(index(x, y + 1)) = Fire;
				fire_spread(x, y + 1);
			} else if (mid.at(index(x, y + 1)) == Ooze) {
				mid.at(index(x, y + 1)) = 0;
				fire_spread(x, y + 1);
			} else if ((mid.at(index(x, y + 1)) == Water or mid.at(index(x, y + 1)) == Blood) and ground.at(index(x, y + 1)) != Deep_water) {
				mid.at(index(x, y + 1)) = Steam;
			} else if (mid.at(index(x, y + 1)) == Oil) {
				mid.at(index(x, y + 1)) = Fire;
				fire_spread(x, y + 1);
			}
			if (ground.at(index(x, y + 1)) == Grass  and mid.at(index(x, y + 1)) == 0) {
				mid.at(index(x, y + 1)) = Smoke;
				ground.at(index(x, y + 1)) = Dirt;
				fire_spread(x, y + 1);
			}

			else if (ground.at(index(x, y + 1)) == Grass and mid.at(index(x, y + 1)) != Wall and mid.at(index(x, y + 1)) != Door and mid.at(index(x, y + 1)) != Water) {
				ground.at(index(x, y + 1)) = Dirt;
				//fire_spread(x, y + 1);
			} else if (ground.at(index(x, y + 1)) == Grass and mid.at(index(x, y + 1)) == Water) {
				mid.at(index(x, y + 1)) = Steam;
			}


		}



		if (y - 1 >= 0) {
			if (mid.at(index(x, y - 1)) == Poison) {
				mid.at(index(x, y - 1)) = 0;
				fire_spread(x, y - 1);
			}

			else if (mid.at(index(x, y - 1)) == Tree) {
				mid.at(index(x, y - 1)) = Fire;
				fire_spread(x, y - 1);
			} else if (mid.at(index(x, y - 1)) == Ooze) {
				mid.at(index(x, y - 1)) = 0;
				fire_spread(x, y - 1);
			} else if ((mid.at(index(x, y - 1)) == Water or mid.at(index(x, y - 1)) == Blood) and ground.at(index(x, y - 1)) != Deep_water) {
				mid.at(index(x, y - 1)) = Steam;
			} else if (mid.at(index(x, y - 1)) == Oil) {
				mid.at(index(x, y - 1)) = Fire;
				fire_spread(x, y - 1);
			} else if (ground.at(index(x, y - 1)) == Grass  and mid.at(index(x, y - 1)) == 0) {
				mid.at(index(x, y - 1)) = Smoke;
				ground.at(index(x, y - 1)) = Dirt;
				fire_spread(x, y - 1);
			}

			else if (ground.at(index(x, y - 1)) == Grass and mid.at(index(x, y - 1)) != Wall and mid.at(index(x, y - 1)) != Door and mid.at(index(x, y - 1)) != Water) {
				ground.at(index(x, y - 1)) = Dirt;
				//fire_spread(x, y - 1);
			} else if (ground.at(index(x, y - 1)) == Grass and mid.at(index(x, y - 1)) == Water) {
				mid.at(index(x, y - 1)) = Steam;
			}



		}

	}
	if (mid.at(index(x, y)) == Entity) {
		for (auto i : level_entities) {
			if (i.x == x and i.y == y) {
				i.temp_burn();
				break;
			}
		}
	}
}
void place_doors(int x, int y) {
	if (x + 1 < SIZE_X and x - 1 > 0 and mid.at(index(x + 1, y)) == Wall and mid.at(index(x - 1, y)) == Wall)
		board.at(index(x, y)) = '|';
	else
		board.at(index(x, y)) = '-';
}


//populates board with the correct chars
void board_set() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
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
				//board.at(index(i, j)) =  DoorNS_char;
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
			}
		}
	}
	for (auto i : level_entities) {
		board.at(index(i.x, i.y)) = i.visual;
	}
}




void terrain_on_terrain_check() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
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
}



