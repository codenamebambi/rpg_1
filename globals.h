#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <limits.h>
#include <fstream>
#include <sstream>
using namespace std;


//things with Clear_ in the name are used to check if the type is empty for a spot ie nothing in the way
//ground values
const unsigned int Void = 0;
const unsigned int Dirt = 1;
const unsigned int Grass = 2;
const unsigned int Stone = 4;
const unsigned int Deep_water = 8;
const unsigned int Lava = 16;
const unsigned int Clear_ground = Dirt | Grass | Stone | Deep_water | Lava;

//mid values, 0 == clean mid
const unsigned int Poison = 32;
const unsigned int Smoke = 64;
const unsigned int Water = 128;//esentially a puddle
const unsigned int Steam = 256;
const unsigned int Caltrops = 512;
const unsigned int Ooze = 1024;
const unsigned int Blood = 2048;
const unsigned int Oil = 4096;
const unsigned int Fire = 8192;
const unsigned int Rock = 16384;
const unsigned int Door = 32768;
const unsigned int Wall = 65536;
const unsigned int Tree = 131072;
const unsigned int Entity =  262144;
//const unsigned int Clear_mid = Entity | Fire | Poison | Smoke | Rock | Steam | Caltrops | Door | Water | Wall | Tree | Ooze | Blood | Oil;

//weather values, 0 == clear weather
const unsigned int Rain = 1048576;
const unsigned int Sandstorm = 2097152;
const unsigned int Winter_wonderland = 8388608 ;
const unsigned int Ash_fall = 524288;
const unsigned int Fog_of_war = 4194304;
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


//current frame
unsigned long long frame = 1;


//ms timeout for input
const unsigned int TIMEOUT = 300;


//board sizes subject to change
//possibly put into main for different levels on a per level basis
int SIZE_X = 10;
int SIZE_Y = 25;
int X_MAX = 30;
int Y_MAX = 60;
//c coords
int c_x = 0;
int c_y = 0;

bool game_on = false;

vector<int> ground;
vector<int> mid;
vector<int> weather;
vector<char> board;

string g, m, w, e, l; //ground mid weather entity
