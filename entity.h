#pragma once
#include "general.h"
#include "colors.h"
using namespace std;
int index(int, int);
void print_board();
void debug_window(string , int) ;

bool checkIfPlayer(int x , int y);

class Node {
  public:
	int x = 0;
	int y = 0;
	double to_target;
	double fromStart;
	int prevx = 0;
	int prevy = 0;
	Node(int new_x, int new_y, double new_to_target, double new_fromStart, int new_prevx, int new_prevy) {
		this->x = new_x;
		this->y = new_y;
		this->to_target = new_to_target;
		this->fromStart = new_fromStart;
		this->prevx = new_prevx;
		this->prevy = new_prevy;
	}
	Node() {}
	friend bool operator<(const Node &lhs, const Node &rhs) {
		return lhs.to_target + lhs.fromStart > rhs.to_target + rhs.fromStart;
	}
	friend bool operator==(const Node &lhs, const Node &rhs) {
		if (lhs.x == rhs.x and lhs.y == rhs.y and lhs.to_target == rhs.to_target and lhs.fromStart == rhs.fromStart and lhs.prevx == rhs.prevx and lhs.prevy == rhs.prevy)return true;
		else return false;
	}
	Node operator=(const Node &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->to_target = rhs.to_target;
		this->fromStart = rhs.fromStart;
		this->prevx = rhs.prevx;
		this->prevy = rhs.prevy;
		return *this;
	}
	bool passedisPrevious(Node temp) {
		if (this->prevx == temp.x and this->prevy == temp.y)
			return true;
		else return false;
	}
};



bool lookup(int x, int y, multiset<Node> & set, vector<Node> & vec) {
	for (auto i : vec)
		if (i.x == x and i.y == y)return true;
	for (auto i : set)
		if (i.x == x and i.y == y)return true;
	return false;

}


class entity;
class loot;
class player;
list<entity> level_entities;
list<loot> level_loot;
//doesnt check for entities
bool is_open(int, int, int);


class loot {
  public:
	char visual = '$';
	short color = COLOR_YELLOW;
	int x = 0;
	int y = 0;
	unsigned int arrows = 0;
	unsigned int potions = 0;
	unsigned int weapons = 0;
	unsigned int armor = 0;
	unsigned int msc_inventory = 0;
	unsigned int msc_pots = 0;
	unsigned int mana_pots = 0;
	unsigned int food = 0;
	unsigned int good_food = 0;
	unsigned int bandages = 0;
	unsigned int weak_food = 0;
	bool key = false;
	void clear() {
		this->potions = 0;
		this->weapons = 0;
		this->armor = 0;
		this->msc_inventory = 0;
		this->mana_pots = 0;
		this->food = 0;
		this->good_food = 0;
		this->bandages = 0;
		this->weak_food = 0;
	}
	bool is_empty() {
		if (arrows > 0)return false;
		else if (potions > 0)return false;
		else if (weapons > 0)return false;
		else if (armor > 0)return false;
		else if (msc_inventory > 0)return false;
		else if (msc_pots > 0)return false;
		else if (mana_pots > 0)return false;
		else if (food > 0)return false;
		else if (good_food > 0)return false;
		else if (bandages > 0)return false;
		else if (weak_food > 0) return false;
		else if (key)return false;
		else return true;
	}
	loot & operator=(const loot& rhs) {
		this->arrows = rhs.arrows  ;
		this->potions = rhs.potions  ;
		this->weapons = rhs.weapons  ;
		this->armor = rhs.armor  ;
		this->msc_inventory = rhs.msc_inventory  ;
		this->msc_pots = rhs.msc_pots  ;
		this->mana_pots = rhs.mana_pots  ;
		this->food = rhs.food  ;
		this->good_food = rhs.good_food  ;
		this->bandages = rhs.bandages  ;
		this->weak_food = rhs.weak_food  ;
		this->key = rhs.key;
		this->x = rhs.x;
		this->y = rhs.y;
		this->visual = rhs.visual;
		this->color = rhs.color;
		return *this;
	}
	friend bool operator<(const loot &lhs, const loot &rhs) {
		return lhs.color < rhs.color;
	}
	friend ostream& operator<<(ostream& os, const loot &rhs) {
		os << rhs.arrows << endl;
		os << rhs.potions << endl;
		os << rhs.weapons << endl;
		os << rhs.armor << endl;
		os << rhs.msc_inventory << endl;
		os << rhs.msc_pots << endl;
		os << rhs.mana_pots << endl;
		os << rhs.food << endl;
		os << rhs.good_food << endl;
		os << rhs.bandages << endl;
		os << rhs.weak_food << endl;
		os << rhs.key << endl;
		os << rhs.x << endl;
		os << rhs.y << endl;
		os << rhs.visual << endl;
		os << rhs.color << endl;
		return os;
	}
	friend istream& operator>>(istream& is, loot &rhs) {
		is >> rhs.arrows;
		is >> rhs.potions;
		is >> rhs.weapons;
		is >> rhs.armor;
		is >> rhs.msc_inventory;
		is >> rhs.msc_pots;
		is >> rhs.mana_pots;
		is >> rhs.food;
		is >> rhs.good_food;
		is >> rhs.bandages;
		is >> rhs.weak_food;
		is >> rhs.key;
		is >> rhs.x;
		is >> rhs.y;
		is >> rhs.visual;
		is >> rhs.color;
		return is;
	}


};


class chest: public loot {

};
//entity and player classes
//most,if not all, will inherit from entity class

class entity {
  public:
	string type = "Template";
	char visual = 'P';
	int x = 0; //position
	int y = 0;
	entity() {}
	entity(int new_x, int new_y): x(new_x), y(new_y) {}
	int color = COLOR_WHITE;
	//see const values for possible inclusions to each of the following
	unsigned int status = 0; //status effects like sleeping, stun, etc
	unsigned int resistance = 0; //status resistances like fire, poison, etc
	unsigned int weapon_inventory = 0; //weapon inventory
	unsigned int armor_inventory = 0; //armor inventory
	unsigned int current_weapon = 0; //current weapon (no dual weilding unless with shield)
	unsigned int current_armor = 0; //current armor
	unsigned int msc_inventory = 0; //necklaces, rings, etc
	unsigned int spells = 0; //learned spells
	unsigned int skills = 0; //learned skills

	loot drops;

	//number of potions held;
	unsigned int potions = 0; //restores hp upon use
	unsigned int mana_pots = 0; //restores mana upon use
	unsigned int weak_food = 0; //hunger -25
	unsigned int food = 0; //hunger -50
	unsigned int good_food = 0; //hunger -100
	unsigned int msc_pots = 0; //fire resistance etc, max 1 each, can only hold 1 total if no potion belt

	//msc
	unsigned int arrows = 0;//max of 5 unless quivver iin msc inventory
	unsigned int bandages = 0;
	bool has_key = false;
	int turns_poisoned = 0;
	int turns_on_fire = 0;


	//stats
	bool dead = false;
	int intellect = 0;
	unsigned int current_attack = 1;
	unsigned int current_defense = 1;
	double attack_mod = 1;
	unsigned int evasivness = 0;
	unsigned int accuracy = 0;
	unsigned int hp_max = 100;
	unsigned int mana_max = 50;
	unsigned int hunger = 0; //if accumulates to 100(max) you start losing 1hp each turn, does not apply to npc
	unsigned int mana = 0; //used for spells
	unsigned int hp = 1; //if drops to 0 you die
	unsigned int level = 1; //entity's level
	unsigned int range = 1; //attack range if applicable
	unsigned int xp = 0; //current xp, resets upon leveling
	unsigned int level_up_xp = 100; //threshhold required to level up, increase 1.5x every level
	virtual bool attack(entity &target) {
		if (this->accuracy > target.evasivness * .75) {
			target.hp -= this->current_attack;
			return true;
		} else return false;
	}
	void status_check() {
		if (this->status & on_fire) {
			this->Burn();
		}
		if (this->status & poisoned) {
			this->Poisoned();
		}
		if (this->status & bleeding) {
			this->Bleeding();
		}
	}
	void Burn() {
		if (this->turns_on_fire <= 5  and  this->status & on_fire) {
			this->turns_on_fire++;
			double x = 1;
			if (this->resistance & full_fire)
				return;
			else if (this->resistance & half_fire)
				x = .5;
			this->hp -= 6 * x;
		} else {
			this->turns_on_fire = 0;
			this->status ^= on_fire;
		}
	}
	void temp_burn() {
		double x = 1;
		if (this->resistance & full_fire)
			return;
		else if (this->resistance & half_fire)
			x = .5;
		this->hp -= 6 * x;
	}
	void Poisoned() {
		if (this->turns_poisoned <= 8  and  this->status & poisoned) {
			this->turns_poisoned++;
			double x = 1;
			if (this->resistance & full_poison)
				return;
			else if (this->resistance & half_poison)
				x = .5;
			this->hp -= 6 * x;
		} else {
			this->turns_poisoned = 0;
			this->resistance ^= half_poison | full_poison;
			this->status ^= poisoned;
		}
	}
	void Bleeding() {
		if (this->status & bleeding) {
			this->hp -= hp_max * .05;
		}
	}
	bool apply_bandage() {
		if (this->bandages >= 1) {
			this->status ^= bleeding;
			return true;
		} else return false;
	}
	virtual void statcheck() {
		if (this->xp >= this->level_up_xp) {
			this->level++;
			this->level_up_stat_change();
			this->xp -= this->level_up_xp;
			this->level_up_xp = this->level_up_xp * 1.5;
		}
		if (hp <= 0) {
			this->dead = true;
		}
		if (this->hunger == 100) {
			hp--;
		}
		//if hunger isnt in the half closer to starving, hp+1 every turn
		if (this->hunger < 50  and  this->hp < this->hp_max) {
			hp++;
		}
		//if hunger isnt 100 but is in the half closer to starving hp goes up by one every other turn
		if (this->hunger < 100  and  this->hunger >= 50  and  frame % 2 == 0  and  this->hp < this->hp_max) {
			hp++;
		}
		this->hunger++;
		current_attack_check();
		current_defense_check();
	}
	void item_pickup(loot &drop) {
		this->potions += drop.potions;
		this->mana_pots += drop.mana_pots;
		this->weapon_inventory |= drop.weapons;
		this->armor_inventory |= drop.armor;
		this->msc_inventory |= drop.msc_inventory;
		this->food += drop.food;
		this->good_food += drop.good_food;
		this->bandages += drop.bandages;
		this->weak_food += drop.weak_food;
		if (this->has_key == false)
			this->has_key = drop.key;
		int temp_arrows = this->arrows;
		this->arrows += drop.arrows;
		if (this->msc_inventory & quivver  and  this -> arrows > 5)
			this->arrows = 5;
		drop.arrows -= this->arrows - temp_arrows;
		int temp_pots = this->msc_pots;
		if (this->msc_pots > 0  and  this->msc_inventory & potion_belt) {
			;//do nothing
		} else {
			this->msc_pots |= drop.msc_pots;
			drop.msc_pots = temp_pots & drop.msc_pots;
		}
		drop.clear();
	}
	virtual void current_attack_check() {

	}
	virtual void current_defense_check() {
	}
	virtual void level_up_stat_change() {
	}
	/*		void weapon_equip(int new_weapon) {
			}
			void armor_equip(int new_armor) {
			}
			*/
	virtual void terrain_check() {
	}
	void move(int direction) {
		//if (direction == -1)debug_window("not working", 0);
		if (direction == KEY_LEFT) {
			if (this->y - 1 >= 0 and !checkIfPlayer(this->x, this->y - 1)) {
				if (mid.at(index(this->x, this->y - 1)) < Rock) {
					for (auto i : level_entities) {
						if (i.x == this->x && i.y == this->y - 1) {
							y++;
						}
					}
					this->y--;
				}
			}
		}
		if (direction == KEY_RIGHT) {
			if (size_t(this->y + 1) <= SIZE_Y  and !checkIfPlayer(this->x, this->y + 1)) {
				if (mid.at(index(this->x, this->y + 1)) < Rock) {
					for (auto i : level_entities) {
						if (i.x == this->x && i.y == this->y + 1) {
							y--;
						}
					}
					this->y++;
				}
			}
		}
		if (direction == KEY_DOWN) {
			if (this->x + 1 >= 0 and !checkIfPlayer(this->x + 1, this->y)) {
				if (mid.at(index(this->x + 1, this->y)) < Rock) {
					for (auto i : level_entities) {
						if (i.x == this->x + 1 && i.y == this->y) {
							x--;
						}
					}
					this->x++;
				}
			}
		}
		if (direction == KEY_UP) {
			if (size_t(this->x - 1) <= SIZE_X  and !checkIfPlayer(this->x - 1, this->y)) {
				if (mid.at(index(this->x - 1, this->y)) < Rock) {
					for (auto i : level_entities) {
						if (i.x == this->x - 1 && i.y == this->y) {
							x++;
						}
					}
					this->x--;
				}
			}
		}

		if (direction == 'q') {
			if (this->x - 1 >= 0 and this->y >= 0 and !checkIfPlayer(this->x - 1 , this->y - 1))
				if (size_t(this->x - 1) <= SIZE_X and size_t(this->y - 1) <= SIZE_Y and this->y - 1 >= 0 and this->x - 1 >= 0) {
					if (mid.at(index(this->x - 1, this->y - 1)) < Rock) {
						for (auto i : level_entities) {
							if (i.x == this->x - 1 && i.y == this->y - 1) {
								x++;
								y++;
							}
						}
						this->x--;
						this->y--;
					}
				}
		}
		if (direction == 'e') {
			if (this->x - 1 >= 0 and size_t(this->y + 1) <= SIZE_Y and !checkIfPlayer(this->x - 1, this->y + 1))
				if (size_t(this->x - 1) <= SIZE_X and size_t(this->y + 1) <= SIZE_Y and this->y + 1 >= 0 and this->x - 1 >= 0) {
					if (mid.at(index(this->x - 1, this->y + 1)) < Rock) {
						for (auto i : level_entities) {
							if (i.x == this->x - 1 && i.y == this->y + 1) {
								x++;
								y--;
							}
						}
						this->x--;
						this->y++;
					}
				}
		}
		if (direction == 'z') {
			if (size_t(this->x + 1) <= SIZE_X and !checkIfPlayer(this->x + 1, this->y - 1) and this->y >= 0)
				if (size_t(this->x + 1) <= SIZE_X and size_t(this->y - 1) <= SIZE_Y and this->y - 1 >= 0 and this->x + 1 >= 0) {
					if (mid.at(index(this->x + 1, this->y - 1)) < Rock) {
						for (auto i : level_entities) {
							if (i.x == this->x + 1 && i.y == this->y - 1) {
								x--;
								y++;
							}
						}
						this->x++;
						this->y--;
					}
				}
		}
		if (direction == 'x') {
			if (size_t(this->x + 1) <= SIZE_X and !checkIfPlayer(this->x + 1, this->y + 1) and size_t(this->y + 1) <= SIZE_Y)
				if (size_t(this->x + 1) <= SIZE_X and size_t(this->y + 1) <= SIZE_Y and this->y + 1 >= 0 and this->x + 1 >= 0) {
					if (mid.at(index(this->x + 1, this->y + 1)) < Rock) {
						for (auto i : level_entities) {
							if (i.x == this->x + 1 && i.y == this->y + 1) {
								x--;
								y--;
							}
						}
						this->x++;
						this->y++;
					}
				}
		}
	}
	void move_rand() {
		int z = rand() % 4;
		if (z == 0) {
			if (this->y - 1 > 0) {
				if (mid.at(index(this->x, this->y - 1)) < Rock) {
					this->y--;
				}
			}
		}
		if (z == 1) {
			if (size_t(this->y + 1) < SIZE_Y) {
				if (mid.at(index(this->x, this->y + 1)) < Rock) {
					this->y++;
				}
			}
		}
		if (z == 2) {
			if (this->x - 1 > 0) {
				if (mid.at(index(this->x - 1, this->y)) < Rock) {
					this->x--;
				}
			}
		}
		if (z == 3) {
			if (size_t(this->x + 1) < SIZE_X) {
				if (mid.at(index(this->x + 1, this->y)) < Rock) {
					this->x++;
				}
			}
		}

	}



	int astar(int target_x, int target_y, int intellect) {
		priority_queue<Node> potential;
		multiset<Node> p;
		vector<Node> visited;
		bool no_route = false;
		int sx = this->x;
		int sy = this->y;
		double from_start = 0;
		double current_distance = sqrt(pow((sx - target_x), 2) + pow((sy - target_y), 2));
		Node current_location;
		potential.push(Node(sx, sy, current_distance, from_start, -1, -1));
		while (true) {
			current_location = potential.top();
			sx = current_location.x;
			sy = current_location.y;
			potential.pop();
			visited.push_back(current_location);
			//ground.at(index(sx, sy)) = Stone;
			if (current_location.x == target_x and current_location.y == target_y)break;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (diag_allowed || (i != j and (i == 1 or j == 1))) {
						if (is_open(sx + (i - 1), sy + (j - 1), intellect)) {
							current_distance = sqrt(pow((sx + (i - 1) - target_x), 2) + pow(sy + (j - 1) - target_y, 2));
							from_start = current_location.fromStart + 1;
							Node temp(sx + (i - 1), sy + (j - 1), current_distance, from_start, sx, sy);
							if (!lookup(sx + (i - 1), sy + (j - 1), p, visited)) {
								//ground.at(index(sx + (i - 1), sy + (j - 1))) = Grass;
								potential.push(temp);
								p.insert(temp);
							}
						}
					}
				}
			}
			if (potential.size() <= 0) {
				no_route = true;
				break;
			}
			print_board();
			//wait_ticks(200000);
		}
		if (no_route) {
			//debug_window("no_route", 10);
			return -1;
		}
		if (current_location.prevx == -1 and current_location.prevy == -1)return -1;
		while (!(current_location.prevx == this->x and current_location.prevy == this->y)) {
			for (auto &i : visited) {
				if (current_location.passedisPrevious(i)) {
					current_location = i;
					//mid.at(index(current_location.x, current_location.y)) = Water;
					break;
				}
			}
			print_board();
		}
		if (this->x - 1 == current_location.x and this->y == current_location.y)
			return KEY_UP;
		else if (this->x + 1 == current_location.x and this->y == current_location.y)
			return KEY_DOWN;
		else if (this->y + 1 == current_location.y and this->x == current_location.x)
			return KEY_RIGHT;
		else if (this->y - 1 == current_location.y and this->x == current_location.x)
			return KEY_LEFT;
		else if (this->y - 1 == current_location.y and this->x - 1 == current_location.x)
			return 'q';
		else if (this->y + 1 == current_location.y and this->x - 1 == current_location.x)
			return 'e';
		else if (this->y - 1 == current_location.y and this->x + 1 == current_location.x)
			return 'z';
		else if (this->y + 1 == current_location.y and this->x + 1 == current_location.x)
			return 'x';
		else return -1;
	}




	entity & operator=(const entity &rhs) {

		this->type = rhs.type;
		this->x = rhs.x  ;
		this->y = rhs.y;
		this->visual = rhs.visual  ;
		this-> color = rhs.color  ;
		this->status = rhs.status  ;
		this->resistance = rhs.resistance  ;
		this->weapon_inventory = rhs.weapon_inventory  ;
		this->armor_inventory = rhs.armor_inventory  ;
		this->current_weapon = rhs.current_weapon  ;
		this->current_armor = rhs.current_armor  ;
		this->msc_inventory = rhs.msc_inventory  ;
		this->spells = rhs.spells  ;
		this->skills = rhs.skills  ;

		this->drops = rhs.drops;

		this->potions = rhs.potions  ;
		this->mana_pots = rhs.mana_pots  ;
		this->weak_food = rhs.weak_food  ;
		this->food = rhs.food  ;
		this->good_food = rhs.good_food  ;
		this->msc_pots = rhs.msc_pots  ;

		this->arrows = rhs.arrows  ;
		this->bandages = rhs.bandages  ;
		this->has_key = rhs.has_key  ;
		this->turns_poisoned = rhs.turns_poisoned  ;
		this->turns_on_fire = rhs.turns_on_fire  ;


		this->dead = rhs.dead  ;
		this->current_attack = rhs.current_attack  ;
		this->current_defense = rhs.current_defense  ;
		this->attack_mod = rhs.attack_mod  ;
		this->evasivness = rhs.evasivness  ;
		this->accuracy = rhs.accuracy  ;
		this->hp_max = rhs.hp_max  ;
		this->mana_max = rhs.mana_max  ;
		this->hunger = rhs.hunger  ;
		this->mana = rhs.mana  ;
		this->hp = rhs.hp  ;
		this->level = rhs.level  ;
		this->range = rhs.range  ;
		this->xp = rhs.xp  ;
		this->level_up_xp = rhs.level_up_xp  ;
		this->intellect = rhs.intellect;
		return *this;

	}
	friend bool operator<(const entity &lhs, const entity &rhs) {
		return lhs.type < rhs.type;
	}
	friend ostream& operator<<(ostream& os, const entity &rhs) {
		os << rhs.type << endl;
		os << rhs.x << endl;
		os << rhs.y << endl;
		os << rhs.visual << endl;
		os << rhs.color << endl;
		os << rhs.status << endl;
		os << rhs.resistance << endl;
		os << rhs.weapon_inventory << endl;
		os << rhs.armor_inventory << endl;
		os << rhs.current_weapon << endl;
		os << rhs.current_armor << endl;
		os << rhs.msc_inventory << endl;
		os << rhs.spells << endl;
		os << rhs.skills << endl;
		os << rhs.drops ;
		os << rhs.potions << endl;
		os << rhs.mana_pots << endl;
		os << rhs.weak_food << endl;
		os << rhs.food << endl;
		os << rhs.good_food << endl;
		os << rhs.msc_pots << endl;
		os << rhs.arrows << endl;
		os << rhs.bandages << endl;
		os << rhs.has_key << endl;
		os << rhs.turns_poisoned << endl;
		os << rhs.turns_on_fire << endl;
		os << rhs.dead << endl;
		os << rhs.current_attack << endl;
		os << rhs.current_defense << endl;
		os << rhs.attack_mod << endl;
		os << rhs.evasivness << endl;
		os << rhs.accuracy << endl;
		os << rhs.hp_max << endl;
		os << rhs.mana_max << endl;
		os << rhs.hunger << endl;
		os << rhs.mana << endl;
		os << rhs.hp << endl;
		os << rhs.level << endl;
		os << rhs.range << endl;
		os << rhs.xp << endl;
		os << rhs.level_up_xp << endl;
		os << rhs.intellect << endl;
		return os;
	}
	friend istream& operator>>(istream& is, entity &rhs) {
		is >> rhs.type;
		is >> rhs.x;
		is >> rhs.y;
		is >> rhs.visual;
		is >> rhs.color;
		is >> rhs.status;
		is >> rhs.resistance;
		is >> rhs.weapon_inventory;
		is >> rhs.armor_inventory;
		is >> rhs.current_weapon;
		is >> rhs.current_armor;
		is >> rhs.msc_inventory;
		is >> rhs.spells;
		is >> rhs.skills;
		is >> rhs.drops;
		is >> rhs.potions;
		is >> rhs.mana_pots;
		is >> rhs.weak_food;
		is >> rhs.food;
		is >> rhs.good_food;
		is >> rhs.msc_pots;
		is >> rhs.arrows;
		is >> rhs.bandages;
		is >> rhs.has_key;
		is >> rhs.turns_poisoned;
		is >> rhs.turns_on_fire;
		is >> rhs.dead;
		is >> rhs.current_attack;
		is >> rhs.current_defense;
		is >> rhs.attack_mod;
		is >> rhs.evasivness;
		is >> rhs.accuracy;
		is >> rhs.hp_max;
		is >> rhs.mana_max;
		is >> rhs.hunger;
		is >> rhs.mana;
		is >> rhs.hp;
		is >> rhs.level;
		is >> rhs.range;
		is >> rhs.xp;
		is >> rhs.level_up_xp;
		is >> rhs.intellect;
		return is;
	}


};
class entity_hostile: public entity {

};
class eyeball: public entity_hostile {
  public:
	eyeball(int new_x, int new_y) {
		x = new_x;
		y = new_y;
		type = "Eye";
		visual = 'o';
		color = COLOR_WHITE;
	}
	eyeball() {
		type = "Eye";
		visual = 'o';
		color = COLOR_WHITE;
	}


};





class player: public entity {
  public:
	char visual = 'Q';
	short color = COLOR_WHITE;
	player(int new_x, int new_y) {
		x = new_x;
		y = new_y;
		type = "You";
	}
	player() {
		type = "You";
	}
	player & operator=(const entity &rhs) {

		this->type = rhs.type;
		this->x = rhs.x  ;
		this->y = rhs.y;
		this->visual = rhs.visual  ;
		this-> color = rhs.color  ;
		this->status = rhs.status  ;
		this->resistance = rhs.resistance  ;
		this->weapon_inventory = rhs.weapon_inventory  ;
		this->armor_inventory = rhs.armor_inventory  ;
		this->current_weapon = rhs.current_weapon  ;
		this->current_armor = rhs.current_armor  ;
		this->msc_inventory = rhs.msc_inventory  ;
		this->spells = rhs.spells  ;
		this->skills = rhs.skills  ;

		this->drops = rhs.drops;

		this->potions = rhs.potions  ;
		this->mana_pots = rhs.mana_pots  ;
		this->weak_food = rhs.weak_food  ;
		this->food = rhs.food  ;
		this->good_food = rhs.good_food  ;
		this->msc_pots = rhs.msc_pots  ;

		this->arrows = rhs.arrows  ;
		this->bandages = rhs.bandages  ;
		this->has_key = rhs.has_key  ;
		this->turns_poisoned = rhs.turns_poisoned  ;
		this->turns_on_fire = rhs.turns_on_fire  ;


		this->dead = rhs.dead  ;
		this->current_attack = rhs.current_attack  ;
		this->current_defense = rhs.current_defense  ;
		this->attack_mod = rhs.attack_mod  ;
		this->evasivness = rhs.evasivness  ;
		this->accuracy = rhs.accuracy  ;
		this->hp_max = rhs.hp_max  ;
		this->mana_max = rhs.mana_max  ;
		this->hunger = rhs.hunger  ;
		this->mana = rhs.mana  ;
		this->hp = rhs.hp  ;
		this->level = rhs.level  ;
		this->range = rhs.range  ;
		this->xp = rhs.xp  ;
		this->level_up_xp = rhs.level_up_xp  ;
		this->intellect = rhs.intellect;
		return *this;

	}
};



player current_player;
bool checkIfPlayer(int x , int y) {
	if (current_player.x == x and current_player.y == y)return true;
	else return false;
}

void entity_push(entity input) {
	bool check_if_occupied = false;
	if (size_t(current_player.x) == c_x and size_t(current_player.y) == c_y)
		check_if_occupied = true;
	else {
		for (auto i : level_entities) {
			if (size_t(i.x) == c_x and size_t(i.y) == c_y) {
				check_if_occupied = true;
				break;
			}
		}
	}
	if (!check_if_occupied and ground.at(index(c_x, c_y)) < Rock)
		level_entities.push_back(input);
}


void print_console_in(string);
void print_console_out(string);
string type();






string modify_entity_sub_1(string stat, string temp) {
	print_console_out("Current " + stat + ": " + temp + " | Please enter a new " + stat + " value");
	string input = type();
	print_console_in("");
	return input;
}

void modify_entity(int x, int y) {
	bool check = false;
	entity editing;
	string current_value;
	if (x == current_player.x or y == current_player.y) {
		editing = current_player;
		check = true;
	} else
		for (auto i : level_entities) {
			if (i.x == x and i.y == y) {
				editing = i;
				check = true;
				break;
			}
		}
	if (!check)return;
	print_console_out("Enter a stat to change");
	string stat = type();
	print_console_in("");
	for (auto &i : stat)
		tolower(i);
	if (stat == "type") {
		string temp =  editing.type;
		string temp2 = modify_entity_sub_1(stat, temp);
		current_value = temp2;
	} else if (stat == "x") {
		string temp = to_string(editing.x);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int x = stoi(temp2);
		if (x < 0) {
			print_console_out("x value too small, setting to 0");
			x = 0;
		} else if (size_t(x) > SIZE_Y) {
			print_console_out("x value too large, setting to X_MAX");
			x = Y_MAX;
		}
		editing.x = x;
		current_value = temp2;
	} else if (stat == "y") {
		string temp = to_string(editing.y);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int x = stoi(temp2);
		if (x < 0) {
			print_console_out("y value too small, setting to 0");
			x = 0;
		} else if (size_t(x) > SIZE_Y) {
			print_console_out("y value too large, setting to Y_MAX");
			x = Y_MAX;
		}
		editing.y = x;
		current_value = temp2;
	} else if (stat == "visual") {
		string temp = to_string(editing.visual);
		string temp2 = modify_entity_sub_1(stat, temp);
		if (temp2.size() != 1) {
			print_console_out("Invalid input");
			return;
		}
		current_value = temp2;
		editing.visual = temp2.at(0);
	} else if (stat == "color") {
		string temp = to_string(editing.color);
		string temp2 = modify_entity_sub_1(stat, temp);
		current_value = temp2;
		if (temp == "black")
			editing.color = COLOR_BLACK;
		else if (temp == "white")
			editing.color = COLOR_WHITE;
		else if (temp == "cyan")
			editing.color = COLOR_CYAN;
		else if (temp == "yellow")
			editing.color = COLOR_YELLOW;
		else if (temp == "blue")
			editing.color = COLOR_BLUE;
		else if (temp == "red")
			editing.color = COLOR_RED;
		else if (temp == "green")
			editing.color = COLOR_GREEN;
		else if (temp == "purple")
			editing.color = COLOR_MAGENTA;
		else return;
	} else if (stat == "status") {
		string temp = to_string(editing.status);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.status = converted;
	} else if (stat == "resistance") {
		string temp = to_string(editing.resistance);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.resistance = converted;
	} else if (stat == "weapon_inventory") {
		string temp = to_string(editing.weapon_inventory);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.weapon_inventory = converted;
	} else if (stat == "armor_inventory") {
		string temp = to_string(editing.armor_inventory);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.armor_inventory = converted;
	} else if (stat == "current_weapon") {
		string temp = to_string(editing.current_weapon);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.current_weapon = converted;
	} else if (stat == "current_armor") {
		string temp = to_string(editing.current_armor);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.current_armor = converted;
	} else if (stat == "msc_inventory") {
		string temp = to_string(editing.msc_inventory);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.msc_inventory = converted;
	} else if (stat == "spells") {
		string temp = to_string(editing.spells);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.spells = converted;
	} else if (stat == "skills") {
		string temp = to_string(editing.skills);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.skills = converted;
	} else if (stat == "potions") {
		string temp = to_string(editing.potions);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.potions = converted;
	} else if (stat == "mana_pots") {
		string temp = to_string(editing.mana_pots);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.mana_pots = converted;
	} else if (stat == "weak_food") {
		string temp = to_string(editing.weak_food);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.weak_food = converted;
	} else if (stat == "food") {
		string temp = to_string(editing.food);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.food = converted;
	} else if (stat == "good_food") {
		string temp = to_string(editing.good_food);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.good_food = converted;
	} else if (stat == "msc_pots") {
		string temp = to_string(editing.msc_pots);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.msc_pots = converted;
	} else if (stat == "arrows") {
		string temp = to_string(editing.arrows);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.arrows = converted;
	} else if (stat == "bandages") {
		string temp = to_string(editing.bandages);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.bandages = converted;
	} else if (stat == "has_key") {
		string temp = "True";
		if (!editing.has_key)temp = "False";
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto &i : temp2)
			tolower(i);
		bool converted = false;
		if (temp2 == "true") {
			converted = true;
		} else if (temp2 == "false")
			converted = false;
		else {
			print_console_out("Invalid input");
			return;
		}
		editing.dead = converted;
		current_value = temp2;
	} else if (stat == "turns_poisoned") {
		string temp = to_string(editing.turns_poisoned);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int converted = stoi(temp2);
		current_value = temp2;
		editing.turns_poisoned = converted;
	} else if (stat == "turns_on_fire") {
		string temp = to_string(editing.turns_on_fire);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int converted = stoi(temp2);
		current_value = temp2;
		editing.turns_on_fire = converted;
	} else if (stat == "dead") {
		string temp = "True";
		if (!editing.dead)temp = "False";
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto &i : temp2)
			tolower(i);
		bool converted = false;
		if (temp2 == "true") {
			converted = true;
		} else if (temp2 == "false")
			converted = false;
		else {
			print_console_out("Invalid input");
			return;
		}
		editing.dead = converted;
		current_value = temp2;
	} else if (stat == "current_attack") {
		string temp = to_string(editing.current_attack);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.current_attack = converted;
	} else if (stat == "current_defense") {
		string temp = to_string(editing.current_defense);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.current_defense = converted;
	} else if (stat == "attack_mod") {
		string temp = to_string(editing.attack_mod);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int converted = stod(temp2);
		current_value = temp2;
		editing.attack_mod = converted;
	} else if (stat == "evasivness") {
		string temp = to_string(editing.evasivness);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.evasivness = converted;
	} else if (stat == "accuracy") {
		string temp = to_string(editing.accuracy);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.accuracy = converted;
	} else if (stat == "hp_max") {
		string temp = to_string(editing.hp_max);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.hp_max = converted;
	} else if (stat == "mana_max") {
		string temp = to_string(editing.mana_max);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.mana_max = converted;
	} else if (stat == "hunger") {
		string temp = to_string(editing.hunger);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.hunger = converted;
	} else if (stat == "mana") {
		string temp = to_string(editing.mana);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.mana = converted;
	} else if (stat == "hp") {
		string temp = to_string(editing.hp);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.hp = converted;
	} else if (stat == "level") {
		string temp = to_string(editing.level);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.level = converted;
	} else if (stat == "range") {
		string temp = to_string(editing.range);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.range = converted;
	} else if (stat == "xp") {
		string temp = to_string(editing.xp);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.xp = converted;
	} else if (stat == "level_up_xp") {
		string temp = to_string(editing.level_up_xp);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		unsigned int converted = stoul(temp2);
		current_value = temp2;
		editing.level_up_xp = converted;
	} else if (stat == "intellect") {
		string temp = to_string(editing.intellect);
		string temp2 = modify_entity_sub_1(stat, temp);
		for (auto i : temp2) {
			if (!isdigit(i)) {
				print_console_out("Invalid input");
				return;
			}
		}
		int converted = stoi(temp2);
		current_value = temp2;
		editing.intellect = converted;
	} else {
		print_console_out("Invalid stat");
		return;
	}



	if (x == current_player.x or y == current_player.y) {
		current_player = editing;
	} else
		for (auto &i : level_entities) {
			if (i.x == x and i.y == y) {
				i = editing;
			}
		}


	print_console_out("New " + stat + ": " + current_value);

}




