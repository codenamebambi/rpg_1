#pragma once
#include "globals.h"
#include "colors.h"
using namespace std;
int index(int, int);

class loot;
class entity;

list<entity> level_entities;
list<loot> level_loot;


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
	loot operator=(const loot& rhs) {
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
	unsigned int current_attack = 1;
	unsigned int current_defense = 1;
	float attack_mod = 1;
	unsigned int evasivness = 0;
	unsigned int accuracy = 0;
	unsigned int hp_max = 100;
	unsigned int mana_max = 50;
	unsigned int hunger = 0; //if accumulates to 100(max) you start losing 1hp each turn, does not apply to npc
	unsigned int mana = 0; //used for spells
	unsigned int hp = 0; //if drops to 0 you die
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
			float x = 1;
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
		float x = 1;
		if (this->resistance & full_fire)
			return;
		else if (this->resistance & half_fire)
			x = .5;
		this->hp -= 6 * x;
	}
	void Poisoned() {
		if (this->turns_poisoned <= 8  and  this->status & poisoned) {
			this->turns_poisoned++;
			float x = 1;
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
		if (this->hunger = 100) {
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
	void weapon_equip(int new_weapon) {
	}
	void armor_equip(int new_armor) {
	}
	virtual void terrain_check() {
	}
	void move_up(int direction) {
		if (direction == KEY_LEFT) {
			if (this->y - 1 > 0) {
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
			if (this->y + 1 < SIZE_Y) {
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
			if (this->x - 1 > 0) {
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
		if (direction == KEY_UP) {
			if (this->x + 1 < SIZE_X) {
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
	}
	void move_rand() {
		int x;
		while (true) {
			x = rand() % 4;
			if (x == 0) {
				if (this->y - 1 > 0) {
					if (mid.at(index(this->x, this->y - 1)) < Rock) {
						this->y--;
						break;
					}
				}
			}
			if (x == 1) {
				if (this->y + 1 < SIZE_Y) {
					if (mid.at(index(this->x, this->y + 1)) < Rock) {
						this->y++;
						break;
					}
				}
			}
			if (x == 2) {
				if (this->x - 1 > 0) {
					if (mid.at(index(this->x - 1, this->y)) < Rock) {
						this->x--;
						break;
					}
				}
			}
			if (x == 3) {
				if (this->x + 1 < SIZE_X) {
					if (mid.at(index(this->x + 1, this->y)) < Rock) {
						this->x++;
						break;
					}
				}
			}
		}

	}





	entity operator=(const entity &rhs) {

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
		os << rhs.drops << endl;
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

	}


};



class eyeball: public entity {
  public:


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
};



