#pragma once
#include "general.h"
#include "board.h"
#include "entity.h"
#include "print.h"
using namespace std;


class Map {
  public:
	string name = "NULL";
	vector<string> Linked; // format for linked strings is: "next_level exit_x exit_y" or "null"
	string Back_link = "NULL";
	int SIZEX = 0;
	int SIZEY = 0; //no _ to differentiate
	player P;
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
	//segaults last time i checked;
	Map operator=(Map &rhs) {
		this->SIZEX = rhs.SIZEX;
		this->SIZEY = rhs.SIZEY;
		this->name = rhs.name;
		for (const auto &i : rhs.Linked)
			this->Linked.push_back(i);
		for (const auto &i : rhs.Ground)
			this->Ground.push_back(i);
		for (const auto &i : rhs.Mid)
			this->Mid.push_back(i);
		for (const auto &i : rhs.Weather)
			this->Weather.push_back(i);
		this->Loot.resize(0);
		this->Loot.merge(rhs.Loot);
		this->Entities.resize(0);
		this->Entities.merge(rhs.Entities);
		return *this;
	}
	friend ostream& operator<<(ostream& os, const Map &rhs) {
		os << rhs.name << endl;
		os << rhs.Linked.size() << endl;
		for (auto i : rhs.Linked)
			os << i << endl;
		os << rhs.Back_link << endl;
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
		return os;
	}
	friend istream& operator>>(istream& is, Map &rhs) {
		int temp = 0;
		is >> rhs.name;
		is >> temp;
		rhs.Linked.resize(temp);
		for (auto & i : rhs.Linked) {
			for (int j = 0; j < 3; j++) {
				string temp_input;
				is >> temp_input;
				i += temp_input + " ";
			}
		}
		is >> rhs.Back_link;
		is >> rhs.SIZEX;
		is >> rhs.SIZEY;
		rhs.Ground.resize(rhs.SIZEX * rhs.SIZEY);
		rhs.Mid.resize(rhs.SIZEX * rhs.SIZEY);
		rhs.Weather.resize(rhs.SIZEX * rhs.SIZEY);
		board.resize(rhs.SIZEX * rhs.SIZEY);
		for (auto & i : rhs.Ground)
			is >> i;
		for (auto & i : rhs.Mid)
			is >> i;
		for (auto & i : rhs.Weather)
			is >> i;
		is >> temp;
		rhs.Loot.resize(temp);
		for (auto & i : rhs.Loot)
			is >> i; //loot and entity ostreams end in an endl
		is >> temp;
		rhs.Entities.resize(temp);
		for (auto & i : rhs.Entities)
			is >> i;
		return is;
	}
	void Map_set() {
		this->name = current_map_name;
		this->P = current_player;
		this->Linked.resize(0);
		for (auto i : linked)
			this->Linked.push_back(i);
		this->Back_link = back_link;
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
		current_map_name = this->name;
		current_player = this->P;
		linked.resize(0);
		for (auto i : this->Linked)
			linked.push_back(i);
		back_link = this-> Back_link;
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
	string s = map_save.name;
	/*
	   cout << "Please enter a name for this level" << endl;
	   cin.ignore();
	   getline(cin, s);
	   */
	out.open(s, fstream::out);
	if (!out.is_open()) {
		cout << "Failed to open " << s << endl;
		return;
	} else {
		map_save.Map_set();
		//		map_save.name = s;
		out << map_save.P;
		out << map_save;
		string temp = "File " + s + " saved";
		print_console_out(temp);
	}
	out.close();
}


bool Load(string &s) {
	Map map_save;
	fstream in;
	in.open(s);
	if (!in.is_open()) {
		return false;
	} else {
		in >> map_save.P;
		in >> map_save;
		map_save.level_set();
		clear_screen();
	}
	in.close();
	return true;
}



bool Load_link(int &in_x, int &in_y) {
	string n;
	int x = 0, y = 0;
	stringstream input;
	for (auto i : linked) {
		input << i;
		while (true) {
			input >> n >> x >> y;
			if (!input)
				return false;
		}
		if (x == in_x && y == in_y)
			break;
	}
	if (!(x == in_x && y == in_y))
		return false;
	Map map_save;
	fstream in;
	in.open(n);
	if (!in.is_open()) {
		return false;;
	} else {
		in >> map_save;
		map_save.level_set();
	}
	in.close();
	return true;
}




void modify_map_name() {
	print_console_out("Please enter a name");
	current_map_name = type();
	print_console_in("");
	print_console_out("Name set");
}

void modify_map_links() {
	print_console_out("Please enter a link");
	int c_in = 0;
	while (true) {
		bool break_check = false;
		int ch = getch();
		c_in = typing(ch);
		if (c_in == 1)
			;
		else if (c_in == 2) {
			string temp = console_input;
			stringstream temp_stream;
			int q = 0, w = 0;
			temp_stream << temp;
			temp_stream >> temp >> q >> w;
			if (!temp_stream || !temp_stream.eof()) {
				print_console_out("Invalid input");
				print_console_in("");
				break_check = true;
			}
			for (auto i : temp) {
				if (!isalnum(i)) {
					print_console_out("Invalid input");
					print_console_in("");
					break_check = true;
					break;
				}
			}
			if (break_check) break;
			linked.push_back(console_input);
			temp = "Link " + to_string(linked.size()) + " added";
			print_console_out(temp.c_str());
			print_console_in("");
			break;
		} else
			break;
		print_console_in(console_input);
		refresh();
	}
}

void remove_link() {
	print_console_out("Type yes to remove last link");
	int c_in = 0;
	while (true) {
		int ch = getch();
		c_in = typing(ch);
		if (c_in == 1)
			;
		else if (c_in == 2) {
			string temp;
			for (auto &i : console_input)
				i = toupper(i);
			if (console_input == "YES") {
				linked.pop_back();
				temp = "Link " + to_string(linked.size() + 1) + " removed";
			} else
				temp = "Link " + to_string(linked.size()) + " left alone";
			print_console_out(temp);
			print_console_in("");
			break;
		} else
			break;
		print_console_in(console_input);
		refresh();
	}
}




void modify_back_link() {
	print_console_out("Please enter a link");
	int c_in = 0;
	while (true) {
		bool break_check = false;
		int ch = getch();
		c_in = typing(ch);
		if (c_in == 1)
			;
		else if (c_in == 2) {
			string temp = console_input;
			stringstream temp_stream;
			temp_stream << temp;
			temp_stream >> temp;
			if (!temp_stream) {
				print_console_out("Invalid input");
				print_console_in("");
				break_check = true;
			}
			for (auto i : temp) {
				if (!isalnum(i)) {
					print_console_out("Invalid input");
					print_console_in("");
					break_check = true;
					break;
				}
			}
			if (break_check) break;
			back_link = console_input;
			temp = "Back link set";
			print_console_out(temp);
			print_console_in("");
			break;
		} else
			break;
		print_console_in(console_input);
		refresh();
	}
	print_console_in("");
}

