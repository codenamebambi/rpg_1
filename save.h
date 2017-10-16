#include "globals.h"
#include "board.h"
#include "entity.h"
using namespace std;

class Map {
  public:
	string name;
	string linked;
	int SIZEX = 0;
	int SIZEY = 0; //no _ to differentiate
	vector<int> Ground;
	vector<int> Weather;
	vector<int> Mid;
	list<loot> Loot;
	list<entity> Entities;
	Map() {
		Ground.resize(this->SIZEY * this->SIZEX);
		Weather.resize(this->SIZEY * this->SIZEX);
		Mid.resize(this->SIZEY * this->SIZEX);
	}
	friend bool operator<(const Map &lhs, const Map &rhs) {
		return lhs.name < rhs.name;
	}
	//segfaults
	Map operator=(Map &rhs) {
		this->SIZEX = rhs.SIZEX;
		this->SIZEY = rhs.SIZEY;
		this->linked = rhs.linked;
		this->name = rhs.name;
		for (auto i : rhs.Ground)
			this->Ground.push_back(i);
		for (auto i : rhs.Mid)
			this->Mid.push_back(i);
		for (auto i : rhs.Weather)
			this->Weather.push_back(i);
		this->Loot.resize(0);
		this->Loot.merge(rhs.Loot);
		this->Entities.resize(0);
		this->Entities.merge(rhs.Entities);
	}
	friend ostream& operator<<(ostream& os, const Map &rhs) {
		os << rhs.SIZEX << endl;
		os << rhs.SIZEY << endl;
		for (auto i : rhs.Ground)
			os << i << endl;
		for (auto i : rhs.Mid)
			os << i << endl;
		for (auto i : rhs.Weather)
			os << i << endl;
		os << rhs.Loot.size() << endl;
		for (auto i : rhs.Loot)
			os << i; //loot and entity ostreams end in an endl
		os << rhs.Entities.size() << endl;
		for (auto i : rhs.Entities)
			os << i;
	}
	friend istream& operator>>(istream& is, Map &rhs) {
		is >> rhs.SIZEX;
		is >> rhs.SIZEY;
		rhs.Ground.resize(rhs.SIZEX * rhs.SIZEY);
		rhs.Mid.resize(rhs.SIZEX * rhs.SIZEY);
		rhs.Weather.resize(rhs.SIZEX * rhs.SIZEY);
		board.resize(rhs.SIZEX * rhs.SIZEY);
		for (auto && i : rhs.Ground)
			is >> i;
		for (auto && i : rhs.Mid)
			is >> i;
		for (auto && i : rhs.Weather)
			is >> i;
		int temp = 0;
		is >> temp;
		rhs.Loot.resize(temp);
		for (auto && i : rhs.Loot)
			is >> i; //loot and entity ostreams end in an endl
		is >> temp;
		rhs.Entities.resize(temp);
		for (auto && i : rhs.Entities)
			is >> i;
	}
	void Map_set() {
		this->Loot.resize(0);
		this->Entities.resize(0);
		for (auto i : level_loot) {
			this->Loot.push_back(i);
		}
		for (auto i : level_entities) {
			this->Entities.push_back(i);
		}
		this->SIZEX = SIZE_X;
		this->SIZEY = SIZE_Y;
		this->Ground.resize(0);
		for (auto i : ground)
			this->Ground.push_back(i);
		this->Mid.resize(0);
		for (auto i : mid)
			this->Mid.push_back(i);
		this->Weather.resize(0);
		for (auto i : weather)
			this->Weather.push_back(i);
	}
	void level_set() {
		level_loot.resize(0);
		level_entities.resize(0);
		ground.resize(0);
		mid.resize(0);
		weather.resize(0);
		for (auto i : this->Loot) {
			level_loot.push_back(i);
		}
		for (auto i : this->Entities) {
			level_entities.push_back(i);
		}
		SIZE_X = this->SIZEX;
		SIZE_Y = this->SIZEY;
		for (auto i : this->Ground)
			ground.push_back(i);
		for (auto i : this->Mid)
			mid.push_back(i);
		for (auto i : this->Weather)
			weather.push_back(i);
	}
};


void Save(Map &map_save) {
	fstream out;
	string s;
	cout << "Please enter a name for this level" << endl;
	cin.ignore();
	getline(cin, s);
	out.open(s, fstream::out);
	if (!out.is_open()) {
		cout << "Failed to open " << s << endl;
		return;
	} else {
		map_save.Map_set();
		map_save.name = s;
		out << map_save;
		cout << "File " << s << " saved" << endl;
	}
	out.close();
}


bool Load(string &s) {
	Map map_save;
	fstream in;
	in.open(s);
	if (!in.is_open()) {
		return false;;
	} else {
		in >> map_save;
		map_save.level_set();
	}
	in.close();
	return true;
}





