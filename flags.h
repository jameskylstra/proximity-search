#ifndef FLAGS_H
#define FLAGS_H

#include <string>
#include <map>
#include <iostream>
#include <cstdlib>
using namespace std;

class Flag {
    string flag_id;
    bool on;
  public:
    string getFlagId() const { return flag_id; }
    void setFlagId(string id) { flag_id = id; }
    bool isOn() const { return on; }
    void turnOn() { on = true; }
    void turnOff() { on = false; }
    void toggle() { on = !on; }
    Flag(string fid) : flag_id(fid), on(false) {};
    ~Flag() {}
};

class Flags {
    map<string, Flag> flag_map;
    char leader;
    bool isFlag(string arg) { return arg[0] == leader; }
  public:
    void gather(int argc, char* argv[]);
    Flags(char l = '-') : leader(l) {}
    ~Flags() {}
    const Flag& operator[](string flag_id) const {
	return flag_map.at(flag_id);
    }
    void add(Flag f) {
	flag_map.insert(pair<string, Flag>(f.getFlagId(), f));
    }
    void add(string fid) {
	flag_map.emplace(fid, Flag(fid));
    }
    void add(const string fids[], const int num_fids) {
	for (int i = 0; i < num_fids; i++)
	    flag_map.emplace(fids[i], Flag(fids[i]));
    }
};

extern Flags flags;

#endif //FLAGS_H
