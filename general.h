#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <exception>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


//things with Clear_ in the name are used to check if the type is empty for a spot ie nothing in the way
//ground values
const int Void = 0;
const int Dirt = 1;
const int Grass = 2;
const int Stone = 4;
const int Deep_water = 8;
const int Lava = 16;


//once ice is fully implemented it should be set up in a way that flickers * over the ice spot to indicate that
//it is ice, probably make a function called ice_visual() or something and put it in a loop with the input stuff while the game is playing
//im thinking that it should probably move across 2 tiles in the time it would take to walk one except you are forced to glide
const int Ice = 16777216;


const int Clear_ground = Ice | Dirt | Grass | Stone | Deep_water | Lava;

//mid values, 0 == clean mid
const int Poison = 32;
const int Smoke = 64;
const int Water = 128;//esentially a puddle
const int Steam = 256;
const int Caltrops = 512;
const int Ooze = 1024;
const int Blood = 2048;
const int Oil = 4096;
const int Fire = 8192;
const int Rock = 16384;
const int Door = 32768;
const int Wall = 65536;
const int Tree = 131072;
const int Perma_fire =  262144;
//const unsigned int Clear_mid = Entity | Fire | Poison | Smoke | Rock | Steam | Caltrops | Door | Water | Wall | Tree | Ooze | Blood | Oil;

//weather values, 0 == clear weather
const int Rain = 1048576;
const int Sandstorm = 2097152;
const int Winter_wonderland = 8388608 ;
const int Ash_fall = 524288;
const int Fog_of_war = 4194304;
//const unsigned int Clear_weather = ;


//Characters to represent each thing
const char Poison_char = 's';
const char Smoke_char = 's';
const char Rock_char = 'r';
const char Steam_char = 's';
const char Caltrops_char = 'x';
const char DoorEW_char = '-';
const char DoorNS_char = '|';
const char Water_char = '~';
const char Wall_char = '#';
const char Tree_char = '+';
const char Ooze_char = '~';
const char Blood_char = '~';
const char Oil_char = '~';
const char Fire_char = '^';
const char Empty = ' ';
//TBD npcs/player



//weapons
//_# indicates enchantment
//most inventories use bitpacking
const unsigned int short_sword =  1;
const unsigned int short_sword_1 = 2;
const unsigned int short_sword_2 = 4;
const unsigned int long_sword = 8;
const unsigned int long_sword_1 = 16;
const unsigned int long_sword_2 = 32;
const unsigned int short_bow = 64;
const unsigned int short_bow_1 = 128;
const unsigned int short_bow_2 = 256;
const unsigned int long_bow = 512;
const unsigned int long_bow_1 = 1024;
const unsigned int long_bow_2 = 2048;
const unsigned int shield = 4096;
const unsigned int shield_1 = 8192;
const unsigned int shield_2 = 16384;
const unsigned int staff = 32768;//enables use of spells
const unsigned int staff_1 = 65536;
const unsigned int staff_2 = 131072;




//armor
const unsigned int cloth = 1;
const unsigned int cloth_1 = 2;
const unsigned int cloth_2 = 4;
const unsigned int leather = 8;
const unsigned int leather_1 = 16;
const unsigned int leather_2 = 32;
const unsigned int chain = 64;
const unsigned int chain_1 = 128;
const unsigned int chain_2 = 256;
const unsigned int plate = 512;
const unsigned int plate_1 = 1024;
const unsigned int plate_2 = 2048;


//msc pots
const unsigned int xp_pot = 1;
const unsigned int half_fire_pot = 2;
const unsigned int full_fire_pot = 4;
const unsigned int full_Lava_pot = 8;
const unsigned int half_poison_pot = 16;
const unsigned int full_poison_pot = 32;
const unsigned int full_stun_pot = 64;
const unsigned int half_pushback_pot = 128;
const unsigned int full_pushback_pot = 256;
const unsigned int half_damage_pot = 512;
const unsigned int full_damage_pot = 1024;


//msc equip
const unsigned int potion_belt = 1 ; //required to hold more than 1 special potion
const unsigned int quivver = 2;


//skills (basically non staff spells) (can be passive)




//spells (require staff)



//status effects
const unsigned int on_fire = 1;
const unsigned int stunned = 2;
const unsigned int poisoned = 4;
const unsigned int bleeding = 8;
const unsigned int hungry = 16;
const unsigned int starving = 32;
const unsigned int god_mode = 64;//may be implemented, maybe not (currently not)

//resistances
const unsigned int half_fire = 1;
const unsigned int full_fire = 2;
const unsigned int full_Lava = 4;
const unsigned int half_poison = 8;
const unsigned int full_poison = 16;
const unsigned int full_stun = 32;
const unsigned int half_pushback = 64;
const unsigned int full_pushback = 128;
const unsigned int half_damage = 256;
const unsigned int full_damage = 512;

unsigned int mode = 0;
const int GAME_MODE = 0;
const int EDITOR_MODE = 1;
bool diag_allowed =  false ;

//current frame
unsigned long long frame = 1;


//ms timeout for input
const unsigned int TIMEOUT = 300;


//board sizes subject to change
//possibly put unsigned longo main for different levels on a per level basis
unsigned long SIZE_X = 10;
unsigned long SIZE_Y = 25;
unsigned long X_MAX = 30;
unsigned long Y_MAX = 60;
unsigned long Y_MIN = 60;
unsigned long X_MIN = 10;
//c coords
unsigned long c_x = 0;
unsigned long c_y = 0;

string current_map_name = "NULL";
vector<string> linked;
string back_link = "NULL";
string console_input;
string console_output;




bool game_on = false;

vector<int> ground;
vector<int> mid;
vector<int> weather;
vector<char> board;




void initialize_arrays() {
	for (size_t i = 0; i < SIZE_Y * SIZE_X; i++) {
		board.at(i) = ' ';
		mid.at(i) = 0;
		ground.at(i) = Dirt;
		weather.at(i) = 0;
	}
}


int index(int x, int y) {
	while (x < 0)x += SIZE_X;
	while (y < 0)y += SIZE_Y;
	if (size_t(x) >= SIZE_X)x %= SIZE_X;
	if (size_t(y) >= SIZE_Y)y %= SIZE_Y;
	return (x * SIZE_Y + y);
}



string g, m, w, e, l, hp; //ground mid weather entity


void wait_ticks(int ticks) {
	clock_t start = clock();
	while ((clock() - start) < ticks)
		; //Do nothing
}







