#pragma once
#include <vector>
using namespace std;

enum UnitType{Soldier, Captain, MachineGun, Armor, Plane};

class Unit
{
public:
	Unit(UnitType ut);
	~Unit();
	int attack;
	int defense;
	int range;
	int movement;
	int health;
	enum Status{Healthy, Damaged, Dead};
	
	virtual int Attack(const Unit &unit);
	virtual int TakeDamage(int damage);
	virtual bool Move(vector<int> coords);

};

